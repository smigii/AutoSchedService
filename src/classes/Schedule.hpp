#ifndef __SCHEDULE__
#define __SCHEDULE__

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <utility>

#include "Employee.hpp"
#include "Manpower.hpp"
#include "EmpWrapper.hpp"

class Schedule
{
	private:
		
		std::vector<Empwrapper> vec_empwrappers;
		std::vector<EmpSortWrapper> vec_empsort;

		std::vector<std::vector<float>> vec_spl;
		std::vector<std::vector<int>> vec_shiftcnt;

	public:
		Schedule();

		void clear();
		void setup(const std::vector<Employee>& vec_emps, const std::vector<Manpower>& vec_manp);
		void create(const std::vector<Manpower>& vec_manp);
		void set_closers();

		void print_spls();
		void print_empspls();
		void print_schedule();
};

#endif