#include "Model.h"

void Model::min_max_scaler(std::vector<float>& output, const std::vector<std::vector<float>> input)
{
    int ix = 0;
    for (int i = 0; i < this->num_timestep; ++i)
        for (int k = 0; k < this->num_features; ++k, ++ix)
            output[ix] = float(input[i][k] - min_scaler[k]) / (max_scaler[k] - min_scaler[k]);
}

int Model::preditct(const std::vector<std::vector<float>> input_data) {
    std::vector<float> scaled_input_data(this->num_timestep * this->num_features);
    this->min_max_scaler(scaled_input_data, input_data);
    auto output = this->model(cppflow::tensor(scaled_input_data, { 1,this->num_timestep,this->num_features }));
    auto values = output.get_data<float>();
    float glob_max = -1;
    int res = 0;
    for (int i = 0; i < values.size(); ++i) {
        res = values[i] > glob_max ? i : res;
        glob_max = values[i] > glob_max ? values[i] : glob_max;
    }
    return res;
}