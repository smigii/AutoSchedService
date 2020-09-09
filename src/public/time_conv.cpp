#include "time_conv.hpp"

#include <iostream>

std::string float_to_time(float num){
    int hr = (int)num;
    int min = (int)((num-hr)*60);
    std::string min_str;
    if(min == 0){
        min_str = "00";
    } else {
        min_str = std::to_string(min);
    }

    return(std::to_string(hr) + ":" + min_str);
}

float time_to_float(std::string time){
    if(time == "OFF"){
        return -1;
    } else {
        std::string hr;
        std::string min;
        bool latch {true};
        for(size_t i = 0; i < time.size(); i++){
            if(time.at(i) == ':'){
                latch = false;
            } else if(latch){
                hr += time.at(i);
            } else {
                min += time.at(i);
            }
        }
        float hr_num = std::stoi(hr);
        if(min == "00"){
            return (float)hr_num;
        } else {
            float min_num = std::stoi(min);
            float time_num = hr_num + (min_num/60);
            return time_num;
        }
    }
}
