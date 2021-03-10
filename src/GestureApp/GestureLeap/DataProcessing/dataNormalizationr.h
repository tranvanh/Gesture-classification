#pragma once
#include<list>
#include<vector>
#include <LeapC.h>
#include <math.h>
#include <iostream>

#define PI 3.14159265

class DataNormalization {
public:
	DataNormalization(const int& t, const int& f) :timeStep(t), num_feature(f) {};
	void scale(const std::list<LEAP_HAND>& window, std::vector<double>& normalized_data);
private:
	struct VECT {
		double x;
		double y;
		double z;
	};

	int timeStep;
	int num_feature;

	std::vector<double> max_scaler = { 179.999, 179.998, 180.   , 179.997, 179.995, 179.997, 179.973,
	   180.   , 179.979, 179.938, 562.126, 701.2  , 533.133, 580.836,
	   721.897, 545.729, 579.616, 722.18 , 546.661, 579.62 , 727.649,
	   503.163, 594.318, 743.124, 508.462, 510.422, 722.803, 501.416,
	   173.127, 162.605, 164.575 };
	std::vector<double> min_scaler = { 9.50955e+01,  8.99999e+01,  9.00456e+01,  9.00456e+01,
		9.00455e+01,  6.54812e+01,  2.57840e+01,  3.11686e+01,
		2.83181e+01,  2.04904e+01, -4.65014e+02,  6.15573e+01,
	   -2.90505e+02, -4.80121e+02,  3.30287e+01, -3.15328e+02,
	   -4.71490e+02,  2.19222e+01, -3.17749e+02, -4.59829e+02,
		3.47366e+01, -3.13954e+02, -4.57886e+02,  1.45195e+01,
	   -3.02162e+02, -4.42757e+02,  7.13368e+01, -2.82183e+02,
		4.41342e-02,  4.25457e-02,  4.19405e-02 };
	double min_max_scaler(const double& input, const int& k);
	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand, int& i);

	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);
	double internalAngle(const VECT& a, const VECT& b);

};