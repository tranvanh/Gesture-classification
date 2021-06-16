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
	DataNormalization(const int& t, const int& f) :timeStep(t), num_feature(f) {};

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

	std::vector<double> max_scaler = { 180.   , 180.   , 180.   , 179.999, 179.991, 180.   , 179.983,
	   180.   , 179.985, 179.985, 539.053, 468.363, 720.07 , 581.654,
	   522.811, 709.384, 585.01 , 508.522, 705.543, 567.779, 478.013,
	   702.861, 544.45 , 478.722, 693.173, 499.893, 466.308, 707.228,
	   127.401, 161.082, 127.977 };
	std::vector<double> min_scaler = { 0.    ,    0.    ,    0.    ,    0.    ,    0.    ,    0.    ,
		  0.    ,    0.    ,    0.    ,    0.    , -591.101 ,  -12.7777,
	   -190.142 , -626.233 ,    0.    , -238.535 , -648.629 ,    0.    ,
	   -251.495 , -643.156 ,    0.    , -243.005 , -675.481 ,    0.    ,
	   -220.466 , -607.075 ,    0.    , -158.459 ,    0.    ,    0.    ,
		  0. };
	/** Perform MinMax scaling **/
	double min_max_scaler(const double& input, const int& k);

	/** Calculate hand features **/
	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand, int& i);

	/** Compute vectors from given two points **/
	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);

	/** Compute internal angle of given two vectors **/
	double internalAngle(const VECT& a, const VECT& b);

};