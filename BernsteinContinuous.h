//
// Created by finea on 8/17/2017.
//

#ifndef MANDELBROT_BERNSTEINCONTINUOUS_H
#define MANDELBROT_BERNSTEINCONTINUOUS_H

#include "Mandelbrot.h"

class BernsteinContinuous : public Mandelbrot
{
private:
    double redCoef;
    double grnCoel;
    double bluCoef;

public:
    explicit BernsteinContinuous( const MandelConfig& initConfig ) :
            Mandelbrot( initConfig ),
            redCoef( 9 ),
            grnCoel( 15 ),
            bluCoef( 8.5 )
    {
        // Empty
    }

    explicit BernsteinContinuous( const MandelConfig& initConfig,
                         double redCoefficent, double greenCoefficent, double blueCoefficent ) :
            Mandelbrot( initConfig ),
            redCoef( redCoefficent ),
            grnCoel( greenCoefficent ),
            bluCoef( blueCoefficent )
    {
        // Empty
    }

private:
    std::tuple< unsigned int, unsigned int, unsigned int > determineColor( unsigned int iteration ) override
    {
        // Adapted from https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/

        // map iterations to the 0..1 interval
        double t = iteration / static_cast<double>(config.getMaxIterations());

        // Use smooth polynomials for r, g, b
        return std::make_tuple(
                static_cast<unsigned int>(( redCoef * ( 1 - t ) * t * t * t * maxColorValue )),
                static_cast<unsigned int>(( grnCoel * ( 1 - t ) * ( 1 - t ) * t * t * maxColorValue )),
                static_cast<unsigned int>(( bluCoef * ( 1 - t ) * ( 1 - t ) * ( 1 - t ) * t * maxColorValue ))
        );
    }
};

#endif //MANDELBROT_BERNSTEINCONTINUOUS_H
