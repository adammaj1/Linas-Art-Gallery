
/* 



   The "bug" in your code is simple: you are adding phases; this is wrong.  Instead, do this: 

Step zero: pick c which is your pixel.  set integer cnt=0

Step one: iterate z^2+c until |z| > escape_radius.  Call this the "final z"  . Count the number of iterations until escape. Call this N.

Step two: Use phase(final_z)  as the color scheme at pixel c.  This gives the very first picture.

Clearly, you can see bands encircling the m-set, and each band winds twice as often as the one before.  Therefore, we need to count how often it winds.  The counting is with integers.

Step 3:  
For each iteration, adjust so that phase(z) lies between 0 and 2pi.
For each iteration: if (phase(z) > pi) then cnt+=1;  because the next iteration will cause the phase to go over 2pi. 
For each iteration set  cnt = 2*cnt; because the next iteration is doubling the angle.
Repeat until escape.

Define the ray angle as:   ray_angle( at c) =  (2 pi * cnt + phase(final_z))  / 2^N

Note that if N is large, then phase(final_z)/2^N is small, and you can  ignore it. then one simply has:

ray_angle( at c) =  2 pi * cnt / 2^N

and that is all.

Step 4: The above works "most of the time". However, as you zoom around in the picture, you discover that counting with that simple if-statement: "if (phase(z) > pi) then cnt+=1; cnt = 2*cnt;"  is not quite right.  It sometimes mis-counts.  So then I tried to get clever, to avoid mis-counting. Some of the fixes are "obvious", they adjust the count, and fix the gross mistakes, but then there are smaller, finer details, where the count is wrong. And these get hard to fix.  I was never able to find a perfect, mistake-free way of counting. This might be one of the great, unsolved problems of the M-set.  Either that, or I was just stupid, and there is some simple answer. I don't know. 

Part of the ray-angle stuff is that the rays have a vanishing laplacian, and so perhaps one can always correct mistakes by computing the laplacian, and then adjusting the angle to force it to be zero.  Just an idea.
    
--------------------------------------------------------------------------------------------------------    
 Perhaps this code snippet will be clearer:

double ray_angle(complex C)
{
   int cnt = 0;
   complex Z = C;
   for (int loopy=1; loopy < 10000; loopy++)
   {
       Z=Z*Z+C;
       double phase = arctan2(im_part(C), re_part(C));  // returns from -pi to +pi
       if (phase > 0.0) cnt +=1;
       cnt *= 2;

       if (abs(Z) > 1.0e10) break;
   }

    return 2.0*M_PI * ((double) cnt) / ((double) (1<<loopy));   // or also the below is slightly better
    return (2.0*M_PI * ((double) cnt) + arctan2(im_part(C), re_part(C)) + M_PI) / ((double) (1<<loopy));  
}

I think I got that right. I might be off-by-one with "loopy". Not sure.

--linas   

---------------
There were several buglets.
Bug 1: you were returning 0 to 2pi, but color wants 0 to 1.  So, get rid of the 2pi.
Bug 2: loop count was off-by-one, so the wrap only went half-way.

 This now works, for me.  Next step: do you see those big "thorns" sticking up?  Those thorns are because the test: 

if (phase > 0.5) cnt +=1;

is almost, but not quite correct. By fiddling with this, you can move the thorns, make them smaller, change their shape.  I was unable to find a generic solution that completely eliminated these thorns.

--linas

    
    
    
    

   http://linas.org/art-gallery/escape/phase/phase.html
   image 
   http://linas.org/art-gallery/escape/phase/winding.gif
  
   c console program:
   
   
   --------------------------------
   1. draws Mandelbrot set for Fc(z)=z*z +c
   using Mandelbrot algorithm ( boolean escape time )
   -------------------------------         
   2. technique of creating ppm file is  based on the code of Claudio Rocchini
   http://en.wikipedia.org/wiki/Image:Color_complex_plot.jpg
   create 24 bit color graphic file ,  portable pixmap file = PPM 
   see http://en.wikipedia.org/wiki/Portable_pixmap
   to see the file use external application ( graphic viewer)
   
   
   complex point c -> virtual 2D array -> memory 1D array -> ppm file on the disc -> png file 
   
   C -> pixel (iX,iY)  -> index k  -> 24bit color 
   
   -----
   https://stackoverflow.com/questions/6418807/how-to-work-with-complex-numbers-in-c
   complex numbers are built in type 
 
 --------------
 formated with emacs
   -------------
   to compile : 

 
 
   gcc phase_cnt.c -lm -Wall 
 
 
   ./a.out
   
   
   to convert to png using ImageMagic

   convert winding.ppm winding.png  



   ----------------------
   git add  phase_cnt.png phase_cnt.c README.md
   git commit -m "phase_cnt for winding"
   git push -u origin master



 
 
*/
#include <stdio.h>
#include <stdlib.h>		// malloc
#include <math.h>
#include <complex.h> // https://stackoverflow.com/questions/6418807/how-to-work-with-complex-numbers-in-c
 
 

 

 
 
