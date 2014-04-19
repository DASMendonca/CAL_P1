/*
 * City.h
 *
 *  Created on: 17/04/2014
 *      Author: Daniel
 */

#ifndef City_H_
#define City_H_

#include <string>
using namespace std;

class City{
	string name;
	bool visited;
	bool interest;
	bool resting;
	bool airport;
	int visit_time;

public:
	City(string name);
	City(string name, bool flying, bool rest, int visit_time);
	bool isVisited();
	bool isRestingPlace();
	bool hasAirport();
	bool isInterestPoint();

	int getVisitTime();
	string getName();

	bool operator == (const City &c2) const;
	friend ostream & operator << (ostream &os, City &c);

	virtual ~City();
};

#endif /* City_H_ */
