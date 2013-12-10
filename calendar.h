#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace lab2{

template <class T>
class Event{
public:
	T date;
	std::string info;

	Event<T>(){}
	Event<T>(std::string in_info,int y,int m, int d):date(y,m,d),info(in_info){}

	bool operator==(const Event<T>& other) const {
		return ((*this).date == other.date) && ((*this).info == other.info); 
	}

	friend std::ostream &operator << (std::ostream &cout, const Event<T>& e){
		cout << e.date << " : " << e.info;
		return cout;
	}
};

template <class T>
class Calendar{
public:
	T current_date;
	std::vector<Event<T>> events;

	//Default contructor
	Calendar<T>(){
		T d;
		current_date = d;
	}

	template <class K>
	Calendar<T>(const Calendar<K>& cal){
		//Copy the current date
		current_date = cal.current_date;
		for(auto it = cal.events.begin(); it != cal.events.end(); ++it){
			// auto& temp = *it;
			Event<T> e;
			e.date = (*it).date;
			e.info = (*it).info;

			events.push_back(e);
		}
	}

	bool set_date(int y,int m,int d){
		try{
			current_date = T(y,m,d);
			return true;
		}catch(std::out_of_range oor){
			return false;
		}
	}

	bool add_event(std::string in_text){
		return add_event(in_text,current_date.day(),current_date.month(),current_date.year());
	}
	bool add_event(std::string in_text,int d){
		return add_event(in_text,d,current_date.month(),current_date.year());
	}
	bool add_event(std::string in_text,int d,int m){
		return add_event(in_text,d,m,current_date.year());	
	}
	bool add_event(std::string in_text,int d,int m ,int y){
		//Create the new event
		try{
			Event<T> e(in_text,y,m,d);

			auto it = events.begin();
			for(; it != events.end(); ++it){
				//auto& temp = *it;
       			//Found a exact event 
				if((*it) == e){
					return false;
				}

       			//If we passed it in date insert it.
				if((*it).date > e.date){
					if(it != events.end()){
						events.insert(it,e);
						return true;
					}
					else {
						events.push_back(e);
						return true;
					}
				}
			}

			//Check if come to the end then insert it at the end
			if(it == events.end()){
				events.push_back(e);
			}
			return true;
		}catch(std::out_of_range oor){
			return false;
		}
	}

	bool remove_event(std::string in_text){
		return remove_event(in_text,current_date.day(),current_date.month(),current_date.year());
	}
	bool remove_event(std::string in_text,int d){
		return remove_event(in_text,d,current_date.month(),current_date.year());
	}
	bool remove_event(std::string in_text,int d,int m){
		return remove_event(in_text,d,m,current_date.year());	
	}
	bool remove_event(std::string in_text,int d,int m ,int y){
		try{
			Event<T> e(in_text,y,m,d);

			auto it = std::find(events.begin(),events.end(),e);

			if(it != events.end()){
				events.erase(it);
				return true;
			}
			return false;
		}catch(std::out_of_range oor){
			return false;
		}
	}
};

template <class T>
std::ostream &operator << (std::ostream &cout, const Calendar<T>& cal){
	for(auto it = cal.events.begin(); it != cal.events.end(); ++it){
		//auto& temp = *it;
		if((*it).date > cal.current_date){
			cout << (*it) << std::endl;
		}
	}
	return cout;
}
}

#endif