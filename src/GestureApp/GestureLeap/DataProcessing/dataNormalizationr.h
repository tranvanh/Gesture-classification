#pragma once
#include<list>
#include<vector>
#include <LeapC.h>
#include <math.h>

#define PI 3.14159265

class DataNormalization {
public:
	DataNormalization(const int& t, const int& f) :timeStep(t), num_feature(f), max_scaler(31, INT_MIN), min_scaler(31, INT_MAX) {};
	void scale(const std::list<LEAP_TRACKING_EVENT>& window, std::vector<float>& normalized_data);
private:
	struct VECT {
		float x;
		float y;
		float z;
	};

	int timeStep;
	int num_feature;

	std::vector<double> max_scaler;/* = { 178.82447815, 178.68522644, 178.87007141, 179.13853455,
		179.99966431, 179.32290649, 179.25852966, 179.37113953,
		179.11717224, 179.99990845, 102.35218811, 68.1058197,
		74.4382019, 72.96920776, 53.61629486, 49.72146988,
		91.41898346, 91.91094971, 48.68366241, 42.18313599,
		37.23873901, 32.60449219, 49.24077606, 83.5871582,
		90.51228333, 87.90242004, 72.41075134, 39.21500397,
		179.85594177, 65.999281, 65.999658 };*/
	std::vector<double> min_scaler; /*{ 9.13711243e+01, 9.14782333e+01, 9.10166931e+01, 9.16859894e+01,
		1.36218796e+02, 1.14113815e+02, 1.17786926e+02, 1.18640160e+02,
		1.07567940e+02, 1.02479424e+02, -1.04593124e+02, -7.95619431e+01,
		-8.50401077e+01, -7.63436203e+01, -4.99267502e+01, -3.33724442e+01,
		-7.83166046e+01, -8.03939819e+01, -6.81694641e+01, -5.89657745e+01,
		-5.15626526e+01, -3.59300079e+01, -1.05577988e+02, -5.57399712e+01,
		-5.52091370e+01, -4.97175941e+01, -3.99056091e+01, -3.35596466e+01,
		4.14714928e+01, 1.00000000e-05, 2.10000000e-05 };*/

	void min_max_scaler(const std::vector<std::vector<double>> input, std::vector<float>& output);
	void calculate_features(std::vector<double>& output, const LEAP_TRACKING_EVENT& frame);

	VECT lineFromPoint(const LEAP_VECTOR &a, const LEAP_VECTOR &b);
	double internalAngle(const VECT& a, const VECT& b);
	void fitScaler(const std::vector<double> &data);

};