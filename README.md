# Project Title

[Linas' Art Gallery](http://linas.org/art-gallery/index.html)

I couldn't run the programs so I made my own based on the description of algorithms

See:
* modified html files in html directory
* md files 
  * [DHParemeterRays](./DHParameterRays.md)
* [Linas Vepstas C programs](http://fraktal.republika.pl/linas.html)
* Images: static (png) and animated (gif)
* c and sh files 


## [Smooth Shading for the Mandelbrot Exterior](http://linas.org/art-gallery/escape/smooth.html)

Parameter plane ( c plane) with Mandelbrot set for complex quadratic polynomial fc(z) = z^2 + c
* Rectangle part of 2D parameter plane: 
  * [corners](https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#Corners): CxMin = -2.000000;   CxMax = 0.700000;  CyMin = -1.350000; CyMax = 1.350000 
  * [center and radius](https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#radius):  CenterX = -0.650000;   CenterY = 0.000000;  radius = 1.350000
  * [magnification = Mag = zoom](https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#magnification) = 0.740741
* [Pixel Size](https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#Pixel_size) : PixelWidth = 0.002700 and PixelHeight =0.002700
* Escape Radius = 3.000000
* Iteration Max = 18


Bands: Color is proportional to last ( final) iteration = i for which z escapes ( [Level set method = LSM/M or Integer Escape Time](https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/MandelbrotSetExterior#Integer_escape_time_.3D_LSM.2FM_.3D_dwell_bands) ). Level sets ( bands) of escape time  are visible

![bands](./bands.png) 


iter18-3e0: Color is proportional to [the renormalized, fractional iteration count](http://linas.org/art-gallery/escape/escape.html) ( [Real Escape Time](https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/MandelbrotSetExterior#Real_Escape_Time)). Level sets ( bands) of escape time  are not visible

![iter18-3e0](./iter18-3e0.png) 


## [Douady Hubbard Parameter Rays](https://linas.org/art-gallery/escape/phase/phase.html)


Parameter plane ( c plane) with Mandelbrot set for complex quadratic polynomial fc(z) = z^2 + c
* Rectangle part of 2D parameter plane: 
  * corners:  CxMin = -2.400000;   CxMax = 1.500000;  CyMin = -1.950000; CyMax = 1.950000 
  * center and radius:  CenterX = -0.450000;   CenterY = 0.000000;  radius = 1.950000
  * Mag = zoom = 0.512821
* PixelWidth = 0.003900 and PixelHeight =0.003900
* Escape Radius = 3.000000
* Iteration Max = 400


### Phase
Phase: color is proportional to angle ( phase) in turns of last Z ( final Z). Level sets ( bands) of escape time  are visible

![phase](./phase.png)

Steps
* pick c which is your pixel
* iterate $`z^2+c`$ until $`|z| > EscapeRadius`$.  Call this the "final z"  . Count the number of iterations until escape. Call this N.
* Use phase(final_z)  as the color scheme at pixel c.  This gives the phase picture.

Clearly, you can see bands encircling the m-set, and each band winds twice as often as the one before. 


Compare with:
* [ External angles in the Mandelbrot set: the work of Douady and Hubbard. by Professor Douglas C. Ravenel](https://web.math.rochester.edu/people/faculty/doug/oldcourses/215s98/lecture10.html)
* [Mandelbrot set decomposition](http://fraktal.republika.pl/mset_decomposition.html)




 

### Winding number or the external angle

(to do !!!!)

How to remove from [phase image](phase.png): 
* level sets of escape time
* doubling of bands inside level sets 

Names: 
* winding number ( external angle)
* cnt = counter, it is an integer value 
* 


#### cnt ( )

Steps
* pick c which is your pixel.  set integer cnt=0
* iterate $`z^2+c`$ until $`|z| > EscapeRadius`$.  Call this the $`z_{final}`$  . Count the number of iterations until escape. Call this N.
* Use $`phase(z_{final})`$  as the color scheme at pixel c.  This gives [the phase picture](phase.png)
* For each iteration adjust phase so that phase(z) lies between 0 and 2pi. Then 
  * if (phase(z) > pi) then cnt+=1;  because the next iteration will cause the phase to go over 2pi. 
  * set  cnt = 2*cnt; because the next iteration is doubling the angle.
* Repeat until escape.

$`angle(c) =  (2 pi * cnt + phase(z_{final}))  / 2^N`$

Note that if N is large, then $`phase(z_{final})/2^N`$ is small, and you can  ignore it. then one simply has:

$`angle(c) =  2 pi * cnt / 2^N`$

and that is all.


![ ](phase_cnt.png)

It was made with:
* [phase_cnt.c](phase_cnt.c)


#### simple algorithm  (binary)

The 'lining up' and doubling for each iteration allows us to use binary numbers to identify each region. 

For the outermost region, we can use:
* 0 to denote the upper half
* 1 to denote the lower half. 

Then, for each subsequent band, we can use:
* 0 if the band lines up to angles less than pi in the previous band
* 1 if it lines up with angles greater than pi in the previous band. 

Thus, [any sequence of binary digits can be used to walk us towards the M-set](http://www.fractalforums.com/animations-showcase-(rate-my-short-animation)/binary-decomposition-and-external-angles/), with each digit determining which fork should be taken. 

If we put a decimal point in front of the sequence, then we have a binary expansion of a real number between 0 and 1. We refer to this number, somewhat incorrectly, as the winding number.



Lets look a this another way: for any real number 0 < x < 1 write down its binary expansion. 

Then use the digits of the binary expansion to pick one's way down through each band. After an infinite number of steps, 
we've reached a unique point at the surface of the M-set. For every number, there's a point at the surface. 

We use the 'lining-up' or period-doubling to subtract out its effects, and generate the winding number shown here.  
Basically, by looking at the first picture, we can see that we can match up the colors by totaling up the winding number as the phase wraps around, and then dividing by 2n-1 for each band. 


The algorithm we used here is the simplest and fastest possible:
* For each parameter c, and each iteration k, we compute the phase $`t_k = arctan(z_k)`$  where$`z_k = r^ke^{it_k}`$ 
* Since arctan always uses one branch, we try to track period doubling by comparing $`t_k`$ to $`t_{k-1}`$ 
* We know that tk should be increasing usually: $`t_{k-1} < t_k`$ ; and we can use this to count the winding number. 

This algorithm is pretty good; its fast, its simple, but is not perfect, and it has a few small defects. 




![winding - original image ](./html/Douady Hubbard Parameter Rays_files/winding-small.gif)


Small defects are barely visible in the image above, but are prominent in the closeups. 

![bud2](./html/Douady Hubbard Parameter Rays_files/defect-bud2-small.gif)
![bud3](./html/Douady Hubbard Parameter Rays_files/defect-bud3-small.gif)

#### correct algorithm



Here's an example of an 'almost' correct algorithm. The idea here is to try to step/integrate along lines of constant phase, moving away from the M-set. We use the vector Dm (employing the notation introduced on the Potential Page) as a predictor to step one iteration at a time away from the M-set. The explicit algorithm is this: Define a sequence {ck} with c0 = c and k<n, where n is the number of times that c is iterated until it reaches some (large) escape radius. Then try

$`c_{k+1} = c_k - 2Dmk/|Dmk|2`$

where Dmk is the derivative of the fractional iteration count m at ck. 

With each ck, we iterate one less time, (i.e. we iterate n-k times). Then the phase of cn seems to be an approximation to the true phase. In particular, it is free of the discontinuities plaguing the simple algorithm.  

Notice how much prettier, and more visually correct these images are, compared to their equivalents above. 
 
![bud2](./html/Douady Hubbard Parameter Rays_files/correct-bud2-small.gif)
![bud3](./html/Douady Hubbard Parameter Rays_files/correct-bud3-small.gif)  

However, this algorithm has some serious spread-out error terms, as shown here.  This image shows the difference between the exact phase, and our approximation. The image is colored so that red represents differences of 2 percent or more between the approximate and the true phase. Although 2 percent may seem small, it is hopelessly large when used for tracing rays. 



![](./html/Douady Hubbard Parameter Rays_files/algo-diff-small.gif)




### final phase after fixed number of iterations without bailout test 

There is no such image in Linas gallery, but I think it could be there

![](phase_f.gif)  

Image was made with 
* [phase_f.c](phase_f.c)
* [phase_f.sh](phase_f.sh) and [Image Magic](https://www.imagemagick.org/script/convert.php)

In the right up corner each frame one can see a number wich shows maximal number of iterations for this frame.


Explanation:
* [algorithm 9 : zeros of qn(c) from program Mandel by WOlf Jung](https://en.wikibooks.org/wiki/Fractals/mandel#algorithm_9_:_zeros_of_qn.28c.29)


compare it with 
* [Formation of Mandelbrot set](https://christopherolah.wordpress.com/tag/sage/) by Christopher Olah
* [Analysis of critical point of z→z²+c ](https://commons.wikimedia.org/wiki/File:Mandelbrot-Iterate-01.jpg?uselang=en) by [Georg-Johann Lay](https://de.wikipedia.org/wiki/Benutzer:Georg-Johann/Mathematik#Visualising_complex_functions)
* [Mandelbrot fractal: How is it possible? from math.stackexchange](https://math.stackexchange.com/questions/32062/mandelbrot-fractal-how-is-it-possible)
* [Phase Angle Shading](http://www.fractalforums.com/index.php?action=gallery;sa=view;id=20141) : Using phase angle of z after it has escaped to shade the image rather than the number of iterations needed for z to escape. by wes
* [ Creating the Mandelbrot set](http://web.ncf.ca/fs039/mp/documents/ptr/) by Martin Pergler
* [Mandelbrot function ](http://www.quadibloc.com/math/mbint.htm) by John J. G. Savard
* [Mandel image by GONZALO E. MENA](https://gomena.github.io/gifs/fractals1/) where at each iteration (frame of the gif) different colors correspond to the angle of the iterations at each point

Note 2 differences
* in my image exterior comes black not white as in Gonzalo image
* in my image ther is no black part near center of main cardioid. Such structure can be seen on other images.

See:
* the differencesc between odd and even frames


# Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

# Prerequisites

What things you need to install the software and how to install them
* c compiler: gcc
* Image Magic ( for file conversion)

Here is example how to use old ( from 1996) original c code 

```
gcc image.c -lm -Wall
./image image.flo 1000 1000
./flo2mtv image.flo > image.mtv
 convert image.mtv image.png 
```

I could not run new code ( 2000)

### Installing

A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

### Git
```
git init
git remote add origin git@gitlab.com:adammajewski/LinasArtGallery_MandelbrotSet.git
git add html
git commit -m "html"
git push -u origin master
```


### HTML preview

[GitHub & BitBucket HTML Preview](http://htmlpreview.github.io/?)




## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [n](link) - description

## Contributing

Please read [CONTRIBUTING.md](link) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [name](link) for versioning. 

## Authors

* 

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the  Creative Commons Attribution-ShareAlike 4.0 International License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone who's code was used
* Inspiration
* etc

# technical note
GitLab uses:
* the Redcarpet Ruby library for [Markdown processing](https://gitlab.com/gitlab-org/gitlab-ce/blob/master/doc/user/markdown.md)
* KaTeX to render [math written with the LaTeX syntax](https://gitlab.com/gitlab-org/gitlab-ce/blob/master/doc/user/markdown.md), but [only subset](https://khan.github.io/KaTeX/function-support.html)


