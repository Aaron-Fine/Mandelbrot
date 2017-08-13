//
// Created by finea on 8/10/2017.
//

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#include "MandelConfig.h"
#include <tuple>

class Mandelbrot
{
private:
    MandelConfig config;
    unsigned int** iterMap;

public:
    explicit Mandelbrot( const MandelConfig& initConfig );

    ~Mandelbrot();

    void generate();

    void save()
    {
        saveTo(config.getFileName());
    }

    void saveTo( const std::string& outputFile );

private:
    unsigned int inMandelbrotSet( double x0, double y0 );

    std::tuple<unsigned int, unsigned int, unsigned int> determineColor(unsigned int iteration);
};


#endif //MANDELBROT_MANDELBROT_H
