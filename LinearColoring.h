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
    /**
     * Calculates a color based on a linear interpolation gradient between two colors. The output
     * color is based on the relative location of that pixel along the calculated gradient.
     * Based on a 'Color Smoosh' assignment given in the Utah State University CS1 class.
     */
private:
    Color colorOne;
    Color colorTwo;

public:
    /**
     * As it is unlikely your program uses the above Color struct, you should probably not use this constructor
     * @param initConfig This is an object that contains all of the configuration options for a mandelbrot.
     * This tells the generator what to generate.
     * @param firstColor Struct containing Red, Green, Blue values for the start of the gradient
     * @param lastColor Struct containing Red, Green, Blue values for the end of the gradient
     */
    explicit LinearColoring( const MandelConfig& initConfig, Color firstColor, Color lastColor ) :
            Mandelbrot( initConfig ), colorOne( firstColor ), colorTwo( lastColor )
    {
        // Empty
    }

    /**
     *
     * @param initConfig This is an object that contains all of the configuration options for a mandelbrot.
     * This tells the generator what to generate.
     * @param firstRed Red value for start of color gradient. Must be between 0 and 255.
     * @param firstGreen Green value for start of color gradient. Must be between 0 and 255.
     * @param firstBlue Blue value for start of color gradient. Must be between 0 and 255.
     * @param secondRed Red value for end of color gradient. Must be between 0 and 255.
     * @param secondGreen Green value for end of color gradient. Must be between 0 and 255.
     * @param secondBlue Blue value for end of color gradient. Must be between 0 and 255.
     */
    explicit LinearColoring( const MandelConfig& initConfig,
                             int firstRed, int firstGreen, int firstBlue,
                             int secondRed, int secondGreen, int secondBlue ) :
            Mandelbrot( initConfig )
    {
        colorOne.red = rangeCheck(firstRed);
        colorOne.green = rangeCheck(firstGreen);
        colorOne.blue = rangeCheck(firstBlue);

        colorTwo.red = rangeCheck(secondRed);
        colorTwo.green = rangeCheck(secondGreen);
        colorTwo.blue = rangeCheck(secondBlue);
    }

private:
    /**
     * Basically, think of a gradient between the two colors given in the constructors with maxIteration possible
     * colors between the two. The function finds the particular color associated with the iteration given.
     * @param iteration See getEscapeCount for details, but will be between 0 and the max allowed by the configuration
     * @return Red, Green, Blue values between 0 and 255.
     */
    std::tuple< unsigned int, unsigned int, unsigned int > determineColor( unsigned int iteration ) override
    {
        double redDelta = (static_cast<double>( colorTwo.red - colorOne.red ) * iteration ) /
                          static_cast<double>(config.getMaxIterations());

        double greenDelta = (static_cast<double>( colorTwo.green - colorOne.green ) * iteration ) /
                            static_cast<double>(config.getMaxIterations());

        double blueDelta = (static_cast<double>( colorTwo.blue - colorOne.blue ) * iteration ) /
                           static_cast<double>(config.getMaxIterations());


        std::tuple< unsigned int, unsigned int, unsigned int > result( colorOne.red + redDelta,
                                                                       colorOne.green + greenDelta,
                                                                       colorOne.blue + blueDelta );
        return result;
    }

    /**
     * Input validation for colors. If colors are out of range, it crops the values to be within range.
     * @param input Input color value
     * @return Output color value between 0 and 255
     */
    int rangeCheck(int input)
    {
        if (input < 0) return 0;
        if (input > 255) return 255;
        return input;
    }
};

#endif //MANDELBROT_LINEARCOLORING_H
