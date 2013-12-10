#include "gregorian.h"
#include "julian.h"
#include <assert.h>

using namespace lab2;	


int main(){

	//Date* d1 = new Date(1337,1,2);
	//Date* d2 = new Date();

	Gregorian g1 = Gregorian(1337,1,2);
	Gregorian g2 = Gregorian();

	//Check basic init
	assert(g1.year() == 1337);
	assert(g1.month() == 1);
	assert(g1.day() == 2);

	//Prefix increment
	++g1;
	assert(g1.day() == 3);

	//Postfix increment
	++g1;
	assert(g1.day() == 4);

	//Leap year?
	Gregorian g3 = Gregorian(2000,2,29);
	assert(g3.is_leap_year() == true);

	//Year 2013 is not a leap year so...
	assert(g2.is_leap_year() == false);

	Gregorian g4 = Gregorian(2013,11,13);
	//std::string temp = g4.week_day_name();
	std::cout << g4.week_day_name() << std::endl;
	assert(g4.week_day_name() == "wednesday");
	assert(g3.week_day_name() == "tuesday");

	assert(g4.month_name() == "november");
	assert(g3.month_name() == "february");

	//Boolean operators
	Gregorian g5 = Gregorian(2000,1,28);
	Gregorian g6 = Gregorian(2000,1,29);

	assert((g5 == g5) == true);

	//test the year
	assert((g3 < g4) == true);
	//Test the month
	assert((g5 < g3) == true);
	//Test the day
	assert((g5 < g6) == true);
	//Test if the same date is not less then the other
	assert((g5 < g5) == false);
	//Some more tests
	assert((g5 == g5) == true);
	assert((g4 > g6) == true);
	assert((g5 <= g5) == true);
	assert((g5 >= g5) == true);

	g6 += 1;

	Gregorian gMonth(2000,1,31);
	gMonth.add_month();

	std::cout << "gMonth: " << gMonth <<  std::endl;

	//assert(g6.month() == 1);
	//assert(g6.day() == 30);

	std::cout << "g6 - 1:" << g6 << std::endl;

	g6 += 2;

	std::cout << "g6 - 2: " << g6 << std::endl;
	assert(g6.month() == 2);
	
	assert(g6.day() == 1);

	std::cout << g5 << std::endl;
	std::cout << g6 << std::endl;
	std::cout << g5.mod_julian_day() << " " <<g6.mod_julian_day() << std::endl;
	std::cout << std::endl;

	assert((g5 - g6) == -4);
	std::cout << g5 << std::endl;
	std::cout << g6 << std::endl;
	std::cout << std::endl;
	assert((g6 - g5) == 4);

	std::cout << g5 << std::endl;
	std::cout << g6 << std::endl;
	std::cout << std::endl;


	//std::cout << g2.mod_julian_day() << std::endl;

	//Mod julian date
	Gregorian julian = Gregorian(2004,1,1);
	std::cout << julian.mod_julian_day() << " == 53005" <<std::endl;

	Gregorian jul2(1974,4,20);
	std::cout << jul2.mod_julian_day() << " == 42157" << std::endl;
	
	Gregorian jul1(2028,11,29);
	std::cout << jul1.mod_julian_day() << " == 62104" << std::endl;	

	assert(julian.mod_julian_day() == 53005);
	assert(jul2.mod_julian_day() == 42157);
	assert(jul1.mod_julian_day() == 62104);

	Julian jul3(1900,2,29);
	Gregorian gregoly(jul3);
	Gregorian grog;
	grog = jul3;

	std::cout << gregoly << " == " << grog << std::endl;

	Gregorian g; // dagens datum
	Julian j; // också dagens datum
	std::cout << "Today it is " << g << " gregorian and " << j << " julian";
	if (g - j == 0) std::cout << ". It is the same date" << std::endl;
	g = j;
	if (g - j == 0) std::cout << "It is still the same date" << std::endl;

	return 0;
}