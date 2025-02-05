#include "Schedule.hpp"

#include <algorithm>

#include "src/public/time_conv.hpp"

Schedule::Schedule()
{
    num_roles = 0;
}

// d = day
// s = shift
// r = role

const Employee* Schedule::get_employee(int e){
    return vec_empwrappers.at(e).empptr;
}
Empwrapper* Schedule::get_empwrapper(int e){
    return &vec_empwrappers.at(e);
}
void Schedule::set_emp(int e, int d, int s, std::string shift){
    int r = vec_empwrappers.at(e).empptr->get_role_idx();
    if(shift != "OFF"){
        vec_empwrappers.at(e).daycnt++;
        vec_shiftcnt.at(r).at(d).at(s)++;
    }

    vec_empwrappers.at(e).vec_assigned_days.at(d) = true;
    vec_empwrappers.at(e).vec_shifts.at(d) = shift;
}

void Schedule::clear(){
	vec_empwrappers.clear();
	vec_empsort.clear();
	vec_spl.clear();
	vec_shiftcnt.clear();
    num_roles = 0;
}

void Schedule::setup(const std::vector<Employee>& vec_emps, const std::vector<Manpower>& vec_manp){
	// Set up EmpWrapper objects
	for(size_t i = 0; i < vec_emps.size(); i++){
		vec_empwrappers.push_back(Empwrapper( &vec_emps.at(i) ));
		vec_empwrappers.at(i).set_idx(i);
	}

	// Set SPLs

	// Get a tally of how many employees are available for each shift
	// of the week.

    // Cycle through all roles
    for(size_t r = 0; r < vec_manp.size(); r++){
        vec_spl.push_back(std::vector<std::vector<float>>());
        vec_shiftcnt.push_back(std::vector<std::vector<int>>());
        num_roles++;

        // Cycle through all days
        for(size_t d = 0; d < 7; d++){
            vec_spl.at(r).push_back(std::vector<float>());
            vec_shiftcnt.at(r).push_back(std::vector<int>());

            // Cycle through each shift of given day
            for(size_t s = 0; s < (size_t)vec_manp.at(r).get_num_shifts(d); s++){
                vec_spl.at(r).at(d).push_back(0);
                vec_shiftcnt.at(r).at(d).push_back(0);

                // Cycle through all employees and get the
                // availability of the given shift.
                for(size_t e = 0; e < vec_empwrappers.size(); e++){
                    if((size_t)vec_empwrappers.at(e).empptr->get_role_idx() == r)
                        vec_spl.at(r).at(d).at(s) += vec_empwrappers.at(e).vec_avail.at(d).at(s);
                }
            }
        }
    }

	// Next, use the info obtained above to calculate the SPL of each shift.
    // For each Role...
    for(size_t r = 0; r < num_roles; r++){
        // For each day...
        for(size_t d = 0; d < vec_spl.at(r).size(); d++){
            // For each shift...
            for(size_t s = 0; s < vec_spl.at(r).at(d).size(); s++){
                // Calculate the SPL using formula described in initial comment.
                float emp_avail = vec_spl.at(r).at(d).at(s);
                float emp_needed = vec_manp.at(r).get_shift_min(d,s);
                if(emp_avail != emp_needed){
                    vec_spl.at(r).at(d).at(s) = (emp_avail / (emp_avail - emp_needed));
                } else {
                    vec_spl.at(r).at(d).at(s) = vec_emps.size()+1;
                }
            }
        }
    }

	// Set EmpSPLs

	// Sets each Empwrapper object's EmpSPL vector. This can only be done 
	// after initializing SPLs, since those values are required for 
	// calculating EmpSPLs.
	for(size_t e = 0; e < vec_empwrappers.size(); e++){
		vec_empwrappers.at(e).set_empspl(vec_spl);
	}

	// Set vector housing all Employee-Shift combos then sort it
	for(size_t e = 0; e < vec_empwrappers.size(); e++){
		for(size_t d = 0; d < 7; d++){
			for(size_t s = 0; s < vec_empwrappers.at(e).vec_empspl.at(d).size(); s++){
				float val = vec_empwrappers.at(e).vec_empspl.at(d).at(s);
				if(val != 0){
					vec_empsort.push_back( EmpSortWrapper(&vec_empwrappers.at(e), val, d, s) );
				}
			}
		}
	}
	std::sort(vec_empsort.begin(), vec_empsort.end());
}

