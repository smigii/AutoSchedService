#include "Employee.hpp"

Employee::Employee(unsigned int id, std::string name, std::string role, bool closer, int max_h, int min_h, int max_d, int min_d)
: id{id}, name{name}, role{role}, closer{closer}, max_h{max_h}, min_h{min_h}, max_d{max_d}, min_d{min_d}
{
	avail.resize(7);
}

std::ostream &operator<<(std::ostream &output, const Employee &Emp){ 
	output << "  Name : " << Emp.name << "\n"
		   << "    ID : " << Emp.id << "\n"
		   << "  Role : " << Emp.role << "\n"
		   << "Closer : " << Emp.closer << "\n"
		   << " Hours : " << Emp.min_h << " - " << Emp.max_h << "\n"
		   << "Shifts : " << Emp.min_d << " - " << Emp.max_d << "\n";
	return output;            
}

unsigned int Employee::get_id() const{
	return id;
}

bool Employee::is_closer() const{
	return closer;
}
void Employee::set_closer(bool b){
	closer = b;
}

std::string Employee::get_name() const{
	return name;
}
void Employee::set_name(std::string n){
	name = n;
}

std::string Employee::get_role() const{
	return role;
}
void Employee::set_role(std::string r){
	role = r;
}

int Employee::get_days_max() const{
	return max_d;
}
int Employee::get_days_min() const{
	return min_d;
}
int Employee::get_hours_max() const{
    return max_h;
}
int Employee::get_hours_min() const{
    return min_h;
}

void Employee::set_days_min(int i){
	min_d = i;
}
void Employee::set_days_max(int i){
	max_d = i;
}
void Employee::set_hours_min(int i){
	min_h = i;
}
void Employee::set_hours_max(int i){
	max_h = i;
}

std::vector<float> Employee::get_avail(int day) const{
	return avail.at(day);
}

void Employee::set_avail(int day, std::vector<float> vec){
	avail.at(day) = vec;
}
