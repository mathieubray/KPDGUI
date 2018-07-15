#include "KPDGUIRNG.h"


RNG::RNG() {

	setSeed(1); // Could set seed according to random time
}

RNG::~RNG() {

}

void RNG::setSeed(int s) {

	if (s == 0)	// Cannot allow seed to be 0;
		seed = 1;
	else
		seed = s;
}

int RNG::getSeed() {

	return seed;
}

/* If this is working properly, starting with seed = 1,
the 10,000th call produces seed = 1043618065 */

double RNG::runif() {

	int k = seed / RAND_Q;
	seed = RAND_A * (seed - k* RAND_Q) - k * RAND_R;
	if (seed < 0)
		seed += RAND_M;
	return seed * (double)RAND_SCALE;
}

double RNG::runif(double l, double u) {

	return l + (u - l)*runif();
}

double RNG::rexp(double lambda) {

	return -log(runif()) / lambda;
}