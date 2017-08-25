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

## Instructions for Linux
To compile run `make` from the command line and it will create an executable called `release`. 

To run use `./release` from the command line and the program will run with the default overview of the Mandelbrot set. 
You will need to create a configuration file for more complex renders and pass that file in as an argument when running the program.

For example, to see a more complex render, use the following:
```
make
./release pretty.txt
```
This will generate a ppm file called pretty.ppm with a render colored as per your selection. To convert a ppm file to a png file you can use almost anything, but Image Magick works well from the command line.
```
sudo apt install imagemagick
convert pretty.ppm pretty.png
```
NOTE: This code doesn't want to compile with g++ version 4.8. I had to install version 7.2 before it would work (`sudo apt install g++-7`) even though the code is all C++11 compliant. 
