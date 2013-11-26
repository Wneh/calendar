#ifndef __DATE.H__
#define __DATE.H__

#include "kattistime.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdexcept> 

namespace lab2{

class Date{
public:
	Date();
	Date(int new_year, int new_month, int new_day);
	Date(const Date& other);
	//Date(const Date& other);
	Date& operator=(const Date& rhs);

	/*
 	 * Get functions
	*/
	const int year() const{
		return this->y;
	}
	const int month() const{
		return this->m;
	}
	const int day() const{
		return this->d;
	}

	/*
	 * Overloading of operators 
	*/
	virtual Date& operator++() = 0;
	virtual Date& operator--() = 0;
	//virtual Date& operator-() = 0;	

	virtual Date& operator+=(const int& n) = 0;
	virtual Date& operator-=(const int& n) = 0;
	virtual int operator-(const Date& rhs) const = 0;

	//Comparision operators
	virtual bool operator==(const Date& rhs) const = 0;
	virtual bool operator!=(const Date& rhs) const = 0;
	virtual bool operator< (const Date& rhs) const = 0;
	virtual bool operator> (const Date& rhs) const = 0;
	virtual bool operator<=(const Date& rhs) const = 0;
	virtual bool operator>=(const Date& rhs) const = 0;

	int days_per_week() const {return 7;}
	virtual bool is_leap_year() const;

	virtual int week_day() const = 0;
	virtual int days_this_month() const = 0;
	virtual int months_per_year() const = 0;
	virtual	std::string week_day_name() const = 0;
	virtual std::string month_name() const = 0;

	virtual void add_month() = 0;
	virtual void add_month(int n) = 0;

	virtual void add_year() = 0;
	virtual void add_year(int n) = 0;

	virtual int mod_julian_day() const = 0;	

 protected:
	int y,m,d;	

};

std::ostream &operator << (std::ostream &cout, const Date &d);

}

#endif
