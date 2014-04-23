/*
 * City.h
 *
 *  Created on: 17/04/2014
 *      Author: Daniel
 */

#ifndef City_H_
#define City_H_

#include <string>

class City{
	std::string name;
	bool resting;
	bool airport;
	int visit_time;
	bool interest;

public:
	City(std::string name, bool flying, bool rest, int visit_time);
	bool isRestingPlace();
	bool hasAirport();
	bool isInterestPoint();

	int getVisitTime();
	std::string getName();

	bool operator == (const City &c2) const;
	friend std::ostream & operator << (std::ostream &os, City &c);

	virtual ~City();
};

#endif /* City_H_ */
