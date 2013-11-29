#ifndef __DATE.H__
#define __DATE.H__

#include "kattistime.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdexcept> 
#include <cmath>

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

	Date& operator+=(const int& n);
	Date& operator-=(const int& n);

	int operator-(const Date& rhs) const;

	//Comparision operators
	bool operator==(const Date& rhs) const;
	bool operator!=(const Date& rhs) const;
	bool operator< (const Date& rhs) const;
	bool operator> (const Date& rhs) const;
	bool operator<=(const Date& rhs) const;
	bool operator>=(const Date& rhs) const;

	int days_per_week() const {return 7;}
	virtual bool is_leap_year() const = 0;

	// virtual int week_day() const = 0;
	// virtual int days_this_month() const = 0;
	// virtual int months_per_year() const = 0;
	// virtual std::string week_day_name() const = 0;
	// virtual std::string month_name() const = 0;

	void add_month();
	void add_month(int n);

	void add_year();
	void add_year(int n);

	virtual int mod_julian_day() const = 0;

	int week_day() const;
	int days_this_month() const;
	int months_per_year() const;
	std::string week_day_name() const;
	std::string month_name() const;

 protected:
	int y,m,d;	

	void remove_day();
	void remove_day(int n);

	void remove_month();
	void remove_month(int n);

	void remove_year();
	void remove_year(int n);

	void add_day();
	void add_day(int n);

};

std::ostream &operator << (std::ostream &cout, const Date &d);

}

#endif
