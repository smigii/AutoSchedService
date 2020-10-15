#ifndef __MANPOWER__
#define __MANPOWER__

//#include <iostream>
#include <string>
#include <vector>

class Manpower
{
	private:

		std::string role;
		
		std::vector<std::vector<int>> data;

	public:
		
		Manpower(std::string role);

		std::string get_role();

		void print_data();
		void set_data(int day, std::vector<int> vec);
        int get_shift_val(int day, int shift) const;        // Will be replaced by get_shift_min or max

        int get_shift_min(int day, int shift) const;
        int get_shift_max(int day, int shift) const;

		int get_num_shifts(int day) const;
};


#endif
