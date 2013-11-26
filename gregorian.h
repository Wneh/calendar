#ifndef __GREGORIAN.H__
#define __GREGORIAN.H__

#include "date.h"

namespace lab2{

class Gregorian : public Date{
public:

	Gregorian();
	Gregorian(int new_year, int new_month, int new_day);
	Gregorian(const Date& other);
	Date& operator=(const Date& rhs);

	Date& operator++();
	Date& operator--();
	Gregorian operator++(int unused);
	Gregorian operator--(int unused);
	int operator-(const Date& rhs) const;

	Date& operator+=(const int& n);
	Date& operator-=(const int& n);

	//Comparision operators
	virtual bool operator==(const Date& rhs) const;
	virtual bool operator!=(const Date& rhs) const;
	virtual bool operator< (const Date& rhs) const;
	virtual bool operator> (const Date& rhs) const;
	virtual bool operator<=(const Date& rhs) const;
	virtual bool operator>=(const Date& rhs) const;

	int mod_julian_day() const;	

	int week_day() const;
	int days_this_month() const;
	int months_per_year() const;
	std::string week_day_name() const;
	std::string month_name() const;

	void add_month();
	void add_month(int n);

	void add_year();
	void add_year(int n);

	//bool is_leap_year() const;

private:
	void add_day();
	void add_day(int n );

	void remove_day();
	void remove_day(int n);

	void remove_month();
	void remove_month(int n);

	void remove_year();
	void remove_year(int n);

};

}

#endif