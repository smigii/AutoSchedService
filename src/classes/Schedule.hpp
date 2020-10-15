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

        std::vector<std::vector<std::vector<float>>> vec_spl;       // L1=Role, L2=Day, L3=SPLs
        std::vector<std::vector<std::vector<int>>> vec_shiftcnt;    // L1=Role, L2=Day, L3=Counts

	public:
		Schedule();

        const Employee* get_employee(int e);
        Empwrapper* get_empwrapper(int e);

		void clear();
		void setup(const std::vector<Employee>& vec_emps, const std::vector<Manpower>& vec_manp);
		void create(const std::vector<Manpower>& vec_manp);
		void set_closers();

        void set_emp(int e, int d, int s, std::string shift);

		void print_spls();
		void print_empspls();
		void print_schedule();
        void print_shiftcnt();

        void swap_empw(int idxa, int idxb);

        size_t get_empwvec_size();
        // Returns the shift in pretty string form
        std::string get_emp_shift(size_t e, size_t d);
};

#endif
