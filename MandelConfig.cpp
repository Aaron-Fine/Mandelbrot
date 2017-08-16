//
// Created by finea on 8/8/2017.
//

#include "MandelConfig.h"

#include <fstream>
#include <iostream>

unsigned int MandelConfig::getWidth() const
{
    return width;
}


unsigned int MandelConfig::getHeight() const
{
    return height;
}


double MandelConfig::getXComplexMin() const
{
    return xComplexMin;
}


double MandelConfig::getXComplexMax() const
{
    return xComplexMax;
}


double MandelConfig::getYComplexMin() const
{
    return yComplexMin;
}


double MandelConfig::getYComplexMax() const
{
    return yComplexMax;
}


unsigned int MandelConfig::getMaxIterations() const
{
    return maxIterations;
}


const std::string& MandelConfig::getFileName() const
{
    return fileName;
}


MandelConfig::MandelConfig() :
        width( 512 ), height( 512 ),
        xComplexMin( -2.0 ), xComplexMax( 0.5 ),
        yComplexMin( -1.25 ), yComplexMax( 1.25 ),
        maxIterations( 80 ), fileName( "output.ppm" )
{
    // Empty
}


MandelConfig::MandelConfig( std::string& filename ) :
        width( 0 ), height( 0 ),
        xComplexMin( 0.0 ), xComplexMax( 0.0 ),
        yComplexMin( 0.0 ), yComplexMax( 0.0 ),
        maxIterations( 1 ), fileName( "" )
{
    readConfigFile( filename );
    validate();
}

MandelConfig::MandelConfig( unsigned int width, unsigned int height,
                            double xmin, double xmax,
                            double ymin, double ymax,
                            unsigned int iterations,
                            std::string& filename ) :
        width( width ), height( height ),
        xComplexMin( xmin ), xComplexMax( xmax ),
        yComplexMin( ymin ), yComplexMax( ymax ),
        maxIterations( iterations ), fileName( filename )
{
    validate();
}

void MandelConfig::readConfigFile( std::string& inputFileName )
{
    std::ifstream fin( inputFileName );

    if ( !fin )
    {
        std::cout << "Cannot read from file. Exiting now.\n";
        exit( EXIT_FAILURE );
    }

    fin >> width >> height;
    fin >> xComplexMin >> xComplexMax;
    fin >> yComplexMin >> yComplexMax;
    fin >> maxIterations;
    fin >> fileName;

    fin.close();
}

void MandelConfig::validate()
{
    if ( width < 1 ) width = 1;
    if ( height < 1 ) height = 1;
    if ( xComplexMin < -2.0 ) xComplexMin = -2.0;
    if ( xComplexMax > 0.5 ) xComplexMax = 0.5;
    if ( yComplexMin < -1.25 ) yComplexMax = -1.25;
    if ( yComplexMax > 1.25 ) yComplexMax = 1.25;
    if ( maxIterations < 1 ) maxIterations = 1;
    if ( fileName.empty()) fileName = "output.ppm";
}
