# Project Title

[Linas' Art Gallery](http://linas.org/art-gallery/index.html)

I couldn't run the programs so I made my own based on the description of algorithms

See:
* modified html files in html directory
* md files 
  * [DHParemeterRays](./DHParameterRays.md)
* [Linas Vepstas C programs](http://fraktal.republika.pl/linas.html)
* Images


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



Phase: color is proportional to angle in turne of last Z. Level sets ( bands) of escape time  are visible

![phase](./phase.png)


Winding: color is proportional to winding number of the map 

![winding](./winding.png)


Small defects are barely visible in the image above, but are prominent in the closeups. 


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
