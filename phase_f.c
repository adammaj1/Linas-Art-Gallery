
/* 


  https://gomena.github.io/gifs/fractals1/
  " at each iteration (frame of the gif) different colors correspond to the angle of the iterations at each point "
  GONZALO E. MENA
  
  
   c console program:
   
   
   --------------------------------
   1. draws parameter plane for Fc(z)=z*z +c
   
   -------------------------------         
   2. technique of creating ppm file is  based on the code of Claudio Rocchini
   http://en.wikipedia.org/wiki/Image:Color_complex_plot.jpg
   create 24 bit color graphic file ,  portable pixmap file = PPM 
   see http://en.wikipedia.org/wiki/Portable_pixmap
   to see the file use external application ( graphic viewer)
   
   
   complex point c -> virtual 2D array -> memory 1D array -> ppm files on the disc -> gif file -> animated gif
   
   https://commons.wikimedia.org/wiki/File:Douady_rabbit_-_final_phase_after_fixed_number_of_iterations_without_bailout_test.gif
   https://gitlab.com/adammajewski/dynamic_external_angle/blob/master/f150.gif
   
   Z -> pixel (iX,iY)  -> index k  -> 24bit color 
   
   -----
   https://stackoverflow.com/questions/6418807/how-to-work-with-complex-numbers-in-c
   complex numbers are built in type 
 
   --------------
   formated with emacs
   -------------
   to compile : 

 
 
   gcc phase_f.c -lm -Wall 
 
 
   ./a.out
   
   
   to convert to png using ImageMagic

   convert phase.ppm phase.png  
   
   use f.sh to create animated gif



   ----------------------
   cd existing_folder
   git init
   git remote add origin git@gitlab.com:adammajewski/LinasArtGallery_MandelbrotSet.git
   git commit -m "Initial commit"
   git push -u origin master

------------------------------
 
*/
#include <stdio.h>
#include <stdlib.h> // malloc and  ISO C Random Number Functions */
#include <math.h>
#include <complex.h> // https://stackoverflow.com/questions/6418807/how-to-work-with-complex-numbers-in-c
#include <string.h> // strncat 
 

 


// screen ( integer) coordinate 

const int iWidth  = 1000; 
const int iHeight = 1000;


/* world ( double) coordinate = parameter plane*/
// double complex C =  Cx + Cy*I ;
double CxMin;
double CxMax;
double CyMin;
double CyMax;

/* */
double PixelWidth; //=(CxMax-CxMin)/iWidth;
double PixelHeight; // =(CyMax-CyMin)/iHeight;


/* color component ( R or G or B) is coded from 0 to 255 */
/* it is 24 bit color RGB file */
int ColorBytes = 3; // 3*8 = 24 bit color 
#define iRed 1 
#define iWhite  2       

/* iterations  */
int  IterationMax = 10 ;

/* bail-out value , radius of circle ;  */
const double EscapeRadius=2.0;
double m = 2.0; //  multiplier


double TwoPi=2.0*M_PI;



       
// memmory virtual 1D array 
unsigned char *data;       
size_t MemmorySize;   

/* 
   gives position ( index) in 1D virtual array  of 2D point (iX,iY) ;
   uses also global variable iWidth 
   without bounds check !!
*/
int f(int ix, int iy) // Give_k
{ return ColorBytes*(ix + iy*iWidth); }



       
void GiveGrayColor(double position , int k, unsigned char A[]) 
{
  unsigned char b = 255*position; // then exterior becomes white for large iter max
  A[k]   = b;
  A[k+1] = b;
  A[k+2] = b;

}


void ColorPixel(int iColor, int k, unsigned char A[])
{
  switch (iColor)
    {
    case iRed:    A[k]   = 255; A[k+1] = 0;   A[k+2] = 0;   break;
    case iWhite : A[k]   = 255; A[k+1] = 255; A[k+2] = 255; break;
    }
}




       

        
        
        
double complex give_C(int iX, int iY){
  double Cx, Cy;
  Cy = CyMax - iY*PixelHeight; // inverse y axis
  
  Cx = CxMin + iX*PixelWidth;
   
  return Cx + Cy*I;
 
 
}
 
 

