#include "TimeOff.hpp"

#include "src/public/time_conv.hpp"

#include <iostream>

TimeOff::TimeOff(std::string n, std::vector<int> start_d, std::vector<int> end_d, int start_s, int end_s, std::string desc)
    :name{n}, start_date{start_d}, end_date{end_d}, start_shift{start_s}, end_shift{end_s}, description{desc}
{
    set_label();
}
TimeOff::TimeOff(std::string n)
    :name{n}
{
    start_date = std::vector<int>{1, 1, 2000};
    end_date = std::vector<int>{1, 1, 2000};
    start_shift = 1;
    end_shift = 1;
    description = "Description.";
}
std::ostream &operator<<(std::ostream &output, const TimeOff &Toff){
    output << "     Name : " << Toff.name << "\n"
           << "Start Day : " << Toff.start_date.at(0) << "/" << Toff.start_date.at(1) << "/" << Toff.start_date.at(2) << "\n"
           << "  End Day : " << Toff.end_date.at(0) << "/" << Toff.end_date.at(1) << "/" << Toff.end_date.at(2) << "\n"
           << "   Shifts : " << Toff.start_shift << " " << Toff.end_shift << "\n\n";
    return output;
}

std::string TimeOff::get_name(){
    return name;
}
void TimeOff::set_name(std::string str){
    name = str;
}
std::string TimeOff::get_label(){
    set_label();
    return label;
}
void TimeOff::set_label(){
    std::string d1 = std::to_string(get_start_day());
    int m1 = get_start_month();
    std::string d2 = std::to_string(get_end_day());
    int m2 = get_end_month();
    label = int_to_month(m1) + " " + d1 + " - " + int_to_month(m2) + " " + d2;
}

int TimeOff::get_start_day() const{
    return start_date.at(0);
}
int TimeOff::get_start_month() const{
    return start_date.at(1);
}
int TimeOff::get_start_year() const{
    return start_date.at(2);
}
std::vector<int> TimeOff::get_start_date() const{
    return start_date;
}

int TimeOff::get_end_day() const{
    return end_date.at(0);
}
int TimeOff::get_end_month() const{
    return end_date.at(1);
}
int TimeOff::get_end_year() const{
    return end_date.at(2);
}
std::vector<int> TimeOff::get_end_date() const{
    return end_date;
}

int TimeOff::get_start_shift() const{
    return start_shift;
}
int TimeOff::get_end_shift() const{
    return end_shift;
}

std::string TimeOff::get_description() const{
    return description;
}

void TimeOff::set_start_day(int d){
    start_date.at(0) = d;
}
void TimeOff::set_start_month(int m){
    start_date.at(1) = m;
}
void TimeOff::set_start_year(int y){
    start_date.at(2) = y;
}
void TimeOff::set_start_date(int d, int m, int y){
    start_date.at(0) = d;
    start_date.at(1) = m;
    start_date.at(2) = y;
}

void TimeOff::set_end_day(int d){
    end_date.at(0) = d;
}
void TimeOff::set_end_month(int m){
    end_date.at(1) = m;
}
void TimeOff::set_end_year(int y){
    end_date.at(2) = y;
}
void TimeOff::set_end_date(int d, int m, int y){
    end_date.at(0) = d;
    end_date.at(1) = m;
    end_date.at(2) = y;
}

void TimeOff::set_start_shift(int s){
    start_shift = s;
}
void TimeOff::set_end_shift(int s){
    end_shift = s;
}

void TimeOff::set_description(std::string str){
    description = str;
}
