#pragma once
#include<list>
#include<vector>
#include <LeapC.h>
#include <math.h>
#include <iostream>

#define PI 3.14159265

/** Preprocess data **/
class DataNormalization {
public:
	DataNormalization(): timeStep(0), num_feature(0) {};
	DataNormalization(const int& t, const int& f, const std::vector<double> &min_s, const std::vector<double> &max_s) :
		timeStep(t), num_feature(f), min_scaler(min_s), max_scaler(max_s) {};

	/** Start processcing **/
	void scale(const std::list<LEAP_HAND>& window, std::vector<double>& normalized_data);
private:
	struct VECT {
		double x;
		double y;
		double z;
	};

	int timeStep;
	int num_feature;

	std::vector<double> min_scaler;
	std::vector<double> max_scaler;

	/** Perform MinMax scaling **/
	double min_max_scaler(const double& input, const int& k);

	/** Calculate hand features **/
	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand, int& i);

	/** Compute vectors from given two points **/
	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);

	/** Compute internal angle of given two vectors **/
	double internalAngle(const VECT& a, const VECT& b);

};