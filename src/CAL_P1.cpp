//============================================================================
// Name        : CAL_P1.cpp
// Author      : Daniel Mendonça
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CAL_P1.h"

int main() {

	graphGenerator();
	//graphViewerTest();

	return 0;
}




//City(string name, bool flying, bool rest, double visit_time);
void graphGenerator(){

	Graph<City> travel;

	City c1("Etosha National Park", false, true, 4);
	City c2("Damaraland", false, false, 2);
	City c3("Swakopmund", false, true, 4);
	City c4("Waterberg", false, true, 0);
	City c5("Windhoek", true, true, 0);
	City c6("Walvis Bay", false, true, 1);

	travel.addVertex(c1); travel.addVertex(c2);
	travel.addVertex(c3); travel.addVertex(c4);
	travel.addVertex(c5); travel.addVertex(c6);

	travel.addEdge(c1,c2,2);	travel.addEdge(c2,c1,2);	//etosha-damaraland
	travel.addEdge(c1,c4,4);	travel.addEdge(c4,c1,4);	//etosha-waterberg
	travel.addEdge(c2,c3,3);	travel.addEdge(c3,c2,3);	//damaraland-swakopmund
	travel.addEdge(c2,c5,4);	travel.addEdge(c5,c2,4);	//damaraland-windhoek
	travel.addEdge(c3,c6,1);	travel.addEdge(c6,c3,1);	//swakopmund-walvis
	travel.addEdge(c3,c5,5);	travel.addEdge(c5,c3,5);	//swakopmund-windhoek
	travel.addEdge(c4,c5,2);	travel.addEdge(c5,c4,2);	//waterberg-windhoek
	travel.addEdge(c5,c6,5);	travel.addEdge(c6,c5,5);	//windhoek-walvis

	travel.floydWarshallShortestPath();

	floydWarshallTester(travel.getW(), 6);


}


void graphViewerTest(){
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
}


void floydWarshallTester(int **W, int square_size){
	for(int i =0; i<square_size; i++)
	{
		for(int j=0; j<square_size; j++)
			cout<<W[i][j]<<" ";
		cout<<endl;
	}
}
