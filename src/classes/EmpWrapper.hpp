#ifndef __EMPWRAPPER__
#define __EMPWRAPPER__

#include <vector>

#include "Employee.hpp"

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

struct Empwrapper{
	/* 
	This class is needed to facilitate creating a schedule. We need a
	counter for the assigned days and assigned hours of each session.
	We also need to convert the availability vector (Employee::avail)
	to something easier to work with, which is accomplished with 
	vec_avail and the constructor.

	    empptr : pointer to Employee object.
	 vec_avail : vecotr of availability from the Employee object,
	 		     converted to simple boolean form.
	vec_empspl : vector of Employee SPL scores
	*/

	const Employee* empptr;

	float eas;
	
	int daycnt;	// day counter
	int hrcnt;	// hour counter

	int sked_idx;	// index within Schedule object
	
	std::vector<std::vector<bool>> vec_avail;
	std::vector<std::vector<float>> vec_empspl;

	// Length = length of schedule, probably 7 days
	std::vector<bool> vec_assigned_days;
	std::vector<std::string> vec_shifts;

	Empwrapper(const Employee* empptr);

	// This can only be called AFTER the SPL vector is initialized, since it is
	// needed to calculate the EmpSPLs.
	void set_empspl(const std::vector<std::vector<float>>& vec_spl);
	void set_idx(int i);
	
};

struct EmpSortWrapper{
	/*
	This struct is needed for combining all the EmpSPLs together
	in one big vector. This way, we can sort the vector by largest
	EmpSPL values and then start assigning shifts by iterating 
	through the big boi vector.
	*/
	Empwrapper* empwptr;
	float value;
	int day;
	int shift;

	EmpSortWrapper(Empwrapper* empwptr, float value, int day, int shift);

	// This is needed by std::sort, we need some way of comparing 
	// each object.
	bool operator<(const EmpSortWrapper& ESW) const;

    void inc_daycnt();
};

#endif
