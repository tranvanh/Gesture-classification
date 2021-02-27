//
// Created by sran on 27.02.21.
//

#ifndef APP_GESTURES_CMODELWRAPPER_H
#define APP_GESTURES_CMODELWRAPPER_H

#include <iostream>
#include <vector>
#include "../include/cppflow/ops.h"
#include "../include/cppflow/model.h"

class CModelWrapper {
private:
    cppflow::model model;
public:
    CModelWrapper(const std::string &model_dir):model(model_dir){};
    int preditct(const std::vector<float> input_data);
};


#endif //APP_GESTURES_CMODELWRAPPER_H
