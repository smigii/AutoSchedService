#include "Manpower.hpp"

Manpower::Manpower(std::string role)
: role{role}
{
	data.resize(7);
}

std::string Manpower::get_role(){
	return role;
}

void Manpower::print_data(){
	std::cout << "Manpower for role [" << role << "]\n";
	for(size_t i = 0; i < data.size(); i++){
		std::cout << "Day " << i << " : ";
		for(size_t j = 0; j < data.at(i).size(); j++){
			std::cout << data.at(i).at(j) << " ";
		}
		std::cout << "\n";
	}
}

void Manpower::set_data(int day, std::vector<int> vec){
	data.at(day) = vec;
}

int Manpower::get_shift_val(int day, int shift) const{
	return(data.at(day).at(shift));
}

int Manpower::get_num_shifts(int day) const{
	return(data.at(day).size());
}