/*
 * City.cpp
 *
 *  Created on: 17/04/2014
 *      Author: Daniel
 */

#include "City.h"
using namespace std;

City::City(string name, bool flying, bool rest, int visit_time):name(name), resting(rest), airport(flying),
		visit_time(visit_time)
{

	if(visit_time>0)
		interest=true;
}

City:: ~City(){}


int City::getVisitTime(){
	return visit_time;
}


string City::getName(){
	return name;
}


bool City::operator == (const City &c2) const {
	return (name==c2.name);
}

ostream & operator << (ostream &os, City &c) {
	os << c.getName();
	return os;
}
