#include <fstream>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "src/classes/Employee.hpp"
#include "src/classes/Manpower.hpp"
#include "src/classes/EmpWrapper.hpp"
#include "src/classes/Schedule.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;



void load_employees(std::vector<Employee>& vec_emps){
    // IF WIN

    // IF NIX
    #ifdef _WIN32
        std::ifstream ifs("D:\\Code\\projects\\AutoSchedServiceQT\\AutoSchedService\\src\\public\\json\\employees.json");
    #endif

    #ifdef __gnu_linux__
        std::ifstream ifs("../AutoSchedService/src/public/json/employees.json");
    #endif


	json jsong;
	ifs >> jsong;

    unsigned int id {0};

	for(auto& element : jsong){

		auto jname = element.find("name");
//		auto jid = element.find("id");
		auto jcloser = element.find("closer");
		auto jrole = element.find("role");

		auto jmax_h = element.find("max_hours");
		auto jmax_d = element.find("max_days");
		auto jmin_h = element.find("min_hours");
		auto jmin_d = element.find("min_days");

        Employee temp(id, *jname, *jrole, *jcloser,
			*jmax_h, *jmin_h, *jmax_d, *jmin_d);

		temp.set_avail(0, *(element.find("sun")));
		temp.set_avail(1, *(element.find("mon")));
		temp.set_avail(2, *(element.find("tue")));
		temp.set_avail(3, *(element.find("wed")));
		temp.set_avail(4, *(element.find("thu")));
		temp.set_avail(5, *(element.find("fri")));
		temp.set_avail(6, *(element.find("sat")));

		vec_emps.push_back(temp);
        id++;
	}
}

void load_manpower(std::vector<Manpower>& vec_manp){
    #ifdef _WIN32
        std::ifstream ifs("D:\\Code\\projects\\AutoSchedServiceQT\\AutoSchedService\\src\\public\\json\\manpower.json");
    #endif
    #ifdef __gnu_linux__
        std::ifstream ifs("../AutoSchedService/src/public/json/manpower.json");
    #endif
    json jsong;
	ifs >> jsong;

	for(auto& element : jsong){

		auto jrole = element.find("role");

		Manpower temp(*jrole);

		temp.set_data(0, *(element.find("sun")));
		temp.set_data(1, *(element.find("mon")));
		temp.set_data(2, *(element.find("tue")));
		temp.set_data(3, *(element.find("wed")));
		temp.set_data(4, *(element.find("thu")));
		temp.set_data(5, *(element.find("fri")));
		temp.set_data(6, *(element.find("sat")));

		vec_manp.push_back(temp);
	}
}
