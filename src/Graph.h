/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include "AuxFunc.h"

using namespace std;
template <class T> class Edge;
template <class T> class Graph;


/********************************************
 * 											*
 * 											*
 * 				Vertex						*
 * 											*
 * 											*
 *******************************************/
template <class T>
class Vertex {
	T info;
	bool visited;
	vector<Edge<T>  > adj;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);

public:
	Vertex(T in);
	T getInfo() const;

	vector<Edge<T> > getAdj();

	bool isVisited();
	void setVisited();
	void unsetVisited();

	friend class Graph<T>;
};


template <class T>
void Vertex<T>::setVisited(){
	visited= true;
}


template <class T>
void Vertex<T>::unsetVisited(){
	visited= false;
}


template <class T>
bool Vertex<T>::isVisited(){
	return visited;
}


template <class T>
vector<Edge<T> > Vertex<T>::getAdj() {
	return adj;
}


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}


template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	adj.push_back(edgeD);
}


template <class T>
Vertex<T>::Vertex(T in):info(in), visited(false){}


/********************************************
 * 											*
 * 											*
 * 				Edge						*
 * 											*
 * 											*
 *******************************************/
template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
	Vertex<T> getDest();
	double getWeight();
};


template <class T>
Vertex<T> Edge<T>::getDest() {
	return *dest;
}


template <class T>
double Edge<T>::getWeight() {
	return weight;
}


template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w){}


/********************************************
 * 											*
 * 											*
 * 				Graph						*
 * 											*
 * 											*
 *******************************************/
template <class T>
class Graph {
	vector<Vertex<T> *> solution;
	vector<Vertex<T> *> vertexSet;
	vector<Vertex<T> *> airport_citys;

	int days;
	int daily_time;
	int **W;
	int **P;

public:
	int available_time;

	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	bool allVisited();
	bool findNextCity(Vertex<T> *city, int &present_index);
	bool findRestPlaceFrom(int index);
	bool visitFromIpRp(int city_index);


	void updateEdges();
	void floydWarshallShortestPath();
	void setDailyTime(int time_to_spend);
	void setDaily_time(int time);
	void restoreAvailableTime();
	void mapAirports();
	void landAndBegin(int daily_time);
	void testerfunction();

	string getInfo(Vertex<T> city);

	int edgeCost(int vOrigIndex, int vDestIndex);
	int getTravelTime(Vertex<T> from, Vertex<T> to);
	int getDailyTime();
	int findIndexVertex(string info);

	int** getW();
	int* cityTravelCosts(int city_index);
	int* restingTravelCosts(int city_index);
	vector<Vertex<T> > getSolution();
	vector<Vertex<T> *> getVertexSet();
	vector<int> getBestCityTo(int city_index);
	vector<int> getIpUnvisited();
};


template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() {
	return vertexSet;
}


template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}


template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}


template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vS->addEdge(vD,w);

	return true;
}


template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	return vS->removeEdgeTo(vD);
}


template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new int * [vertexSet.size()];
	P = new int * [vertexSet.size()];
	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for(unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = edgeCost(i,j);
			P[i][j] = -1;
		}
	}


	for(unsigned int k = 0; k < vertexSet.size(); k++)
		for(unsigned int i = 0; i < vertexSet.size(); i++)
			for(unsigned int j = 0; j < vertexSet.size(); j++)
			{
				if(W[i][k] == INT_MAX || W[k][j] == INT_MAX)
					continue;

				int val = min ( W[i][j], W[i][k]+W[k][j] );
				if(val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}


template<class T>
int Graph<T>::edgeCost(int vOrigIndex, int vDestIndex)
{
	if(vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for(unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
	{
		if(vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_MAX;
}


template <class T>
int** Graph<T>::getW(){
	return W;
}


template <class T>
void Graph<T>::mapAirports(){
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();

	for(; it!=ite; it++)
		if((*it)->info->hasAirport())
			airport_citys.pushback(*it);
}


template <class T>
bool Graph<T>::allVisited(){
	typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
	typename vector<Vertex<T> *>::iterator ite= vertexSet.end();

	for(; it!=ite; it++)
		if(!(*it)->isVisited() && (*it)->info->isInterestPoint())
			return false;

	return true;
}


template <class T>
void Graph<T>::restoreAvailableTime(){
	available_time = daily_time;
	days++;
}


template <class T>
void Graph<T>::landAndBegin(int daily_time){
	this->daily_time = daily_time;
	available_time = daily_time;
	floydWarshallShortestPath();

	typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
	typename vector<Vertex<T> *>::iterator ite= vertexSet.end();

	int index= 0;
	bool is_possible =false;
	for(; it!=ite; it++){
		if((*it)->info->hasAirport())
		{
			available_time -=(*it)->info->getVisitTime();
			(*it)->setVisited();
			solution.push_back(it);
			if((is_possible=findNextCity(it, index)))
				break;
			else{
				solution.pop_back();
				(*it)->unsetVisited();
				available_time = daily_time;
			}
		}
		index++;
	}
	//TODO back to airport again
}


template <class T>
bool Graph<T>::findNextCity(Vertex<T> *city, int &index){

	if(! vertexSet[index]->info.isInterestPoint)
		restoreAvailableTime();

	if(allVisited())
		return true;



	int size = vertexSet.size();

	int *shortest_travel= cityTravelCosts(index);
	quicksortIndex(shortest_travel, size);

	bool is_possible = false;

	for(int i= 0; i<size; i++)
	{

	}

}


template <class T>
bool Graph<T>::visitFromIpRp(int city_index){

	//todo
	if(available_time>= vertexSet[city_index]->info.getVisitTime()){
		available_time-=vertexSet[city_index]->info.getVisitTime();

	}

	return true;
}


template <class T>
void Graph<T>::testerfunction(){
	cout<<vertexSet[0]->info.getName()<<endl;
}


template <class T>
int* Graph<T>::cityTravelCosts(int city_index){
	int size =vertexSet.size();
	int city_tc[size];
	for(int i =0; i<size; i++){
		if(vertexSet[i]->info.isInterestPoint() && !vertexSet[i]->isVisited())
			city_tc[i]= W[city_index][i];
		else
			city_tc[i]= INT_MAX;
	}
	return city_tc;
}


template<class T>
int* Graph<T>::restingTravelCosts(int city_index){
	int size =vertexSet.size();
	int resting_tc[size];
	for(int i =0; i<size; i++){
			if(vertexSet[i]->info.isRestingPlace())
				resting_tc[i]= W[city_index][i];
			else
			resting_tc[i]= INT_MAX;
		}
	return resting_tc;
}


template <class T>
vector<int> Graph<T>::getIpUnvisited(){
	// return a vector with interest points yet to visit
	vector<int> ip_u;
	for(int i =0; i<vertexSet.size(); i++){
		if(vertexSet[i]->info.isInterestPoint() && !vertexSet[i]->info.isVisited())
			ip_u.push_back(i);
	}
	return ip_u;
}


template <class T>
vector<int> Graph<T>::getBestCityTo(int city_index){
	int size = vertexSet.size();
	int *order_by_cost;
	vector<int> citys_index;

	order_by_cost = quicksortIndex(getMatrixColumn(W, city_index, size), size);

	for(int i =0; i<size; i++)
		citys_index.push_back(order_by_cost[i]);

	return citys_index;
}


#endif /* GRAPH_H_ */
