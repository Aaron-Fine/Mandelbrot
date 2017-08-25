release: main.cpp
	g++-7 -std=c++11 -O3 -Wall -Wextra -Werror -o./release main.cpp MandelConfig.h MandelConfig.cpp Utils.h Utils.cpp Mandelbrot.cpp Mandelbrot.h LinearColoring.h BernsteinContinuous.h Greyscale.h
