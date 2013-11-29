#include "gregorian.h"

namespace lab2{

Gregorian::Gregorian():Date(){}

Gregorian::Gregorian(int new_year,int new_month,int new_day):Date(new_year,new_month,new_day){
	if(new_month > 12 || new_month < 1 || new_day < 1 || new_day > days_this_month()){
    	throw std::out_of_range("Invalid date\n");
	}
}

Gregorian::Gregorian(const Date& other):Date(other){
	//Do nothing in here
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

// int Gregorian::week_day() const{
// 	int result;
// 	result += 0;
	
// 	int dayNumber = day_number_array[d];
	
// 	//Month table;
// 	int monthNumber = month_nummer_array[m];
// 	//Leap year check
// 	if(is_leap_year()){
// 		if(m == 1){
// 			monthNumber = -1;
// 		}
// 		else if(m == 2){
// 			monthNumber = 2;
// 		}
// 	}

// 	int yearNumber = y%100;

// 	int centNumberTemp = (y/100)%4;

// 	int centNumber = cent_nummer_array[centNumberTemp];

// 	return ((dayNumber + monthNumber + yearNumber + (int)std::floor((double)(yearNumber/4)) + centNumber-1)%7)+1;
// }

// std::string Gregorian::week_day_name() const{
// 	return day_name_array[week_day()];
// }

// std::string Gregorian::month_name() const{
// 	return month_name_array[m];
// }

// int Gregorian::days_this_month() const{
// 	return ((m == 2 && is_leap_year()) ? (months_length_array[m]+1) : months_length_array[m]);
// }

// int Gregorian::months_per_year() const{
// 	return 12;
// }

bool Gregorian::is_leap_year() const{
	if(((y%4 == 0) && (y%100 != 0)) || (y%400 == 0)){
		return true;
	}
	return false;
}

}