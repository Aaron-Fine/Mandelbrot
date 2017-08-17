#include <iostream>
#include <fstream>
#include <chrono>

#include "Utils.h"
#include "Mandelbrot.h"
#include "LinearColoring.h"
#include "BernsteinContinuous.h"

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
        default:
        {
            mandelbrot = new Mandelbrot( *config );
        }
    }

    std::chrono::time_point<std::chrono::system_clock> beforeGenerate, afterGenerate, afterSave;

    beforeGenerate = std::chrono::system_clock::now();
    mandelbrot->generate();
    afterGenerate = std::chrono::system_clock::now();

    mandelbrot->save();
    afterSave = std::chrono::system_clock::now();

    std::chrono::duration<double> generationTime = afterGenerate-beforeGenerate;
    std::chrono::duration<double> saveTime = afterSave-afterGenerate;
    std::chrono::duration<double> totalTime = afterSave-beforeGenerate;

    std::cout << "Total time      : " << totalTime.count() << "s\n";
    std::cout << "Generation time : " << generationTime.count() << "s\n";
    std::cout << "Saving time     : " << saveTime.count() << "s\n";

//    mandelbrot->outputIterations("debug.csv");

    std::cout << "Generated Mandelbrot!\nFile saved to " << config->getFileName() << std::endl;
    return 0;
}

