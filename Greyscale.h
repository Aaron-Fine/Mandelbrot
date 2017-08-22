//
// Created by finea on 8/17/2017.
//

#ifndef MANDELBROT_GREYSCALE_H
#define MANDELBROT_GREYSCALE_H

#include "Mandelbrot.h"

class Greyscale : public Mandelbrot
{
    /**
     * Super basic greyscale coloring for the fractal.
     */
public:

    /**
     * Basic Generator
     * @param initConfig This is an object that contains all of the configuration options for a mandelbrot.
     * This tells the generator what to generate.
     */
    explicit Greyscale( const MandelConfig& initConfig ) : Mandelbrot( initConfig )
    {
        // Empty
    }

private:

    /**
     * Red, Green, and Blue values will be the same, resulting in a greyscale image.
     * @param iteration This is the escape time value for a particular pixel
     * @return Red, Green, Blue values between 0 and 255.
     */
    std::tuple< unsigned int, unsigned int, unsigned int > determineColor( unsigned int iteration ) override
    {
        return std::make_tuple( iteration % maxColorValue,
                                iteration % maxColorValue,
                                iteration % maxColorValue );
    }
};

#endif //MANDELBROT_GREYSCALE_H
