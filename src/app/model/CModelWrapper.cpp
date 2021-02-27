//
// Created by sran on 27.02.21.
//

#include "CModelWrapper.h"
int CModelWrapper::preditct(const std::vector<float> input_data){
    auto output = this->model(cppflow::tensor(input_data,{1,200,31}));
    auto values = output.get_data<float>();
    float glob_max = -1;
    int res = 0;
    for (int i = 0; i < values.size(); ++i) {
        res = values[i] > glob_max ? i : res;
        glob_max = values[i] > glob_max ? values[i] : glob_max;
    }
    return res;
}