/* screen ( integer) coordinate */

const int iWidth  = 1000; 
const int iHeight = 1000;


/* world ( double) coordinate = parameter plane*/
// double complex C =  Cx + Cy*I ;
 double CxMin=-2.4*2.0;
 double CxMax= 1.5*2.0;
 double CyMin=-1.95*2.0;
 double CyMax= 1.95*2.0;

/* */
double PixelWidth; //=(CxMax-CxMin)/iWidth;
double PixelHeight; // =(CyMax-CyMin)/iHeight;


/* color component ( R or G or B) is coded from 0 to 255 */
/* it is 24 bit color RGB file */
int ColorBytes = 3; // 3*8 = 24 bit color        

/* iterations  */
const int IterationMax=500;

/* bail-out value , radius of circle ;  */
// The bigger the escape radius, the smoother the coloring.
const double EscapeRadius=1.0e15;

double TwoPi=2.0*M_PI;

       
// memmory virtual 1D array 
unsigned char *data;       
size_t MemmorySize;       
    
    
void GiveLinasColor(double position , int k, unsigned char c[])
{
  /* based on the code by Linas Vepstas January 16 1994 : void make_cmap (void) */

   
  int i;
  int iMax = 240;
  i=(int)(iMax-1)*position;  
  c[0] = c[1] = c[2] = 0;
  /* set up a default look up table */
  /* ramp up to blue */
  if (i<60) {
    c[k] = 0;
    c[k+1] = 0;
    c[k+2] = (unsigned char) i*3;
  }
  /* ramp down from blue, up to green */
  if (i>=60 && i<120) {
    c[k] = 0;
    c[k+1] = (unsigned char) (i-60)*3;
    c[k+2] = (unsigned char) (120-i)*3;
  }
  /* ramp from green to yellow */
  if (i>=120 && i<180) {
    /* vlt[i].r = (char) (((i-120)*7) / 2); */
    c[k] = (unsigned char) (210 - (7*(180-i)*(180-i)) / 120);
    c[k+1] = (unsigned char) (210 -i/4);
    c[k+2] = 0;
  }
  /* ramp from yellow to red (pink) */
  if (i>=180 && i<iMax) {
    c[k] = (unsigned char) (210 + (3*(i-180))/4);
    c[k+1] = (unsigned char) (510 - 2*i);
    c[k+2] = (unsigned char) (i-180)/3;
  }
   
}

       
        
/* 
   gives position ( index) in 1D virtual array  of 2D point (iX,iY) from ; uses also global variable iWidth 
   without bounds check !!
*/
int f(int ix, int iy)
{ return ColorBytes*(ix + iy*iWidth); }
        
        
        
double complex give_c(int iX, int iY){
  double Cx,Cy;
  Cy=CyMax - iY*PixelHeight; // inverse y axis
  
  Cx=CxMin + iX*PixelWidth;
   
  return Cx+Cy*I;
 
 
}
 
 

