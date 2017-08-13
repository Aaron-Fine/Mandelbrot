//
// Created by finea on 8/10/2017.
//

#include "Mandelbrot.h"

#include <utility>

Mandelbrot::Mandelbrot( Configuration configuration ) :
        config( std::move( configuration ))
{
    height = unsigned( config.getParamAsInt( "height" ));
    width = unsigned( config.getParamAsInt( "width" ));
    xMin = config.getParamAsDouble("x Complex Min");
    xMax = config.getParamAsDouble("x Complex Max");
    yMin = config.getParamAsDouble("y Complex Min");
    yMax = config.getParamAsDouble("y Complex Max");
    maxIterations = unsigned(config.getParamAsInt("iterations"));

    pixelWidth = (xMax - xMin) / width;
    pixelHeight = (yMax - yMin) / height;

    iterMap = new unsigned int* [height];

    for ( unsigned int i = 0; i < height; ++i )
    {
        iterMap[ i ] = new unsigned int[width];
    }
}

Mandelbrot::~Mandelbrot()
{

    for ( unsigned int i = 0; i < height; ++i )
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

void Mandelbrot::saveTo( std::string outputFile )
{

}

unsigned int Mandelbrot::inSet( double x0, double y0 )
{
    return 0;
}

std::tuple< unsigned int, unsigned int, unsigned int > Mandelbrot::determineColor( unsigned int iteration )
{
    return {0, 0, 0};
}
