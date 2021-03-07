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

	std::vector<double> max_scaler = { 180.   , 179.998, 180.   , 179.996, 179.981, 179.999, 179.989,
	   180.   , 179.974, 179.938, 404.416, 719.193, 570.106, 433.43 ,
	   778.684, 578.49 , 420.316, 791.146, 551.114, 395.499, 783.643,
	   520.983, 389.52 , 762.745, 508.462, 383.431, 723.459, 526.573,
	   173.127, 162.605, 164.575 };
	std::vector<double> min_scaler = { 9.30245e+01,  8.99999e+01,  9.00456e+01,  9.00455e+01,
		9.00455e+01,  6.54812e+01,  2.57840e+01,  2.77705e+01,
		2.79286e+01,  2.04904e+01, -4.24721e+02,  6.97324e+01,
	   -2.97270e+02, -4.20951e+02,  5.95510e+01, -3.15328e+02,
	   -4.48325e+02,  6.33254e+01, -3.17749e+02, -4.46258e+02,
		8.67906e+01, -3.13954e+02, -4.57886e+02,  8.58241e+01,
	   -3.02162e+02, -4.42757e+02,  1.03148e+02, -2.82183e+02,
		1.86895e-01,  6.48663e-02,  1.07620e-01 };
	double min_max_scaler(const double& input, const int& k);
	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand, int& i);

	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);
	double internalAngle(const VECT& a, const VECT& b);

};