void Schedule::set_closers(){
	// Now we create the schedule using the Schedule object passed in.
	// We will cycle through the sorted vector which holds the employees
	// and their EmpSPL values.
	for(int i = vec_empsort.size()-1; i >= 0; i--){
		// Convenient temp var for holding the day in question
		int day = vec_empsort.at(i).day;
        int shift = vec_empsort.at(i).shift;
		// First, check if the employee is a closer and if anyone has been assigned that shift yet.
		// Since this is being called first, none of the shifts should have anyone assigned yet, so
		// this will work (i hope)
        int role_idx = vec_empsort.at(i).empwptr->empptr->get_role_idx();
        if(vec_empsort.at(i).empwptr->empptr->is_closer() && vec_shiftcnt.at(role_idx).at(day).at(shift) == 0){
			// Then, check if the employee has exceeded their max number of
			// days worked.
			if(vec_empsort.at(i).empwptr->daycnt < vec_empsort.at(i).empwptr->empptr->get_days_max()){
                // Next, check if the day has already been added for the employee.
                // This check prevents the program from overwriting already
                // assigned days with lower priority shifts.
                if(vec_empsort.at(i).empwptr->vec_assigned_days.at(day) == false){
                    // Name of employee
                    std::string name = vec_empsort.at(i).empwptr->empptr->get_name();
                    // Which shift is being assigned
                    int shift_num = vec_empsort.at(i).shift;
                    // Converting numeric calue to pretty string
                    std::string start = float_to_time(vec_empsort.at(i).empwptr->empptr->get_avail(day).at(2*shift_num));
                    std::string end = float_to_time(vec_empsort.at(i).empwptr->empptr->get_avail(day).at(2*shift_num+1));
                    std::string shift_string = start + "-" + end;
                    // Setting the day and incrementing necessary values
                    vec_empsort.at(i).inc_daycnt();
                    vec_empsort.at(i).empwptr->vec_assigned_days.at(day) = true;
                    vec_empsort.at(i).empwptr->vec_shifts.at(day) = shift_string;
                    vec_shiftcnt.at(role_idx).at(day).at(shift)++;
                }
			}	
		}
	}
}

void Schedule::create(const std::vector<Manpower>& vec_manp){
	// Now we create the schedule using the Schedule object passed in.
	// We will cycle through the sorted vector which holds the employees
	// and their EmpSPL values.

    // Pass 1 : Set only minimum amount of employees to satisfy Manpower requirements
    // Pass 2 : Fill in other employees to meet their preferred amount of shifts.

    static int pass = 1;

	for(int i = vec_empsort.size()-1; i >= 0; i--){
		// First, check if the employee has exceeded their max number of
		// days worked.
		if(vec_empsort.at(i).empwptr->daycnt < vec_empsort.at(i).empwptr->empptr->get_days_max()){
			// Convenient temp var for holding the day in question
			int day = vec_empsort.at(i).day;
			int shift = vec_empsort.at(i).shift;
            int role_idx = vec_empsort.at(i).empwptr->empptr->get_role_idx();

            int pass_check = (pass == 1) ? vec_manp.at(role_idx).get_shift_min(day,shift) : vec_manp.at(role_idx).get_shift_max(day,shift);

            if(vec_shiftcnt.at(role_idx).at(day).at(shift) < pass_check ){
				// Next, check if the day has already been added for the employee.
				// This check prevents the program from overwriting already 
				// assigned days with lower priority shifts.
				if(vec_empsort.at(i).empwptr->vec_assigned_days.at(day) == false){
					// Name of employee
					std::string name = vec_empsort.at(i).empwptr->empptr->get_name();
					// Which shift is being assigned
					int shift_num = vec_empsort.at(i).shift;
                    // Converting numeric value to pretty string
                    std::string start = float_to_time(vec_empsort.at(i).empwptr->empptr->get_avail(day).at(2*shift_num));
                    std::string end = float_to_time(vec_empsort.at(i).empwptr->empptr->get_avail(day).at(2*shift_num+1));
					std::string shift_string = start + "-" + end;
					// Setting the day and incrementing necessary values
					vec_empsort.at(i).inc_daycnt();
					vec_empsort.at(i).empwptr->vec_assigned_days.at(day) = true;
					vec_empsort.at(i).empwptr->vec_shifts.at(day) = shift_string;
                    vec_shiftcnt.at(role_idx).at(day).at(shift)++;
				}
			}
		}
	}
    print_schedule();
    if(pass == 1){
        pass++;
        create(vec_manp);
    } else {
        pass = 1;
    }
}

