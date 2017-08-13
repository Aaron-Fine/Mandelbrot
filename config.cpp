//
// Created by finea on 8/8/2017.
//

#include "config.h"

#include <fstream>
#include <stdexcept>

int config::getWidth() const
{
    return width;
}

void config::setWidth( int width )
{
    if ( width <= 0 )
    {
        width = 1;
    }
    config::width = width;
}

int config::getHeight() const
{
    return height;
}

void config::setHeight( int height )
{
    if ( height <= 0 )
    {
        height = 1;
    }
    config::height = height;
}

double config::getXComplexMin() const
{
    return xComplexMin;
}

void config::setXComplexMin( double xComplexMin )
{
    if ( xComplexMin < -2.0 )
    {
        xComplexMin = -2.0;
    } else if ( xComplexMin > 0.5 )
    {
        xComplexMin = 0.5;
    }
    config::xComplexMin = xComplexMin;
}

double config::getXComplexMax() const
{
    return xComplexMax;
}

void config::setXComplexMax( double xComplexMax )
{
    if ( xComplexMax < -2.0 )
    {
        xComplexMax = -2.0;
    } else if ( xComplexMax > 0.5 )
    {
        xComplexMax = 0.5;
    }
    config::xComplexMax = xComplexMax;
}

double config::getYComplexMin() const
{
    return yComplexMin;
}

void config::setYComplexMin( double yComplexMin )
{
    if ( yComplexMin < -1.25 )
    {
        yComplexMin = -1.25;
    } else if ( yComplexMin > 1.25 )
    {
        yComplexMin = 1.25;
    }
    config::yComplexMin = yComplexMin;
}

double config::getYComplexMax() const
{
    return yComplexMax;
}

void config::setYComplexMax( double yComplexMax )
{
    if ( yComplexMax < -1.25 )
    {
        yComplexMax = -1.25;
    } else if ( yComplexMax > 1.25 )
    {
        yComplexMax = 1.25;
    }
    config::yComplexMax = yComplexMax;
}

int config::getMaxIterations() const
{
    return maxIterations;
}

void config::setMaxIterations( int maxIterations )
{
    if ( maxIterations < 1 )
    {
        maxIterations = 1;
    }
    config::maxIterations = maxIterations;
}

const std::string& config::getFileName() const
{
    return fileName;
}

void config::setFileName( const std::string& fileName )
{
    config::fileName = fileName;
}

config::config() :
        width( 512 ), height( 512 ),
        xComplexMin( -2.0 ), xComplexMax( 0.5 ),
        yComplexMin( -1.25 ), yComplexMax( 1.25 ),
        maxIterations( 80 ), fileName( "output.ppm" )
{
    // Empty
}


config::config( std::string& filename ) :
        width( 0 ), height( 0 ),
        xComplexMin( 0.0 ), xComplexMax( 0.0 ),
        yComplexMin( 0.0 ), yComplexMax( 0.0 ),
        maxIterations( 1 ), fileName( "" )
{
    readConfigFile( filename );
}

config::config( int width, int height, double xmin, double xmax, double ymin, double ymax, int iterations,
                std::string& filename ) :
        width( width ), height( height ),
        xComplexMin( xmin ), xComplexMax( xmax ),
        yComplexMin( ymin ), yComplexMax( ymax ),
        maxIterations( iterations ), fileName( filename )
{
    // Empty
}

void config::readConfigFile( std::string& inputFileName )
{
    std::ifstream fin( inputFileName );

    if ( !fin )
    {
        throw std::invalid_argument( "Cannot read from file" );
    }

    fin >> width >> height;
    fin >> xComplexMin >> xComplexMax;
    fin >> yComplexMin >> yComplexMax;
    fin >> maxIterations;
    fin >> fileName;

    fin.close();
}