double GiveTurn(double complex z)
{
  double argument;
  
  argument = carg(z); //   argument in radians from -pi to pi
  
  if (argument<0.0) 
    argument = TwoPi + argument ; //   argument in radians from 0 to 2*pi
     
  return (argument/TwoPi) ; // argument in turns from 0.0 to 1.0
}

int ComputeAndSavePixelColor(int iX, int iY){
 
  
  
  int i=0; // iteration
  double complex Z; // initial value for iteration Z0
  double complex C;
  int k; // index of the 1D array
  
  // argument of complex numer in turns
  double tf; //final turn = z after IterationMax forward iterations   
  
  
  // index of 1D memory array
  k = f(iX, iY);   
  
  C = give_C(iX, iY);  
  Z = C; // z0 = 0 so on the image all pixels have the same color
  
      
        
  // forward iteration with fixed number of iterations
  // without bailout test
  for  (i=0;  i<IterationMax; i++)
    Z=Z*Z+C; // forward iteration 
  
  tf =  GiveTurn(Z); // compute angle in turns of final z = final turn = tf
  GiveGrayColor(tf,k,data);  // color pixel proportionaly to tf
  	
  return 0;
}
 
 
 
void Draw(){

  int iX,iY; // screen = integer coordinate in pixels       

  // fill the array = render image = scanline 2D  of virtual 2D array 
  for(iY=0;iY<iHeight;iY++)
    for(iX=0;iX<iWidth;iX++)
      ComputeAndSavePixelColor(iX, iY); 
      	


} 
 




 
 
int setup(){


  CxMin= -3.0;
  CxMax=  1.0;
  CyMin= -2.0;
  CyMax=  2.0;
 
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
int SaveArray_2_PPM_file (unsigned char A[], int iMax)
{

  FILE *fp;
  const unsigned int MaxColorComponentValue = 255;	/* color component is coded from 0 to 255 ;  it is 8 bit color file */
  
  char name [100]; /* name of file */
  snprintf(name, sizeof name, "%d", iMax); /*  */
  char *filename =strncat(name,".ppm", 4);
  
  
  char *comment = "# ";		/* comment should start with # */

  /* save image to the pgm file  */
  fp = fopen (filename, "wb");	/*create new file,give it a name and open it in binary mode  */
  fprintf (fp, "P6\n %s\n %u %u\n %u\n", comment, iWidth, iHeight, MaxColorComponentValue);	/*write header to the file */
  fwrite (A, MemmorySize, 1, fp);	/*write A array to the file in one step */
  printf ("File %s saved. \n", filename);
  fclose (fp);

  return 0;
}


 
 
void CreateImage(int iMax){

  IterationMax = iMax;
  Draw();
  
  
  
  
      	
  SaveArray_2_PPM_file (data, iMax);     	  
} 
 
 
 
void info(){

  printf(" Parameter plane ( c plane)  for complex quadratic polynomial fc(z) = z^2 + c\n ");
  printf(" Rectangle part of 2D dynamic plane: corners: \n CxMin = %f;   CxMax = %f;  CyMin = %f; CyMax = %f \n ", CxMin, CxMax, CyMin, CyMax);
  printf(" center and radius: \n Center = (%f; %f)  radius = %f\n ", (CxMax+CxMin)/2.0, (CyMax+CyMin)/2.0, fabs(CyMax-CyMin)/2.0);
  printf(" Mag = zoom = %f\n ",  2.0/fabs(CyMax-CyMin));
  printf(" PixelWidth = %f and PixelHeight =%f\n", PixelWidth, PixelHeight);
  printf(" Escape Radius = %f\n ", EscapeRadius);
  printf(" Iteration Max = %d\n ", IterationMax);
  


} 
 
 
 
void close(){
 
  info(); 
  free(data); 
}
 
 
 
int main()
{

  int i;
 
  setup();   
     
  for (i=0; i< 30; i++)
    CreateImage(i); 
  	
  	
  	
  close();
  
        
  return 0;
}