void Schedule::print_spls(){
	std::cout << "SPLs...\n";
    for(size_t r = 0; r < num_roles; r++){
        std::cout << "ROLE : " << r << "\n";
        for(size_t d = 0; d < vec_spl.at(r).size(); d++){
            std::cout << "Day " << d << " : ";
            for(size_t s = 0; s < vec_spl.at(r).at(d).size(); s++){
                std::cout << vec_spl.at(r).at(d).at(s) << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
}

void Schedule::print_empspls(){
	// // for printing
	for(size_t e = 0; e < vec_empwrappers.size(); e++){

		std::cout << "Emp " << vec_empwrappers.at(e).empptr->get_name() << 
		" | EAS : " << vec_empwrappers.at(e).eas << "\n";

		for(size_t d = 0; d < 7; d++){
			std::cout << "Day " << d << " : ";

			for(size_t s = 0; s < vec_empwrappers.at(e).vec_empspl.at(d).size(); s++){
				std::cout << std::setw(5) << std::setprecision(3) << vec_empwrappers.at(e).vec_empspl.at(d).at(s) << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
	}

	for(size_t i = 0; i < vec_empsort.size(); i++){
		std::cout << vec_empsort.at(i).empwptr->empptr->get_name() << " : ";
		std::cout << vec_empsort.at(i).value << "\n";
	}

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
}

void Schedule::print_schedule(){
	std::cout << "SCHEDULE\n\n";

    std::cout << std::setw(16) << ""
			  << std::setw(12) << "Sun"
			  << std::setw(12) << "Mon"
			  << std::setw(12) << "Tue"
			  << std::setw(12) << "Wed"
			  << std::setw(12) << "Thu"
			  << std::setw(12) << "Fri"
			  << std::setw(12) << "Sat\n";

	for(size_t e = 0; e < vec_empwrappers.size(); e++){
        std::cout << std::setw(13) << vec_empwrappers.at(e).empptr->get_name() << " : ";

		for(size_t d = 0; d < 7; d++){
			std:: cout << std::setw(11) << vec_empwrappers.at(e).vec_shifts.at(d) << "|";
		}
		std::cout << "\n";
	}
    std::cout << std::endl;
}
void Schedule::print_shiftcnt(){
    for(size_t r = 0; r < num_roles; r++){
        for(size_t d = 0; d < vec_shiftcnt.size(); d++){
            for(size_t s = 0; s < vec_shiftcnt.at(r).at(d).size(); s++){
                std::cout << vec_shiftcnt.at(r).at(d).at(s) << " ";
            }
            std::cout << std::endl;
        }
    }
}

void Schedule::swap_empw(int idxa, int idxb){
    std::swap(vec_empwrappers.at(idxa), vec_empwrappers.at(idxb));
}

size_t Schedule::get_empwvec_size(){
    return vec_empwrappers.size();
}

std::string Schedule::get_emp_shift(size_t e, size_t d){
    return vec_empwrappers.at(e).vec_shifts.at(d);
}

void Schedule::set_timeoffs(int d){
    for(size_t e = 0; e < vec_empwrappers.size(); e++){
        for(int t = 0; t < vec_empwrappers.at(e).empptr->get_vectoff_size(); t++){
            std::cout << vec_empwrappers.at(e).empptr->get_toff_const(t);
        }
    }
    std::cout << std::endl;
}
