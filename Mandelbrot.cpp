//
// Created by finea on 8/10/2017.
//

#include "Mandelbrot.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <chrono>

Mandelbrot::Mandelbrot( const MandelConfig& initConfig ) :
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
    std::cout << "Starting Mandelbrot Generation" << std::endl;
    auto beforeGenerate = std::chrono::system_clock::now();
    double x0;
    double y0;

    for ( unsigned int row = 0; row < config.getHeight(); ++row )
    {
        for ( unsigned int col = 0; col < config.getWidth(); ++col )
        {
            x0 = config.getXComplexMin() + col * config.getPixelWidth();
            y0 = config.getYComplexMin() + row * config.getPixelHeight();
            iterMap[ row ][ col ] = getEscapeCount( x0, y0 );
        }
    }

    std::chrono::duration< double > generationTime = std::chrono::system_clock::now() - beforeGenerate;
    std::cout << "Generation time : " << generationTime.count() << "s\n";
}

void Mandelbrot::saveTo( const std::string& outputFile )
{
    auto beforeSave = std::chrono::system_clock::now();
    std::ofstream fout( outputFile );
    std::stringstream fileData;

    // Header for PPM file.
    fileData << "P3\n" <<
             config.getWidth() << " " << config.getHeight() << "\n" <<
             maxColorValue << "\n";

    unsigned int red, green, blue;

    auto COL_WIDTH = static_cast<unsigned int>(std::to_string( maxColorValue ).length() + 1);

    for ( unsigned int row = 0; row < config.getHeight(); ++row )
    {
        for ( unsigned int col = 0; col < config.getWidth(); ++col )
        {
            std::tie( red, green, blue ) = determineColor( iterMap[ row ][ col ] );
            fileData <<
                     std::setw( COL_WIDTH ) << red <<
                     std::setw( COL_WIDTH ) << green <<
                     std::setw( COL_WIDTH ) << blue << "  ";
        }
        fileData << "\n";
    }

    fout << fileData.str();
    fout.close();

    std::chrono::duration< double > saveTime = std::chrono::system_clock::now() - beforeSave;
    std::cout << "Saving time     : " << saveTime.count() << "s\n";
    std::cout << "Generated Mandelbrot!\nFile saved to " << outputFile << std::endl;
}

unsigned int Mandelbrot::getEscapeCount( double x0, double y0 )
{
    double x = 0.0;
    double y = 0.0;
    unsigned int iteration = 0;

    double xtemp;
    double ytemp;

    while ( x * x + y * y < 4 && iteration < config.getMaxIterations())
    {
        xtemp = x * x - y * y + x0;
        ytemp = 2 * x * y + y0;

        // Periodicity checking. If we get into a loop we know we will be in the set.
        // See https://en.wikipedia.org/wiki/Mandelbrot_set#Periodicity_checking
        // NOTE: This is slower so far...
//        if (x == xtemp && y == ytemp)
//        {
//            iteration = config.getMaxIterations();
//            break;
//        }

        x = xtemp;
        y = ytemp;
        ++iteration;
    }

    return iteration;
}

void Mandelbrot::outputIterations( const std::string& outputFile )
{
    std::ofstream fout( outputFile );

    std::stringstream out;
    for ( unsigned int row = 0; row < config.getHeight(); ++row )
    {
        for ( unsigned int col = 0; col < config.getWidth(); ++col )
        {
            out << std::setw( 5 ) << iterMap[ row ][ col ] << ", ";
        }
        out << "\n";
    }

    fout << out.str();
    fout.close();
}

void Mandelbrot::iterationHistogram( const std::string& outputFile )
{
    std::ofstream fout( outputFile );

    std::stringstream out;
    int histogram[config.getMaxIterations()]{ 0 };

    for ( unsigned int row = 0; row < config.getHeight(); ++row )
    {
        for ( unsigned int col = 0; col < config.getWidth(); ++col )
        {
            histogram[ iterMap[ row ][ col ]]++;
        }
    }

    for ( int i = 0; i < config.getMaxIterations(); ++i )
    {
        out << std::to_string( i ) << ", " << std::to_string( histogram[ i ] ) << "\n";
    }

    fout << out.str();
    fout.close();
}
