#include <iostream>
#include <fstream>

#include "Mandelbrot.h"

// Prototypes

int main( int numArgs, char* args[] )
{
    std::string fileName;
    MandelConfig* config;

    if ( numArgs < 2 )
    {
        config = new MandelConfig();
    } else
    {
        fileName = args[ 2 ];
        config = new MandelConfig( fileName );
    }

    Mandelbrot mandelbrot( *config );
    mandelbrot.generate();
    mandelbrot.save();

    std::cout << "Generated Mandelbrot!\nFile saved to " << config->getFileName() << std::endl;
    return 0;
}

