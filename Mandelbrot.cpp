//
// Created by finea on 8/10/2017.
//

#include "Mandelbrot.h"

Mandelbrot::Mandelbrot( const MandelConfig& initConfig) :
        config( initConfig )
{
    iterMap = new unsigned int* [config.getHeight()];

    for ( unsigned int i = 0; i < config.getHeight(); ++i )
    {
        iterMap[ i ] = new unsigned int[config.getWidth()];
    }
}

Mandelbrot::~Mandelbrot()
{

    for ( unsigned int i = 0; i < config.getHeight(); ++i )
    {
        if ( iterMap[ i ] != nullptr )
        {
            delete iterMap[ i ];
        }
    }

    delete iterMap;

}

void Mandelbrot::generate()
{

}

void Mandelbrot::saveTo( const std::string& outputFile )
{

}

unsigned int Mandelbrot::inMandelbrotSet( double x0, double y0 )
{
    return 0;
}

std::tuple< unsigned int, unsigned int, unsigned int > Mandelbrot::determineColor( unsigned int iteration )
{
    std::tuple< unsigned int, unsigned int, unsigned int > result (0, 0, 0);
    return result;
}
