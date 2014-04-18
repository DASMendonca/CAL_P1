/*
 * CAL_P1.h
 *
 *  Created on: 17/04/2014
 *      Author: Daniel
 */

#ifndef CAL_P1_H_
#define CAL_P1_H_

#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"
#include "City.h"
#include "parser.h"
#include <algorithm>


void graphGenerator();

void graphViewerTest();

void floydWarshallTester(int **W, int square_size);

Graph<City> loadGraph();

bool stringtobool(string toConvert);

void drawGraph(Graph<City> toDraw);

#endif /* CAL_P1_H_ */
