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

	std::vector<double> max_scaler = { 180.        , 179.99999233, 180.        , 179.99998317,
	   179.99994529, 179.999     , 179.99997165, 180.        ,
	   179.99994445, 179.99998066, 404.416     , 719.193     ,
	   570.106     , 433.43      , 778.684     , 578.49      ,
	   423.871     , 791.146     , 551.114     , 433.991     ,
	   783.643     , 520.983     , 443.729     , 762.745     ,
	   508.462     , 383.431     , 723.459     , 526.573     ,
	   179.78636976, 179.25331623, 179.54454478 };
	std::vector<double> min_scaler = { 0.        ,    0.        ,    0.        ,    0.        ,
		  0.        ,    0.        ,    0.        ,    0.        ,
		  0.        ,    0.        , -424.721     ,   -0.62510592,
	   -297.27      , -420.951     ,   -0.61272847, -315.328     ,
	   -448.325     ,   -0.6184431 , -317.749     , -446.258     ,
		 -0.637595  , -313.954     , -457.886     ,   -0.64347916,
	   -302.162     , -442.757     ,   -0.64174975, -282.183     ,
		  0.        ,    0.        ,    0. };
	double min_max_scaler(const double& input, const int& k);
	void calculate_features(std::vector<double>& output, const LEAP_HAND& hand, int& i);

	VECT lineFromPoint(const LEAP_VECTOR& a, const LEAP_VECTOR& b);
	double internalAngle(const VECT& a, const VECT& b);

};