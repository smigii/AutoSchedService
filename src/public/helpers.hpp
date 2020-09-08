#include <iostream>
#include <vector>

#include "src/classes/Employee.hpp"
#include "src/classes/Manpower.hpp"
#include "src/classes/EmpWrapper.hpp"
#include "src/classes/Schedule.hpp"

void print_emps_info(const std::vector<Employee>& vec_emps){
	std::cout << "EMPLOYEE INFO\n\n";
	for(size_t i = 0; i < vec_emps.size(); i++){
		std::cout << vec_emps.at(i);
		std::cout << "\n";
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

void print_emps_shifts(const std::vector<Employee>& vec_emps){
	std::cout << "EMPLOYEE SHIFTS\n\n";
	
	// For all employees in employee vector
	for(size_t e = 0; e < vec_emps.size(); e++){
		std::cout << "Employee : " << vec_emps.at(e).get_name() << "\n";

		// For all days in shift vector
		for(size_t d = 0; d < 7; d++){
			std::cout << "Day " << d << " : ";

			// For all shifts in day
			for(size_t s = 0; s < vec_emps.at(e).get_avail(d).size(); s++){
				std::cout << vec_emps.at(e).get_avail(d).at(s) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

void print_default_manpower(std::vector<Manpower>& vec_manp){
	std::cout << "MANPOWER LIST\n\n";
	for(size_t i = 0; i < vec_manp.size(); i++){
		vec_manp.at(i).print_data();
		std::cout << "\n";
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

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
