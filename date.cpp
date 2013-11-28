#include "date.h"
#include <time.h>

namespace lab2{

//Default contructor
Date::Date(){
	// För att få nuvarande tid
   time_t tp;							//Kommentera denna för kattis
   //time(&tp); 							//Kommentera denna för kattis
   //set_k_time(tp);

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

bool Date::is_leap_year() const{
	if(((y%4 == 0) && (y%100 != 0)) || (y%400 == 0)){
		return true;
	}
	return false;
}

}