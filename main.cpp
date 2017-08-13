#include <iostream>
#include <fstream>
#include <exception>

#include "Mandelbrot.h"
#include "Configuration.h"

// Prototypes
Configuration readFile( const std::string& filename );

int main( int numArgs, char* args[] )
{
    std::string fileName;
    if ( numArgs < 2 )
    {
        std::cout << "Config Filename: ";
        std::cin >> fileName;
    } else
    {
        fileName = args[ 2 ];
    }

    Mandelbrot mandelbrot( readFile( fileName ));
    mandelbrot.generate();
    mandelbrot.save();

    std::cout << "Generated Mandelbrot!\nFile saved to " << fileName << std::endl;
    return 0;
}

Configuration readFile( const std::string& filename )
{
    std::ifstream fin( filename );

    if ( !fin )
    {
        throw std::out_of_range("Cannot read from file");
    }

    Configuration configuration;

    unsigned int width, height;
    double xComplexMin, xComplexMax;
    double yComplexMin, yComplexMax;
    unsigned int maxIterations;
    std::string outputFileName;

    fin >> width >> height;
    fin >> xComplexMin >> xComplexMax;
    fin >> yComplexMin >> yComplexMax;
    fin >> maxIterations;
    fin >> outputFileName;

    configuration.addParameter("height", std::to_string(height));
    configuration.addParameter("width", std::to_string(width));
    configuration.addParameter("x Complex Min", std::to_string(xComplexMin));
    configuration.addParameter("x Complex Max", std::to_string(xComplexMax));
    configuration.addParameter("y Complex Min", std::to_string(yComplexMin));
    configuration.addParameter("y Complex Max", std::to_string(yComplexMax));
    configuration.addParameter("iterations", std::to_string(maxIterations));

    fin.close();
    return Configuration();
}