//============================================================================
// Name        : CAL_P1.cpp
// Author      : Daniel Mendon�a
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CAL_P1.h"

using namespace std;
int main() {

	Graph<City> test;
	graphGenerator();
	return 0;
}

//Draws any Graph as long as it's a valid Graph<City>
//TODO: color coding
void drawGraph(Graph<City> toDraw) {
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	for (unsigned int i = 0; i < toDraw.getVertexSet().size(); i++) {
		gv->addNode(i);
		gv->setVertexLabel(i, toDraw.getVertexSet()[i]->getInfo().getName());
	}
	int edgecount = 0;
	vector<vector<unsigned int> > added;
	vector<unsigned int> temp;
	for (unsigned int i = 0; i < toDraw.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < toDraw.getVertexSet()[i]->getAdj().size(); j++) {
			for (unsigned int k = 0; k < toDraw.getVertexSet().size(); k++) {
				if (toDraw.getVertexSet()[k]->getInfo() == toDraw.getVertexSet()[i]->getAdj()[j].getDest().getInfo()) {
					string result;
					stringstream convert;
					convert << toDraw.getVertexSet()[i]->getAdj()[j].getWeight();
					result = convert.str();
					if (result != "0") {
						bool duplicate = false;
						for (unsigned int n = 0; n < added.size(); n++) {
							if (added[n][1] == i && added[n][0] == k) {
								duplicate = true;
							}
						}
						if (!duplicate) {
							gv -> addEdge(edgecount, i, k, EdgeType::UNDIRECTED);
							gv -> setEdgeLabel(edgecount, result);
							edgecount++;
							temp.clear();
							temp.push_back(i);
							temp.push_back(k);
							added.push_back(temp);
						}
					}
				}
			}
		}
	}
	gv->rearrange();
	getchar();
}

//Loads a graph from a edge + vertex file
Graph<City> loadGraph() {
	Graph<City> toLoad;
	vector<vector<string> > vertexes;
	vector<vector<string> > edges;
	vertexes = readVertex("vertex.csv"); //TEMP HARDCODED FILENAME
	edges = readEdge("edge.csv", vertexes.size()); //TEMP HARDCODED FILENAME

	if(DEBUG)
		for(unsigned int i=0; i<vertexes.size(); i++)
			cout<<vertexes[i][0]<<" "<<vertexes[i][1]<<" "<<vertexes[i][2]<<" "<<vertexes[i][3]<<endl;

	if(DEBUG)
		for(unsigned int i=0; i<edges.size(); i++){
			for(unsigned int j=0; j< edges[i].size(); j++)
				cout<<edges[i][j]<<" ";
			cout<<endl;
		}

	for (unsigned int i = 0; i < vertexes.size(); i++) {
		int result;
		stringstream convert(vertexes[i][3]);
		convert >> result;
		bool airport = stringtobool(vertexes[i][1]);
		bool resting = stringtobool(vertexes[i][2]);
		int visit_time = atoi(vertexes[i][3].c_str());
		toLoad.addVertex(City(vertexes[i][0], airport, resting, visit_time));
	}
	for (unsigned int i = 0; i < edges.size(); i++) {
		for (unsigned int j = 0; j < edges[i].size(); j++) {
			int result = atoi(edges[i][j].c_str());
			if (result != 0) {
				toLoad.addEdge(toLoad.getVertexSet()[i]->getInfo(), toLoad.getVertexSet()[j]->getInfo(), result);
			}
		}
	}
	return toLoad;
}

//Converts a string to a boolean value
bool stringtobool(string toConvert) {
	transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::tolower);
	if (toConvert == "0" || toConvert == "false") {
		return false;
	} else if (toConvert == "1" || toConvert == "true") {
		return true;
	} else return -1;
}

//City(string name, bool flying, bool rest, double visit_time);
//City(string name, bool flying, bool rest, int visit_time);
void graphGenerator(){

	Graph<City> travel;

	//	City c1("Etosha National Park", false, true, 4);
	//	City c2("Damaraland", false, false, 2);
	//	City c3("Swakopmund", false, true, 4);
	//	City c4("Waterberg", false, true, 0);
	//	City c5("Windhoek", true, true, 0);
	//	City c6("Walvis Bay", false, false, 1);
	//
	//	travel.addVertex(c1); travel.addVertex(c2);
	//	travel.addVertex(c3); travel.addVertex(c4);
	//	travel.addVertex(c5); travel.addVertex(c6);
	//
	//	travel.addEdge(c1,c2,2);	travel.addEdge(c2,c1,2);	//etosha-damaraland
	//	travel.addEdge(c1,c4,4);	travel.addEdge(c4,c1,4);	//etosha-waterberg
	//	travel.addEdge(c2,c3,3);	travel.addEdge(c3,c2,3);	//damaraland-swakopmund
	//	travel.addEdge(c2,c5,4);	travel.addEdge(c5,c2,4);	//damaraland-windhoek
	//	travel.addEdge(c3,c6,1);	travel.addEdge(c6,c3,1);	//swakopmund-walvis
	//	travel.addEdge(c3,c5,5);	travel.addEdge(c5,c3,5);	//swakopmund-windhoek
	//	travel.addEdge(c4,c5,2);	travel.addEdge(c5,c4,2);	//waterberg-windhoek
	//	travel.addEdge(c5,c6,5);	travel.addEdge(c6,c5,5);	//windhoek-walvis
	travel = loadGraph();


	if(!(travel.landAndBegin(TIME_PER_DAY)))
	{
		cout<<"no solution found"<<endl;
		exit(1);
	}

	if(DEBUG)
		floydWarshallTester(travel.getW(), travel.getVertexSet().size());

	drawSolution(travel);

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


void drawSolution(Graph<City> &graph){
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex<City> *> path = graph.getSolution();
	int vertex_size = graph.getVertexSet().size();

	for(int i =0; i< vertex_size; i++)
	{
		gv->addNode(i);
		string label = graph.getVertexSet()[i]->getInfo().getName();
		ostringstream temp;  //temp as in temporary
		temp<<label<<"  "<<graph.getVertexSet()[i]->getInfo().getVisitTime();
		if(graph.getVertexSet()[i]->getInfo().isRestingPlace())
			temp<<"  Resting Place";
		if(graph.getVertexSet()[i]->getInfo().hasAirport())
			temp<<"  Airport";
		temp<<endl;

		label=temp.str();

		gv->setVertexLabel(i, label);
	}

	int edge_count=0;


	for(unsigned int i =0; i< path.size() -1; i++){
		int j=i+1;
		int src = graph.findIndexVertex(graph.getSolution()[i]->getInfo().getName());
		int dst = graph.findIndexVertex(graph.getSolution()[j]->getInfo().getName());
		int cost = graph.getCostFromW(src, dst);
		if(DEBUG)
		cout<<"dest: "<<graph.getSolution()[j]->getInfo().getName()<<endl;

		if(src!= dst)
		{

			gv->addEdge(edge_count, src, dst, EdgeType::DIRECTED);
			string str;          //The string
			ostringstream temp;  //temp as in temporary
			temp<<cost;
			str=temp.str();
			gv->setEdgeLabel(edge_count, str);
			edge_count++;
		}
	}
	gv->rearrange();
	getchar();
}
