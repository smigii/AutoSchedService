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

	return(std::to_string(hr) + ":" + std::to_string(min));
}
