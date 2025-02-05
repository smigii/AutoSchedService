#include "Employee.hpp"

#include <iostream>

Employee::Employee(unsigned int id, std::string name, std::string role, bool closer, int max_h, int min_h, int max_d, int min_d, unsigned int pri)
    : id{id}, name{name}, role{role}, closer{closer}, max_h{max_h}, min_h{min_h}, max_d{max_d}, min_d{min_d}, priority{pri}
{
	avail.resize(7);
    std::cout << "EMP CONSTRUCTOR called for " << this->name << std::endl;
}

Employee::Employee(const Employee &emp)
    :id{emp.id}, name{emp.name}, role{emp.role}, closer{emp.closer}, max_h{emp.max_h}, min_h{emp.min_h}, max_d{emp.max_d}, min_d{emp.min_d}, avail{emp.avail}, vec_toff{emp.vec_toff}, priority{emp.priority}
{
    std::cout << "EMP COPY CONSTRUCTOR called for " << this->name << std::endl;
}
Employee::Employee(Employee &&emp)
    :id{emp.id}, name{emp.name}, role{emp.role}, closer{emp.closer}, max_h{emp.max_h}, min_h{emp.min_h}, max_d{emp.max_d}, min_d{emp.min_d}, avail{emp.avail}, vec_toff{emp.vec_toff}, priority{emp.priority}
{
    avail = emp.avail; // i dont think this needs to be here but im a lazy coward so here it stays
    std::cout << "EMP MOVE CONSTRUCTOR called for " << this->name << std::endl;

}
Employee::~Employee(){
    std::cout << "EMP DESTRUCTOR called for " << this->name << std::endl;
}

Employee& Employee::operator=(Employee &&emp){
    id = emp.id;
    priority = emp.priority;
    name = emp.name;
    role = emp.role;
    closer = emp.closer;
    min_d = emp.min_d;
    max_d = emp.max_d;
    min_h = emp.min_h;
    max_h = emp.max_h;
    avail = emp.avail;
    vec_toff = emp.vec_toff;
    return *this;
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
void Employee::set_id(unsigned int ID){
    id = ID;
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

unsigned int Employee::get_priority(){
    return priority;
}
void Employee::set_priority(unsigned int p){
    priority = p;
}

std::vector<float> Employee::get_avail(int day) const{
	return avail.at(day);
}
std::vector<std::vector<float>> Employee::get_avail() const{
    return avail;
}

void Employee::set_avail(int day, std::vector<float> vec){
	avail.at(day) = vec;
}
void Employee::set_avail(int day, int shift, float val){
    avail.at(day).at(shift) = val;
}

// TEMPORARY
int Employee::get_role_idx() const{
    if(role == "Sales"){
        return 0;
    } else {
        return 1;
    }
}

int Employee::get_vectoff_size() const{
    return vec_toff.size();
}
TimeOff* Employee::get_toff(int i) {
    return &vec_toff.at(i);
}
TimeOff Employee::get_toff_const(int i) const{
    return vec_toff.at(i);
}
void Employee::add_timeoff(TimeOff timeoff){
    vec_toff.push_back(timeoff);
}
