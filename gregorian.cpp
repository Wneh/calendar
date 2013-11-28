#include "gregorian.h"

namespace lab2{

const int day_number_array[32] = {0,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3};
const std::string day_name_array[8] = {"sunday","monday","tuesday","wednesday","thursday","friday","saturday","sunday"};
const std::string month_name_array[13] = {"","january","february","march","april","may","june","july","august","september","october","november","december"};
const int months_length_array[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
const int cent_nummer_array[4] = {6,4,2,0};

Gregorian::Gregorian():Date(){}

Gregorian::Gregorian(int new_year,int new_month,int new_day):Date(new_year,new_month,new_day){
	if(new_month > 12 || new_month < 1 || new_day < 1 || new_day > days_this_month()){
    	throw std::out_of_range("Invalid date\n");
	}
}

Gregorian::Gregorian(const Date& other):Date(other){
	//Do nothing in here
}

Date& Gregorian::operator=(const Date& rhs){
	Date::operator=(rhs);
}

//++Gregorian
Date& Gregorian::operator++(){
	add_day();
	return *this;
}

//--Gregorian
Date& Gregorian::operator--(){
	remove_day();
	return *this;
}

//Gregorian++
Gregorian Gregorian::operator++(int unused){
	Gregorian result = *this;
	result.add_day();
	return result;
}

//Gregorian--
Gregorian Gregorian::operator--(int unused){
	Gregorian result = *this;
	result.remove_day();
	return result;
}

Date& Gregorian::operator+=(const int& n){
	add_day(n);
	return *this;
}

Date& Gregorian::operator-=(const int& n){
	remove_day(n);
	return *this;
}

int Gregorian::operator-(const Date& other) const{
	return (*this).mod_julian_day() - other.mod_julian_day();
}



bool Gregorian::operator==(const Date& rhs) const {
 	return ((y == rhs.year()) && (m == rhs.month()) && (d == rhs.day()));
}

bool Gregorian::operator!=(const Date& rhs) const{
	return !((*this) == rhs);
}

bool Gregorian::operator<(const Date& rhs) const{
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

bool Gregorian::operator>(const Date& rhs) const{
	return (rhs < (*this));
}

bool Gregorian::operator<=(const Date& rhs) const{
	return !((*this) > rhs);
}

bool Gregorian::operator>=(const Date& rhs) const{
	return !((*this) < rhs);
}

int Gregorian::mod_julian_day() const{

	int a = (14-month())/12;
	int y = year() + 4800 - a;
	int m = month()+(12*a)-3;

	int JDN = day() + (((153*m)+2)/5) + 365*y + (y/4)-(y/100)+(y/400)-32045;

	return std::floor(JDN - 2400000.5);
}

int Gregorian::week_day() const{
	int result;
	result += 0;
	
	int dayNumber = day_number_array[d];

	/*
	 * Month table;
	*/

	int monthNumber;

	if(m == 1){
		if(is_leap_year()){
			monthNumber = -1;
		} else {
			monthNumber = 0;
		}
	}
	else if(m == 2){
		if(is_leap_year()){
			monthNumber = 2;
		} else {
			monthNumber = 3;
		}
	}
	else if(m == 3){
		monthNumber = 3;
	}
	else if(m == 4){
		monthNumber = 6;
	}
	else if(m == 5){
		monthNumber = 1;
	}
	else if(m == 6){
		monthNumber = 4; 
	}
	else if(m == 7){
		monthNumber = 6;
	}
	else if(m == 8){
		monthNumber = 2;
	}
	else if(m == 9){
		monthNumber = 5;
	}
	else if(m == 10){
		monthNumber = 0;
	}
	else if(m == 11){
		monthNumber = 3;
	}
	else if(m == 12){
		monthNumber = 5;
	}

	int yearNumber = y%100;

	int centNumberTemp = (y/100)%4;

	int centNumber = cent_nummer_array[centNumberTemp];

	// if(centNumberTemp == 1){
	// 	centNumber = 4;
	// }
	// else if(centNumberTemp == 2){
	// 	centNumber = 2;
	// }
	// else if(centNumberTemp == 3){
	// 	centNumber = 0;
	// }
	// else if(centNumberTemp == 0){
	// 	centNumber = 6;
	// }

	return ((dayNumber + monthNumber + yearNumber + (int)std::floor((double)(yearNumber/4)) + centNumber-1)%7)+1;
}

std::string Gregorian::week_day_name() const{
	return day_name_array[week_day()];
}

std::string Gregorian::month_name() const{
	return month_name_array[m];
}

int Gregorian::days_this_month() const{
	return ((m == 2 && is_leap_year()) ? (months_length_array[m]+1) : months_length_array[m]);
}

int Gregorian::months_per_year() const{
	return 12;
}

void Gregorian::add_day(int n){
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
void Gregorian::add_day(){
	add_day(1);
}

//Remove a day
void Gregorian::remove_day(){
	add_day(-1);
}

void Gregorian::remove_day(int n){
	add_day(n*-1);
}

//Add a month
void Gregorian::add_month(){
	// ++m;
	// //Check if we're in the last month
	// if(m == 13){
	// 	//Increment year
	// 	add_year();
	// 	m = 1;
	// }
	// if(d > days_this_month()){
	// 	--m;
	// 	add_day(30);
	// }
	add_month(1);
}

// void Gregorian::add_month(int n){
// 	for(int i = 0; i < abs(n); ++i){
// 		(n > 0) ? add_month() : remove_month();
// 	}
// }

void Gregorian::add_month(int n){
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
void Gregorian::remove_month(){
	add_month(-1);
}

void Gregorian::remove_month(int n){
	add_month(n*-1);
}

//Increment number of years
void Gregorian::add_year(){
	//No limit here on number of year #YOLO
	// ++y;
	// //Check for leap year
	// if(m == 2 && d == 29){
	// 	if(!is_leap_year()){
	// 		d = 28;
	// 	}
	// }
	add_year(1);
}

void Gregorian::add_year(int n){
	// for(int i = 0; i < abs(n); ++i){
	// 	(n > 0) ? add_year() : remove_year();
	// }

	y += n;
  	if(m == 2 && d == 29){
    	if(!is_leap_year()){
      		d = 28; 
    	}
  	}
}

//Remove a year;
void Gregorian::remove_year(){
	// --y;
	// //Check for leap year
	// if(m == 2 && d == 29){
	// 	if(!is_leap_year()){
	// 		d = 28;
	// 	}
	// }
	remove_year(1);
}

void Gregorian::remove_year(int n){
	// for(int i = 0; i < n; ++i){
	// 	remove_year();
	// }

	y-= n;
	if(m == 2 && d == 29){
    	if(!is_leap_year()){
      		d = 28; 
    	}
  	}
}

}