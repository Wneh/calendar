#ifndef __GREGORIAN.H__
#define __GREGORIAN.H__

#include "date.h"

namespace lab2{

	class Gregorian : public Date{
	public:

		Gregorian();
		Gregorian(int new_year, int new_month, int new_day);
		Gregorian(const Date& other);

		Date& operator++();
		Date& operator--();
		Gregorian operator++(int unused);
		Gregorian operator--(int unused);

		int mod_julian_day() const;	

		// int week_day() const;
		// int days_this_month() const;
		// int months_per_year() const;
		// std::string week_day_name() const;
		// std::string month_name() const;

		bool is_leap_year() const;
	private:

	};
}

#endif