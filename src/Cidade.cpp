/*
 * cidade.cpp
 *
 *  Created on: 17/04/2014
 *      Author: Daniel
 */

#include "Cidade.h"


Cidade::Cidade(string name): name(name), airport(false), visit_time(0), visited(false), resting(true), interest(false){}

Cidade::Cidade(string name, bool flying, bool rest, double visit_time):name(name), airport(flying),
		visit_time(visit_time), resting(rest), visited(false){

	if(visit_time>0)
		interest=true;
}

void Cidade::setVisited(){
	visited = true;
}

void Cidade::setNotVisited(){
	visited= false;
}

double Cidade::getVisitTime(){
	return visit_time;
}
