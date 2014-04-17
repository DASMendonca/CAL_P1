/*
 * cidade.h
 *
 *  Created on: 17/04/2014
 *      Author: Daniel
 */

#ifndef CIDADE_H_
#define CIDADE_H_

#include <string>
using namespace std;

class Cidade {
	string name;
	bool visited;
	bool interest;
	bool resting;
	bool airport;
	double visit_time;

public:
	Cidade(string name);
	Cidade(string name, bool flying, bool rest, double visit_time);
	bool isVisited();
	bool isRestingPlace();
	bool hasAirport();
	bool isInterestPoint();
	double getVisitTime();
	void setVisited();
	void setNotVisited();


	virtual ~Cidade();
};

#endif /* CIDADE_H_ */
