//
// Created by finea on 8/17/2017.
//

#ifndef MANDELBROT_GREYSCALE_H
#define MANDELBROT_GREYSCALE_H

#include "Mandelbrot.h"

class Greyscale : public Mandelbrot
{
public:

    explicit Greyscale( const MandelConfig& initConfig ) : Mandelbrot( initConfig )
    {
        // Empty
    }

private:

    std::tuple< unsigned int, unsigned int, unsigned int > determineColor( unsigned int iteration ) override
    {
        return std::make_tuple( iteration % maxColorValue,
                                iteration % maxColorValue,
                                iteration % maxColorValue );
    }
};

#endif //MANDELBROT_GREYSCALE_H
