//
// Created by finea on 8/10/2017.
//

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#include "Configuration.h"

class Mandelbrot
{
private:
    Configuration config;
    unsigned int** iterMap;
    unsigned int height;
    unsigned int width;
    double pixelWidth;
    double pixelHeight;
    double xMin, xMax, yMin, yMax;
    unsigned int maxIterations;

public:
    explicit Mandelbrot( Configuration configuration );

    ~Mandelbrot();

    void generate();

    void save()
    {
        saveTo( config.getParamAsString( "filename" ));
    }

    void saveTo( std::string outputFile );

private:
    unsigned int inSet(double x0, double y0);

    std::tuple<unsigned int, unsigned int, unsigned int> determineColor(unsigned int iteration);
};


#endif //MANDELBROT_MANDELBROT_H
