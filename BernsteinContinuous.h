//
// Created by finea on 8/17/2017.
//

#ifndef MANDELBROT_BERNSTEINCONTINUOUS_H
#define MANDELBROT_BERNSTEINCONTINUOUS_H

#include "Mandelbrot.h"

class BernsteinContinuous : public Mandelbrot
{
    /**
     * A continuous, smooth, color algorithm based on Bernstein Polynomials.
     */
private:
    double redCoef;
    double grnCoel;
    double bluCoef;

public:

    /**
     * This is the typical constructor for this class. The default values produce a good looking image on all
     * inputs that have been tried.
     * @param initConfig This is an object that contains all of the configuration options for a mandelbrot.
     * This tells the generator what to generate.
     */
    explicit BernsteinContinuous( const MandelConfig& initConfig ) :
            Mandelbrot( initConfig ),
            redCoef( 9 ),
            grnCoel( 15 ),
            bluCoef( 8.5 )
    {
        // Empty
    }

    /**
     * If you want to play with the exact nature of the curves, use this constructor. WARNING output may be appear
     * corrupted with certain input values.
     * @param initConfig This is an object that contains all of the configuration options for a mandelbrot.
     * This tells the generator what to generate.
     * @param redCoefficent Governs the "height" of the color values for Red. Recommend max of ~9.48.
     * @param greenCoefficent Governs the "height" of the color values for Green. Recommend max of ~16.00.
     * @param blueCoefficent Governs the "height" of the color values for Blue. Recommend max of ~9.48.
     */
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
    /**
     * The three functions used here (one each for red, green, and blue) map all of the iteration values between 0
     * and the max iteration value in the configuration and give you a color value between 0 and 255. As there are
     * three different curves, you will get different values for Red, Green, and Blue. The coefficents are from the
     * constructors. Plot the curves below at https://www.desmos.com/calculator to get a sense of what they are doing.
     * Red:   R(1-x)   * x^3
     * Green: G(1-x)^2 * x^2
     * Blue:  B(1-x)^3 * x
     * @param iterationSee getEscapeCount for details, but will be between 0 and the max allowed by the configuration
     * @return Red, Green, Blue values between 0 and 255.
     */
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
