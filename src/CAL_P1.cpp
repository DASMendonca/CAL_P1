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
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->addNode(0);
	gv->addNode(1);
	gv->addNode(2);
	gv->addNode(3);
	gv->addNode(4);
	gv->addNode(5);
	gv->setVertexLabel(0, "Etosha National Park");
	gv->setVertexLabel(1, "Waterberg");
	gv->setVertexLabel(2, "Damaraland");
	gv->setVertexLabel(3, "Windhoek");
	gv->setVertexLabel(4, "Swakopmund");
	gv->setVertexLabel(5, "Walvis Bay");
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 1, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(4, 2, 4, EdgeType::UNDIRECTED);
	gv->addEdge(5, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(6, 3, 5, EdgeType::UNDIRECTED);
	gv->addEdge(7, 4, 5, EdgeType::UNDIRECTED);
	gv->setEdgeLabel(0, "4h");
	gv->setEdgeLabel(1, "2h");
	gv->setEdgeLabel(2, "2h");
	gv->setEdgeLabel(3, "4h");
	gv->setEdgeLabel(4, "3h");
	gv->setEdgeLabel(5, "5h");
	gv->setEdgeLabel(6, "5h");
	gv->setEdgeLabel(7, "1h");
	gv->rearrange();
	getchar();
	return 0;
}
