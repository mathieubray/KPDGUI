#ifndef _RNG_h
#define _RNG_h

#include <math.h>

class RNG{

private:
	int seed; //Default seed is 1, which will be initialized in the constructor function;

	int RAND_A;
	int RAND_M;
	int RAND_Q;
	int RAND_R;
	double RAND_SCALE;

public:
	RNG();
	~RNG();
	void setSeed(int s);				//s=0 is a bad choice;
	int getSeed();						//This will return a U(0,1) random variable;
	double runif();						//This will return a U(a,b) random variable;
	double runif(double l, double u);	//This will return an exponentially distributed random variable with hazard rate lambda;
	double rexp(double lambda);
};

#endif