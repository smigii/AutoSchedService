#include <numeric>								// Used for std::accumulate()
#include <algorithm>							// Used for std::sort()

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "src/classes/Employee.hpp"
#include "src/classes/Manpower.hpp"
#include "src/classes/EmpWrapper.hpp"
#include "src/classes/Schedule.hpp"

/* 
SPL : Shift Priority Level. This value describes which shifts will be
	  hardest to fill, based on how many employees are available
	  to work a given shift and how many of the total employees are
	  needed for that shift. Obtained with...

	  spl = (# emps available) / (# emps available - # emps needed)

	  Higher SPL values receive higher priority, as they are the most
	  "demanding" shifts. The maximum SPL value is (total # of employees)+1.
	  The minimum SPL is 1, when no employees are needed for a certain shift.
	  
	  If the # of employees needed is equal to # of employees available, 
	  the value should be set to (total # of employees + 1). This will
	  make sure these days are the highest priority.
	  
	  Examples... (Assuming total # of employees = 8)
	   AVAIL :   6    6    6    6    2    8
	  NEEDED :   1    4    5    6    2    7
	     SPL :   1.2  3.0  6.0  9    9    8

EAS : Employee Availability Score. This value describes how easy/hard
	  it will be to assign the employee shifts. Employees who with 
	  limited schedules and availabilty will have a high EAS are
	  harder to schedule than those with low EAS. Obtained with...

	  (Total # of shifts / # of available shifts) * (MAX NUMBER OF DAYS (5) / # of available days)

EmpSPL : Employee Shift Priority Level. This takes into account the given 
		 week's SPL levels and the given Employee's EAS, and returns a 
		 value which describes which of the employees available shifts
		 should be assigned first. EmpSPL is simply...

		 (Employee's vector of shifts) * (EAS)

		 When we combine all the EmpSPL vecotrs of all the emplyees, 
		 we get a matrix of EmpSPLs that tell us which unique Employee
		 and shift combination should be assigned first.

Generally, for loops here will use d, s and e for indices.
	d : day of week
	s : shift number
	e : index of employee vector
*/

void create_schedule(const std::vector<Employee>& vec_emps, 
					 const std::vector<Manpower>& vec_manp,
					 Schedule& schedule){

	schedule.clear();
	schedule.setup(vec_emps, vec_manp);
	schedule.set_closers();
	schedule.create(vec_manp);
}
