//
// Created by finea on 8/15/2017.
//

#ifndef MANDELBROT_LINEARCOLORING_H
#define MANDELBROT_LINEARCOLORING_H

#include "Mandelbrot.h"

struct Color
{
    int red = 0;
    int green = 0;
    int blue = 0;
};

class LinearColoring : public Mandelbrot
{
private:
    Color colorOne;
    Color colorTwo;

public:
    explicit LinearColoring( const MandelConfig& initConfig, Color firstColor, Color lastColor ) :
            Mandelbrot( initConfig ), colorOne( firstColor ), colorTwo( lastColor )
    {
        // Empty
    }

    explicit LinearColoring( const MandelConfig& initConfig,
                             int firstRed, int firstGreen, int firstBlue,
                             int secondRed, int secondGreen, int secondBlue ) :
            Mandelbrot( initConfig )
    {
        colorOne.red = firstRed;
        colorOne.green = firstGreen;
        colorOne.blue = firstBlue;

        colorTwo.red = secondRed;
        colorTwo.green = secondGreen;
        colorTwo.blue = secondBlue;
    }

    std::tuple< unsigned int, unsigned int, unsigned int > determineColor( unsigned int iteration ) override
    {
        double redDelta = (( colorTwo.red - colorOne.red ) * iteration ) /
                          static_cast<double>(config.getMaxIterations());

        double greenDelta = (( colorTwo.green - colorOne.green ) * iteration ) /
                            static_cast<double>(config.getMaxIterations());

        double blueDelta = (( colorTwo.blue - colorOne.blue ) * iteration ) /
                           static_cast<double>(config.getMaxIterations());


        std::tuple< unsigned int, unsigned int, unsigned int > result( colorOne.red + redDelta,
                                                                       colorOne.green + greenDelta,
                                                                       colorOne.blue + blueDelta );
        return result;
    }
};

#endif //MANDELBROT_LINEARCOLORING_H
