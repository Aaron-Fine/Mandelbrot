# Mandelbrot Generator
Created by Aaron Fine

## References
* Basic algorithms - https://en.wikipedia.org/wiki/Mandelbrot_set
* Advanced color gradient - https://stackoverflow.com/questions/16500656/which-color-gradient-is-used-to-color-mandelbrot-in-wikipedia
* Good Python version - https://www.ibm.com/developerworks/community/blogs/jfp/entry/My_Christmas_Gift?lang=en
* Better Escape Time - http://linas.org/art-gallery/escape/escape.html
* Smooth Coloring - https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/

## Description
This program will generate mandelbrot fractals and color them based on various user selectable schemes.

The generated image file will be in a basic PPM format.

You can save generation parameters into a file that matches the following format
```
width height
xComplexMin xComplexMax
yComplexMin yComplexMax
maxIterations
outputFileName
```