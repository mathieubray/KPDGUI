
#ifndef RNG_H
#define RNG_H

#include <math.h>

/* This uses a portable implementation for generating U(0,1) due to Schrage */
#define RAND_A 16807
#define RAND_M 2147483647
#define RAND_Q 127773
#define RAND_R 2836
#define RAND_SCALE (1.0 / RAND_M)

class RNG {

private:
	int seed; //Default seed is 1, which will be initialized in the constructor function;

public:
	RNG();
	~RNG();
	void setSeed(int s);				// s=0 is a bad choice;
	int getSeed();						// This will return a U(0,1) random variable;
	double runif();						// This will return a U(a,b) random variable;
	double runif(double l, double u);	// This will return an exponentially distributed random variable with hazard rate lambda;
	double rexp(double lambda);

};

#endif