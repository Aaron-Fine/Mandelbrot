//
// Created by finea on 8/10/2017.
//

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#include "MandelConfig.h"
#include <tuple>

class Mandelbrot
{
protected:
    MandelConfig config;
    unsigned int** iterMap;
    unsigned int maxColorValue = 255;

public:
    explicit Mandelbrot( const MandelConfig& initConfig );

    ~Mandelbrot();

    void generate();

    void save()
    {
        saveTo( config.getFileName());
    }

    void saveTo( const std::string& outputFile );

    void outputIterations( const std::string& outputFile );
    
    void iterationHistogram(const std::string& outputFile );

private:
    // TODO: Try looking into better escape count techniques from http://linas.org/art-gallery/escape/escape.html

    unsigned int getEscapeCount( double x0, double y0 );

    virtual std::tuple< unsigned int, unsigned int, unsigned int > determineColor( unsigned int iteration ) = 0;
};


#endif //MANDELBROT_MANDELBROT_H
