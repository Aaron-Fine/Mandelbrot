//
// Created by finea on 8/8/2017.
//

#ifndef MANDELBROT_CONFIG_H
#define MANDELBROT_CONFIG_H

#include <string>

class MandelConfig
{
private:
    unsigned int width;
    unsigned int height;
    double xComplexMin;
    double xComplexMax;
    double yComplexMin;
    double yComplexMax;
    unsigned int maxIterations;
    std::string fileName;

public:
    unsigned int getWidth() const;

    unsigned int getHeight() const;

    double getXComplexMin() const;

    double getXComplexMax() const;

    double getYComplexMin() const;

    double getYComplexMax() const;

    unsigned int getMaxIterations() const;

    const std::string& getFileName() const;

    double getPixelWidth()
    {
        return ( xComplexMax - xComplexMin ) / width;
    }

    double getPixelHeight()
    {
        return ( yComplexMax - yComplexMin ) / height;
    }

    MandelConfig();

    explicit MandelConfig( std::string& filename );

    MandelConfig( unsigned int width, unsigned int height,
                  double xmin, double xmax,
                  double ymin, double ymax,
                  unsigned int iterations, std::string& filename );

private:

    void readConfigFile( std::string& inputFileName );

    void validate();
};


#endif //MANDELBROT_CONFIG_H
