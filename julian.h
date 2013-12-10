#ifndef JULIAN_H
#define JULIAN_H

#include "date.h"

namespace lab2{

	class Julian : public Date{
	public:
		Julian();
		Julian(int new_year, int new_month, int new_day);
		Julian(const Date& other);

		Date& operator=(const Date& rhs);
		Date& operator++();
		Date& operator--();
		Julian operator++(int unused);
		Julian operator--(int unused);

		int mod_julian_day() const;	
		bool is_leap_year() const;
		int week_day() const;
	private:
		int julian_day() const;
		int mod_julian_day_from_greg() const;
	};
}

#endif
