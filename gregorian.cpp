#include "gregorian.h"

namespace lab2{

Gregorian::Gregorian():Date(){}

Gregorian::Gregorian(int new_year,int new_month,int new_day):Date(new_year,new_month,new_day){
	if(new_month > 12 || new_month < 1 || new_day < 1 || new_day > days_this_month()){
    	throw std::out_of_range("Invalid date\n");
	}
}

Gregorian::Gregorian(const Date& other):Date(other){

	if(is_leap_year() != (other.year() % 4 == 0)){
		if(other.month() == 2 && other.day() == 29){
			// ++(*this);
			m = 3;
			d = 1;
		}
	}

	(*this) += (other.mod_julian_day() - (*this).mod_julian_day());
}

Date& Gregorian::operator=(const Date& other){
	Date::operator=(other);

	if(is_leap_year() != (other.year() % 4 == 0)){
		if(other.month() == 2 && other.day() == 29){
			m = 3;
			d = 1;
		}
	}

	(*this) += (other.mod_julian_day() - (*this).mod_julian_day());
}

//++Date
Date& Gregorian::operator++(){
	add_day();
	return *this;
}

//--Date
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

int Gregorian::mod_julian_day() const{

	int a = (14-month())/12;
	int y = year() + 4800 - a;
	int m = month()+(12*a)-3;

	int JDN = day() + (((153*m)+2)/5) + 365*y + (y/4)-(y/100)+(y/400)-32045;

	return std::floor(JDN - 2400000.5);
}

bool Gregorian::is_leap_year() const{
	if(((y%4 == 0) && (y%100 != 0)) || (y%400 == 0)){
		return true;
	}
	return false;
}

}