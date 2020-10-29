#ifndef __LD_JSON__
#define __LD_JSON__

#include <fstream>

#include <iostream>
#include <string>
#include <vector>

#include "src/classes/Employee.hpp"
#include "src/classes/Manpower.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

void load_employees(std::vector<Employee>& vec_emps){
    #ifdef _WIN32
        std::ifstream ifs("..\\AutoSchedService\\src\\public\\json\\employees.json");
    #endif

    #ifdef __gnu_linux__
        std::ifstream ifs("../AutoSchedService/src/public/json/employees.json");
    #endif


	json jsong;
	ifs >> jsong;

    unsigned int id {0};

	for(auto& element : jsong){

		auto jname = element.find("name");
		auto jcloser = element.find("closer");
		auto jrole = element.find("role");
        auto jpri = element.find("priority");

		auto jmax_h = element.find("max_hours");
		auto jmax_d = element.find("max_days");
		auto jmin_h = element.find("min_hours");
		auto jmin_d = element.find("min_days");

        vec_emps.push_back(Employee(id, *jname, *jrole, *jcloser, *jmax_h, *jmin_h, *jmax_d, *jmin_d, *jpri));

        vec_emps.at(id).set_avail(0, *(element.find("sun")));
        vec_emps.at(id).set_avail(1, *(element.find("mon")));
        vec_emps.at(id).set_avail(2, *(element.find("tue")));
        vec_emps.at(id).set_avail(3, *(element.find("wed")));
        vec_emps.at(id).set_avail(4, *(element.find("thu")));
        vec_emps.at(id).set_avail(5, *(element.find("fri")));
        vec_emps.at(id).set_avail(6, *(element.find("sat")));

        id++;
	}
    ifs.close();
}

void save_employees(std::vector<Employee>& vec_emps){
    #ifdef _WIN32
        std::ofstream ofs("..\\AutoSchedService\\src\\public\\json\\employees.json");
    #endif

    #ifdef __gnu_linux__
        std::ofstream ofs("../AutoSchedService/src/public/json/employees.json");
    #endif

    nlohmann::ordered_json jsong = nlohmann::ordered_json::array();

    for(size_t e = 0; e < vec_emps.size(); e++){
        jsong[e]["name"] = vec_emps.at(e).get_name();
        jsong[e]["closer"] = vec_emps.at(e).is_closer();
        jsong[e]["role"] = vec_emps.at(e).get_role();
        jsong[e]["priority"] = vec_emps.at(e).get_priority();

        jsong[e]["max_hours"] = vec_emps.at(e).get_hours_max();
        jsong[e]["max_days"] = vec_emps.at(e).get_days_max();
        jsong[e]["min_hours"] = vec_emps.at(e).get_hours_min();
        jsong[e]["min_days"] = vec_emps.at(e).get_days_min();

        jsong[e]["sun"] = vec_emps.at(e).get_avail(0);
        jsong[e]["mon"] = vec_emps.at(e).get_avail(1);
        jsong[e]["tue"] = vec_emps.at(e).get_avail(2);
        jsong[e]["wed"] = vec_emps.at(e).get_avail(3);
        jsong[e]["thu"] = vec_emps.at(e).get_avail(4);
        jsong[e]["fri"] = vec_emps.at(e).get_avail(5);
        jsong[e]["sat"] = vec_emps.at(e).get_avail(6);
    }
    ofs << jsong.dump(4);
    std::cout << "JSON emp written." << std::endl;
    ofs.close();
}

void load_manpower(std::vector<Manpower>& vec_manp){
    #ifdef _WIN32
        std::ifstream ifs("..\\AutoSchedService\\src\\public\\json\\manpower.json");
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
    ifs.close();
}

void save_manpower(std::vector<Manpower>& vec_manp){
    #ifdef _WIN32
        std::ofstream ofs("..\\AutoSchedService\\src\\public\\json\\manpower.json");
    #endif

    #ifdef __gnu_linux__
        std::ofstream ofs("../AutoSchedService/src/public/json/manpower.json");
    #endif

    nlohmann::ordered_json jsong = nlohmann::ordered_json::array();

    for(size_t m = 0; m < vec_manp.size(); m++){
        jsong[m]["role"] = vec_manp.at(m).get_role();

        jsong[m]["sun"] = vec_manp.at(m).get_shifts_day(0);
        jsong[m]["mon"] = vec_manp.at(m).get_shifts_day(1);
        jsong[m]["tue"] = vec_manp.at(m).get_shifts_day(2);
        jsong[m]["wed"] = vec_manp.at(m).get_shifts_day(3);
        jsong[m]["thu"] = vec_manp.at(m).get_shifts_day(4);
        jsong[m]["fri"] = vec_manp.at(m).get_shifts_day(5);
        jsong[m]["sat"] = vec_manp.at(m).get_shifts_day(6);
    }
    ofs << jsong.dump(4);
    std::cout << "JSON manp written." << std::endl;

    ofs.close();
}

#endif
