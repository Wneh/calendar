#include "date.h"
#include <time.h>

namespace lab2{

const int day_number_array[32] = {0,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3};
const std::string day_name_array[8] = {"sunday","monday","tuesday","wednesday","thursday","friday","saturday","sunday"};
const std::string month_name_array[13] = {"","january","february","march","april","may","june","july","august","september","october","november","december"};
const int months_length_array[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const int cent_nummer_array[4] = {6,4,2,0};
const int month_nummer_array[13] = {-1,0,3,3,6,1,4,6,2,5,0,3,5};

//Default contructor
Date::Date(){
	// För att få nuvarande tid
   time_t tp;							//Kommentera denna för kattis
   // time(&tp); 							//Kommentera denna för kattis
   // set_k_time(tp);

   k_time(&tp); 						//Avkommentera denna för kattis

   // För att få ut datum lokalt 
   struct tm* t = gmtime(&tp);
   y = t->tm_year + 1900;
   m = t->tm_mon + 1;      // månaderna och dagarna
   d = t->tm_mday;         // indexerade från ETT
}

Date::Date(const Date& other): y(other.y), m(other.m), d(other.d){}

//Standard contructor
Date::Date(int new_year,int new_month,int new_day)
	:y(new_year),m(new_month),d(new_day){

}

Date& Date::operator=(const Date& other){
  (*this).y = other.y;
  (*this).m = other.m;
  (*this).d = other.d;
  return *this;
}

bool Date::operator==(const Date& other) const {
 	return (*this).mod_julian_day() == other.mod_julian_day();
}

bool Date::operator!=(const Date& rhs) const{
	return !((*this) == rhs);
}

bool Date::operator<(const Date& rhs) const{
	if(y == rhs.year()){
		if(m == rhs.month()){
			if(d < rhs.day()){
				return true;
			}
		}
		else if(m < rhs.month()){
			return true;
		}
	}
	else if(y < rhs.year()){
		return true;
	}
	return false;
}

bool Date::operator>(const Date& rhs) const{
	return (rhs < (*this));
}

bool Date::operator<=(const Date& rhs) const{
	return !((*this) > rhs);
}

bool Date::operator>=(const Date& rhs) const{
	return !((*this) < rhs);
}

int Date::operator-(const Date& other) const{
	return (*this).mod_julian_day() - other.mod_julian_day();
}

Date& Date::operator+=(const int& n){
	add_day(n);
	return *this;
}

Date& Date::operator-=(const int& n){
	remove_day(n);
	return *this;
}

std::ostream &operator << (std::ostream &cout, const Date &d){
	std::cout << d.year() << "-";

	if(d.month() < 10){
		std::cout << "0";
	}

	std::cout << d.month() << "-";

	if(d.day() < 10){
		std::cout << "0";
	}

	return std::cout << d.day();
}

//Add a month
void Date::add_month(){
	add_month(1);
}

void Date::add_month(int n){
	if(n == 0){
		return;
	}
	for(int i = 0; i < abs(n); ++i){
		if(n > 0){
			//Add month
			++m;
			if(m == 13){
				m = 1;
				++y;
			}
			if(d > days_this_month()){
				--m;
				add_day(30);
			}
		} else {
			--m;
			if(m == 0){
				m = 12;
				--y;
			}
			if(d > days_this_month()){
				++m;
				add_day(-30);
			}
		}
	}
}

//Remove a month
void Date::remove_month(){
	add_month(-1);
}

void Date::remove_month(int n){
	add_month(n*-1);
}

//Increment number of years
void Date::add_year(){
	add_year(1);
}

void Date::add_year(int n){
	y += n;
  	if(m == 2 && d == 29){
    	if(!is_leap_year()){
      		d = 28; 
    	}
  	}
}

//Remove a year;
void Date::remove_year(){
	remove_year(1);
}

void Date::remove_year(int n){
	y-= n;
	if(m == 2 && d == 29){
    	if(!is_leap_year()){
      		d = 28; 
    	}
  	}
}

void Date::add_day(int n){
	if(n == 0){
		return;
	}

	for(int i = 0; i < abs(n); ++i){
		//Add or remove day(s)?
		if(n > 0){
			//Add days
			if(d == days_this_month()){
				d = 1;
				if(m == 12){
					m = 1;
					++y;
				} else {
					++m;
				}
			} else {
				++d;
			}
		} else {
			//Remove days
			if(d == 1){
				if(m == 1){
					m = 12;
					--y;
					d = days_this_month();
				} else {
					--m;
					d = days_this_month();
				}
			} else {
				--d;
			}
		}
	}
}

//Add a day
void Date::add_day(){
	add_day(1);
}

//Remove a day
void Date::remove_day(){
	add_day(-1);
}

void Date::remove_day(int n){
	add_day(n*-1);
}

int Date::week_day() const{
	int result;
	result += 0;
	
	int dayNumber = day_number_array[d];
	
	//Month table;
	int monthNumber = month_nummer_array[m];
	//Leap year check
	if(is_leap_year()){
		if(m == 1){
			monthNumber = -1;
		}
		else if(m == 2){
			monthNumber = 2;
		}
	}

	int yearNumber = y%100;

	int centNumberTemp = (y/100)%4;

	int centNumber = cent_nummer_array[centNumberTemp];

	return ((dayNumber + monthNumber + yearNumber + (int)std::floor((double)(yearNumber/4)) + centNumber-1)%7)+1;
}

int Date::days_this_month() const{
	return ((m == 2 && is_leap_year()) ? (months_length_array[m]+1) : months_length_array[m]);
}

int Date::months_per_year() const{
	return 12;
}

std::string Date::week_day_name() const{
	return day_name_array[week_day()];
}

std::string Date::month_name() const{
	return month_name_array[m];
}

}