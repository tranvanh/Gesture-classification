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

	std::vector<double> max_scaler = { 180.   , 179.999, 180.   , 179.996, 179.995, 179.999, 179.989,
	   180.   , 179.991, 179.986, 579.577, 719.193, 570.106, 549.272,
	   778.684, 578.49 , 533.127, 791.146, 551.114, 543.578, 783.643,
	   520.983, 550.029, 762.745, 508.462, 519.313, 723.459, 526.573,
	   173.127, 162.605, 164.575 };
	std::vector<double> min_scaler = { 0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,
		  0.   ,    0.   ,    0.   ,    0.   , -591.369,    0.   ,
	   -297.27 , -627.313,    0.   , -315.328, -631.764,    0.   ,
	   -319.745, -617.919,    0.   , -313.954, -591.069,    0.   ,
	   -302.162, -538.871,    0.   , -282.183,    0.   ,    0.   ,
		  0. };
	double min_max_scaler(const double& input, const int& k);
	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand, int& i);

	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);
	double internalAngle(const VECT& a, const VECT& b);

};