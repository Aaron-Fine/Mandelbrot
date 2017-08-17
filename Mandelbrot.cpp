//
// Created by finea on 8/10/2017.
//

#include "Mandelbrot.h"
#include <fstream>
#include <sstream>
#include <iomanip>

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
}

void Mandelbrot::saveTo( const std::string& outputFile )
{
    std::ofstream fout( outputFile );
    std::stringstream fileData;

    // Header for PPM file.
    fileData << "P3\n" <<
             config.getWidth() << " " << config.getHeight() << "\n" <<
             maxColorValue << "\n";

    unsigned int red, green, blue;

    const int COL_WIDTH = 4;

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
}

unsigned int Mandelbrot::getEscapeCount( double x0, double y0 )
{
    double x = 0.0;
    double y = 0.0;
    unsigned int iteration = 0;

    while ( x * x + y * y < 4 && iteration < config.getMaxIterations())
    {
        double temp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = temp;
        ++iteration;
    }

    return iteration;
}

std::tuple< unsigned int, unsigned int, unsigned int > Mandelbrot::determineColor( unsigned int iteration )
{
    return std::make_tuple( iteration % maxColorValue,
                            iteration % maxColorValue,
                            iteration % maxColorValue );
}

void Mandelbrot::outputIterations( const std::string& outputFile )
{
    std::ofstream fout( outputFile );

    for ( unsigned int row = 0; row < config.getHeight(); ++row )
    {
        for ( unsigned int col = 0; col < config.getWidth(); ++col )
        {
            fout << std::setw( 5 ) << iterMap[ row ][ col ] << ", ";
        }
        fout << "\n";
    }
}

void Mandelbrot::iterationHistogram(const std::string &outputFile) {
    std::ofstream fout( outputFile );

    std::string out;
    int histogram[config.getMaxIterations()]{0};


    for ( unsigned int row = 0; row < config.getHeight(); ++row )
    {
        for ( unsigned int col = 0; col < config.getWidth(); ++col )
        {
            histogram[iterMap[row][col]]++;
        }
    }

    for (int i = 0; i < config.getMaxIterations(); ++i) {
        out += std::to_string(i);
        out += ", ";
        out += std::to_string(histogram[i]);
        out += "\n";
    }

    fout << out;
}
