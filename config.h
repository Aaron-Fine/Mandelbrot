//
// Created by finea on 8/8/2017.
//

#ifndef MANDELBROT_CONFIG_H
#define MANDELBROT_CONFIG_H

#include <string>

class config
{
private:
    int width;
    int height;
    double xComplexMin;
    double xComplexMax;
    double yComplexMin;
    double yComplexMax;
    int maxIterations;
    std::string fileName;
public:
    int getWidth() const;

    void setWidth( int width );

    int getHeight() const;

    void setHeight( int height );

    double getXComplexMin() const;

    void setXComplexMin( double xComplexMin );

    double getXComplexMax() const;

    void setXComplexMax( double xComplexMax );

    double getYComplexMin() const;

    void setYComplexMin( double yComplexMin );

    double getYComplexMax() const;

    void setYComplexMax( double yComplexMax );

    int getMaxIterations() const;

    void setMaxIterations( int maxIterations );

    const std::string& getFileName() const;

    void setFileName( const std::string& fileName );

    config();

    explicit config( std::string& filename );

    config( int width, int height,
            double xmin, double xmax,
            double ymin, double ymax,
            int iterations, std::string& filename );

private:

    void readConfigFile( std::string& inputFileName );
};


#endif //MANDELBROT_CONFIG_H
