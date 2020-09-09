#include "EmpWrapper.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <utility>

#include <numeric>								// Used for std::accumulate()
#include <algorithm>							// Used for std::sort()

Empwrapper::Empwrapper(const Employee* empptr)
	: empptr{empptr}, daycnt{0}, hrcnt{0}
	{
	// Loop through the employees availabilty vectors for each day
	// and determine whether or not an employee is available. 
	for(size_t d = 0; d < 7; d++){
		vec_avail.push_back(std::vector<bool>());
		// s increases by two since the data stored in Employee::avail
		// holds a start time and end time for each shift. We only need
		// to check one of those values to see if the employee is
		// available that day.
		for(size_t s = 0; s < empptr->get_avail(d).size(); s+=2){
			if(empptr->get_avail(d).at(s) == -1){
				// A value of -1 in Employee::avail means they are 
				// unavailable to work that shift.
				vec_avail.at(d).push_back(false);
			} else {
				// Any other value indicates they are free to work
				vec_avail.at(d).push_back(true);
			}
		}
	}

	// Set all days to not taken. Values will be changed to true as 
	// the schedule is made.
	for(size_t i = 0; i < 7; i++){
		vec_assigned_days.push_back(false);
		vec_shifts.push_back("");
	}

	// This will count how many shifts are possible (total_shifts) and how many 
	// the given Employee is available for (temp_score)
	float temp_score {0};
	float total_shifts {0};
	for(size_t i = 0; i < 7; i++){
		// since each available shift is stored as a 1 and each unavailable shift
		// is stored as a 0, we can simply take the sum of each day to speed up 
		// the process.
		temp_score += std::accumulate(vec_avail.at(i).begin(), vec_avail.at(i).end(), 0);
		total_shifts += vec_avail.at(i).size();
	}
	
	eas = (total_shifts / temp_score) * (5 / (float)empptr->get_days_max());
}

void Empwrapper::set_empspl(const std::vector<std::vector<float>>& vec_spl){
	for(size_t d = 0; d < vec_spl.size(); d++){
		vec_empspl.push_back(std::vector<float>());

		for(size_t s = 0; s < vec_spl.at(d).size(); s++){
			float empspl_score = (vec_avail.at(d).at(s) * vec_spl.at(d).at(s) * eas);
			vec_empspl.at(d).push_back(empspl_score);
		}
	}
}

void Empwrapper::set_idx(int i){
	sked_idx = i;
}

////////
////////
////////

EmpSortWrapper::EmpSortWrapper(Empwrapper* empwptr, float value, int day, int shift)
: empwptr{empwptr}, value{value}, day{day}, shift{shift}
{

}
// This is needed by std::sort, we need some way of comparing 
// each object.
bool EmpSortWrapper::operator<(const EmpSortWrapper& ESW) const{ 
    return value < ESW.value; 
}

void EmpSortWrapper::inc_daycnt(){
	empwptr->daycnt += 1;
}
