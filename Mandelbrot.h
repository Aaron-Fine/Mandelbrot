//
// Created by finea on 8/10/2017.
//

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#include "MandelConfig.h"
#include <tuple>

class Mandelbrot
{
    /**
     * This class is the base class for all other mandelbrot generators. This class handels everything except coloring
     * the final mandelbrot.
     */
protected:
    /**
     * Holds all the relevant information about what the fractal should be. This tells you things like:
     * Width, Height, location in complex plane, output file name, etc.
     */
    MandelConfig config;

    /**
     * 2D array of iteration values from the escape time algorithm. See getEscapeTime for details.
     */
    unsigned int** iterMap;

    /**
     * Reference value chosen to match typical RGB maximum values.
     */
    const unsigned int maxColorValue = 255;

public:
    /**
     * Base constructor for a mandelbrot set
     * @param initConfig This is an object that contains all of the configuration options for a mandelbrot.
     * This tells the generator what to generate.
     */
    explicit Mandelbrot( const MandelConfig& initConfig );

    /**
     * Includes code to correctly destruct the generated iteration map.
     */
    ~Mandelbrot();

    /**
     * Generates an iteration map over the area specified in the configuration object.
     * Basically, this uses an escape time algorithm to see if any particular point is part of the mandelbrot set
     * and then stores the number of iterations needed to make that determination. This iteration count can then be
     * used later for coloring the fractal image.
     */
    void generate();

    /**
     * Saves the generated fractal image to the filename specified in the configuration object.
     */
    void save()
    {
        saveTo( config.getFileName());
    }

    /**
     * Saves the generated fractal image to the given filename.
     * @param outputFile A string representing the file you want to save you image to.
     * EXAMPLE: output.ppm or mandelbrot.ppm
     */
    void saveTo( const std::string& outputFile );

    /**
     * Diagnostic function to write all of the actual iteration counts out to a CSV file.
     * @param outputFile A string representing the name of the CSV output file.
     * EXAMPLE: iterations.csv (5 x 5 grid with 80 as max iteration count)
     *
     *   28,    24,    29,    34,    80,
     *   24,    42,    35,    80,    80,
     *   35,    46,    80,    80,    80,
     *   35,    46,    80,    80,    80,
     *   24,    42,    35,    80,    80,
     */
    void outputIterations( const std::string& outputFile );

    /**
     * Diagnostic function to write out the frequency of each iteration count to a CSV file.
     * @param outputFile A string representing the name of the CSV output file.
     * EXAMPLE: histogram.csv
     *
     * 0, 0
     * 1, 0
     * 2, 0
     * 3, 0
     * 24, 3
     * 25, 0
     * 26, 0
     * 27, 0
     * 28, 1
     * 29, 1
     * 30, 0
     * 31, 0
     * 32, 0
     * 33, 0
     * 34, 1
     * 35, 4
     * 36, 0
     * 37, 0
     * 38, 0
     * 79, 0
     */
    void iterationHistogram(const std::string& outputFile );

private:
    /**
     * Calculates the escape count of a given pixel in the complex plane.
     * Code based on https://en.wikipedia.org/wiki/Mandelbrot_set psudo code
     * See http://yozh.org/2010/12/01/mset005/ for a good explanation of escape time and what it means.
     * @param x0 The 'X' position in the complex plane for the point we are evaluating
     * @param y0 The 'Y' position in the complex plane for the point we are evaluating
     * @return The escape count between 0 and the max allowed by the configuration
     */
    unsigned int getEscapeCount( double x0, double y0 );

    /**
     * Translates iteration values to RGB color values.
     * @param iteration See getEscapeCount for details, but will be between 0 and the max allowed by the configuration
     * @return Red, Green, Blue values between 0 and 255.
     */
    virtual std::tuple< unsigned int, unsigned int, unsigned int > determineColor( unsigned int iteration ) = 0;
};


#endif //MANDELBROT_MANDELBROT_H