double GiveTurn(double complex z)
{
  double argument;
 
  argument = carg(z); //   argument in radians from -pi to pi
  if (argument<0) argument=argument + TwoPi; //   argument in radians from 0 to 2*pi
  return argument/TwoPi ; // argument in turns from 0.0 to 1.0
}






 
double GiveExternalAngle(complex C)
{
   int cnt = 0;
   complex Z = C;
   int i;
   double phase = 0.0;
   
   
   for (i=1; i < IterationMax; i++)
   {   
       	phase = GiveTurn(Z);  // returns from 0.0 to 1.0 
	      if (phase > 0.5) cnt +=1;   		
       
      	Z=Z*Z+C;
       
       	cnt *= 2; // 

       	if (cabs(Z) > EscapeRadius) break;
   }


    phase = GiveTurn(Z); 
    
    // return phase + cnt/pow(2.0, i+1); // 1. level sets visible , doubling visible
    // return cnt/pow(2.0, i+1); // 2. 
    return (2.0*phase + cnt)/pow(2.0, i+1); // 3. 

    
} 


int ComputeAndSavePixelColor(int iX, int iY){
 
  
  complex double C;
  //int i; // iteration
  
  int k; // index of the 1D array
  double t = 0.0;
  
  
  // index of 1D memory array
  k = f(iX, iY);  
   
  C = give_c(iX, iY);
  t = GiveExternalAngle(C);
  
  
  GiveLinasColor(t , k,  data); //
      
    
 
   
  return 0;
}
 
int setup(){
 
  //
  PixelWidth=(CxMax-CxMin)/iWidth;
  PixelHeight=(CyMax-CyMin)/iHeight;
  //
    
  //
  MemmorySize = iWidth * iHeight * ColorBytes * sizeof (unsigned char);	// https://stackoverflow.com/questions/492384/how-to-find-the-sizeof-a-pointer-pointing-to-an-array
        
  /* create dynamic 1D arrays for colors   */
  data = malloc (MemmorySize);
  if (data == NULL )
    { fprintf (stderr, " Error: Could not allocate memory !!! \n"); return 1; }

  printf (" No errors. End of setup \n");
  return 0;

}
 
 
 
 
 
// save dynamic "A" array to pgm file 
int SaveArray_2_PPM_file (unsigned char A[])
{

  FILE *fp;
  const unsigned int MaxColorComponentValue = 255;	/* color component is coded from 0 to 255 ;  it is 8 bit color file */
  char *filename = "phase_cnt.ppm";
  char *comment = "# ";		/* comment should start with # */

  /* save image to the pgm file  */
  fp = fopen (filename, "wb");	/*create new file,give it a name and open it in binary mode  */
  fprintf (fp, "P6\n %s\n %u %u\n %u\n", comment, iWidth, iHeight, MaxColorComponentValue);	/*write header to the file */
  fwrite (A, MemmorySize, 1, fp);	/*write A array to the file in one step */
  printf ("File %s saved. \n", filename);
  fclose (fp);

  return 0;
}


 
 
void CreateImage(){
  int iX,iY; // screen = integer coordinate in pixels       

  // fill the array = render image = scanline 2D  of virtual 2D array 
  for(iY=0;iY<iHeight;iY++)
    for(iX=0;iX<iWidth;iX++)
      ComputeAndSavePixelColor(iX, iY); 
      	
      	
  SaveArray_2_PPM_file (data);     	  
} 
 
 
 
void info(){

  printf(" Parameter plane ( c plane) with Mandelbrot set for complex quadratic polynomial fc(z) = z^2 + c\n ");
  printf(" Rectangle part of 2D parameter plane: corners: \n CxMin = %f;   CxMax = %f;  CyMin = %f; CyMax = %f \n ", CxMin, CxMax, CyMin, CyMax);
  printf(" center and radius: \n CenterX = %f;   CenterY = %f;  radius = %f\n ", (CxMax+CxMin)/2.0, (CyMax+CyMin)/2.0, fabs(CyMax-CyMin)/2.0);
  printf(" Mag = zoom = %f\n ",  2.0/fabs(CyMax-CyMin));
  printf("PixelWidth = %f and PixelHeight =%f\n", PixelWidth, PixelHeight);
  printf(" Escape Radius = %f\n ", EscapeRadius);
  printf(" Iteration Max = %d\n ", IterationMax);



} 
 
 
 
void close(){
 
  info(); 
  free(data); 
}
 
 
 
int main()
{
 
  setup();      
  CreateImage();     
  close();
  
        
  return 0;
}
