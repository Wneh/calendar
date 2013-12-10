#include "julian.h"

namespace lab2{

	const int day_number_array[32] = {0,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3,4,5,6,7,1,2,3};
	const int months_length_array[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	const int cent_nummer_array_julian[7] = {4,3,2,1,0,6,5};
	const int month_nummer_array[13] = {-1,0,3,3,6,1,4,6,2,5,0,3,5};

	Julian::Julian():Date(){
		*this += ((*this).mod_julian_day_from_greg() - (*this).mod_julian_day());
	}

	Julian::Julian(int new_year,int new_month,int new_day):Date(new_year,new_month,new_day){
		if(new_month > 12 || new_month < 1 || new_day < 1 || new_day > days_this_month()){
    		throw std::out_of_range("Invalid date\n");
		}
	}

	Julian::Julian(const Date& other):Date(other){
		//Do nothing in here
		(*this) += (other.mod_julian_day() - (*this).mod_julian_day());
	}

	Date& Julian::operator=(const Date& other){
		Date::operator=(other);
		(*this) += (other.mod_julian_day() - (*this).mod_julian_day());	
	}

	//++Date
	Date& Julian::operator++(){
		add_day();
		return *this;
	}

	//--Date
	Date& Julian::operator--(){
		remove_day();
		return *this;
	}

	//Gregorian++
	Julian Julian::operator++(int unused){
		Julian result = *this;
		result.add_day();
		return result;
	}

	//Gregorian--
	Julian Julian::operator--(int unused){
		Julian result = *this;
		result.remove_day();
		return result;
	}

	int Julian::julian_day() const{
		int a = (14-month())/12;
		int y = year() + 4800 - a;
		int m = month()+(12*a)-3;

		int JDN = day() + (((153*m)+2)/5) + 365*y + (y/4)-32083;	

		return JDN;
	}

	int Julian::mod_julian_day_from_greg() const{
		int a = (14-month())/12;
		int y = year() + 4800 - a;
		int m = month()+(12*a)-3;

		int JDN = day() + (((153*m)+2)/5) + 365*y + (y/4)-(y/100)+(y/400)-32045;

		return std::floor(JDN - 2400000.5);
	}

	int Julian::mod_julian_day() const{
		return std::floor(julian_day()- 2400000.5);
	}

	bool Julian::is_leap_year() const{
		if(y%4 == 0){
			return true;
		}
		return false;
	}

	int Julian::week_day() const{
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

		int centNumberTemp = (y/100)%7;

		int centNumber = cent_nummer_array_julian[centNumberTemp];

		return ((dayNumber + monthNumber + yearNumber + (int)std::floor((double)(yearNumber/4)) + centNumber-1)%7)+1;
	}

}
