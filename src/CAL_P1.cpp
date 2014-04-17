//============================================================================
// Name        : CAL_P1.cpp
// Author      : Daniel Mendonça
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"

int main() {
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("green");
	gv->defineEdgeColor("black");
	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->setEdgeLabel(0, "20");
	gv->rearrange();
	getchar();
	return 0;
}
