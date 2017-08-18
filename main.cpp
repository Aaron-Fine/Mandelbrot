#include <iostream>
#include <fstream>
#include <chrono>

#include "Utils.h"
#include "Mandelbrot.h"
#include "LinearColoring.h"
#include "BernsteinContinuous.h"
#include "Greyscale.h"

int main( int numArgs, char* args[] )
{
    std::string fileName;
    MandelConfig* config;
    Mandelbrot* mandelbrot;

    if ( numArgs < 1 )
    {
        config = new MandelConfig();
    } else
    {
        fileName = args[ 1 ];
        config = new MandelConfig( fileName );
    }

    std::cout << "Choose coloring scheme by entering integer associated with desired option:\n";
    std::cout << "0) Default\n";
    std::cout << "1) Linear (default coloring)\n";
    std::cout << "2) Linear (custom coloring)\n";
    std::cout << "3) Bernstein Continuous (default coloring)\n";
    std::cout << "4) Bernstein Continuous (custom coloring)\n";
    std::string choice;
    std::cin >> choice;

    switch ( convertStringToUnsignedInt( choice ))
    {
        case 1:
        {
            mandelbrot = new LinearColoring( *config, 255, 255, 102, 102, 0, 0 );
            break;
        }
        case 2:
        {
            std::string red1, green1, blue1;
            std::string red2, green2, blue2;

            std::cout << "Please enter RGB triplets between 0 and 255\nFirst Color: ";
            std::cin >> red1 >> green1 >> blue1;
            std::cout << "Second Color: ";
            std::cin >> red2 >> green2 >> blue2;
            mandelbrot = new LinearColoring( *config,
                                             convertStringToInt( red1 ),
                                             convertStringToInt( green1 ),
                                             convertStringToInt( blue1 ),
                                             convertStringToInt( red2 ),
                                             convertStringToInt( green2 ),
                                             convertStringToInt( blue2 ));
            break;
        }
        case 3:
        {
            mandelbrot = new BernsteinContinuous( *config );
            break;
        }
        case 4:
        {
            std::string red, green, blue;
            std::cout << "Please enter positive floats for the red, green, and blue color curve coefficents:\n";
            std::cout << "Red  :";
            std::cin >> red;
            std::cout << "Green:";
            std::cin >> green;
            std::cout << "Blue :";
            std::cin >> blue;

            mandelbrot = new BernsteinContinuous( *config,
                                                  convertStringToDouble( red ),
                                                  convertStringToDouble( green ),
                                                  convertStringToDouble( blue ));
            break;
        }
        default:
        {
            mandelbrot = new Greyscale( *config );
        }
    }

    mandelbrot->generate();
    mandelbrot->save();

//    mandelbrot->outputIterations("debug.csv");
//    mandelbrot->iterationHistogram("iterationHistogram.csv");


    return 0;
}

