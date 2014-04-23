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

	bool landAndBegin(int daily_time);
	bool findNextCity(Vertex<T> *city, int present_index);
	bool selectAction(int city_index);
	bool visitFromIpRp(int city_index);
	bool visitFromRp(int city_index, int next_index);
	bool visitRestGo(int city_index);
	bool visitGo(int city_index);
	bool restGo(int city_index);
	bool travel(vector<int> destinations, int city_index);



	void updateEdges();
	void floydWarshallShortestPath();
	void setDailyTime(int time_to_spend);
	void setDaily_time(int time);
	void restoreAvailableTime();
	void mapAirports();
	void testerfunction();
	void filterAndOrder(vector<int> unvisited_ip, vector<int> city_tc);
	string getInfo(Vertex<T> city);

	int edgeCost(int vOrigIndex, int vDestIndex);
	int getTravelTime(Vertex<T> from, Vertex<T> to);
	int getDailyTime();
	int findIndexVertex(string info);

	int** getW();
	vector<Vertex<T> > getSolution();
	vector<Vertex<T> *> getVertexSet();
	vector<int> getBestCityTo(int city_index);
	vector<int> getIpUnvisited();
	vector<int> getRestingPlaces();
	vector<int> cityTravelCosts(int city_index);
	vector<int> restingTravelCosts(int city_index);
	vector<int> getCostsFrom(vector<int> citys);
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
bool Graph<T>::landAndBegin(int daily_time){
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
			if((is_possible=selectAction(index)))
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
bool Graph<T>::selectAction(int city_index){
	bool isIp = vertexSet[city_index]->info.isInterestPoint();
	bool isRp = vertexSet[city_index]->info.isRestingPlace();
	bool visited = vertexSet[city_index]->isVisited();

	bool possible = false;

	if(isIp)
	{
		if(!visited)
		{
			if(isRp)
				possible = visitRestGo(city_index);	//it may not be needed to rest
			else
				possible = visitGo(city_index);
		}
		else if(isRp)
			possible = restGo(city_index);
	}
	else
	{
		possible = restGo(city_index);
	}

	return possible;
}


template <class T>
bool Graph<T>::findNextCity(Vertex<T> *city, int index){

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


/*
 *returns an array with the costs to unvisited Interest Points, visited ones and non IP also in but with INT_MAX
 */
template <class T>
vector<int> Graph<T>::cityTravelCosts(int city_index){
	vector<int> city_tc;
	int size =vertexSet.size();
	for(int i =0; i<size; i++){
		if(vertexSet[i]->info.isInterestPoint() && !vertexSet[i]->isVisited() && i != city_index)
			city_tc.push_back( W[city_index][i]);
		else
			city_tc.push_back[INT_MAX];
	}
	return city_tc;
}


/*
 *returns an array with the costs to every resting place, non rps also in but with INT_MAX
 */
template<class T>
vector<int> Graph<T>::restingTravelCosts(int city_index){
	int size =vertexSet.size();
	vector<int> resting_tc;
	for(int i =0; i<size; i++){
		if(vertexSet[i]->info.isRestingPlace())
			resting_tc.push_back(W[city_index][i]);
		else
			resting_tc.push_back(INT_MAX);
	}
	return resting_tc;
}


template <class T>
vector<int> Graph<T>::getIpUnvisited(){
	// return a vector with interest points yet to visit
	vector<int> ip_u;
	for(int i =0; i<vertexSet.size(); i++)
		if(vertexSet[i]->info.isInterestPoint() && !vertexSet[i]->info.isVisited())
			ip_u.push_back(i);

	return ip_u;
}


template <class T>
vector<int> Graph<T>::getRestingPlaces(){
	vector<int> rp;
	for(int i = 0; i<vertexSet.size(); i++)
		if(vertexSet[i]->info.isRestingPlace())
			rp.push_back(i);

	return rp;
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


template <class T>
bool Graph<T>::restGo(int city_index){
	int tmp_available_time= available_time;
	available_time = daily_time;
	days++;
	solution.push_back(vertexSet[city_index]);

	vector<int> unvisited_ip = getIpUnvisited();
	vector<int> city_tc = cityTravelCosts(city_index);
	filterAndOrder(unvisited_ip, city_tc);
	//now we have the unvisited_ip ordered by the least costing travel

	if(travel(unvisited_ip, city_index))
		return true;

	available_time = tmp_available_time;
	days--;
	solution.pop_back();
	return false;
}


template <class T>
bool Graph<T>::visitGo(int city_index){
	int visit_time = vertexSet[city_index]->info.getVisitTime();
	if(available_time < visit_time)
		return false;

	int tmp_av_time = available_time;
	available_time -= visit_time;
	solution.push_back(vertexSet[city_index]);

	vector<int> unvisited_ip = getIpUnvisited();
	vector<int> city_tc = cityTravelCosts(city_index);
	filterAndOrder(unvisited_ip, city_tc);
	//now we have the unvisited_ip ordered by the least costing travel

	if(travel(unvisited_ip, city_index))
		return true;

	//but now, we may have a resting place near, and using it may be usefull
	unvisited_ip = getRestingPlaces();
	city_tc = restingTravelCosts(city_index);
	filterAndOrder(unvisited_ip, city_tc);

	if(travel(unvisited_ip, city_index))
		return true;


	available_time = tmp_av_time;
	days--;
	solution.pop_back();

	return false;

}


template <class T>
bool Graph<T>::travel(vector<int> destinations, int city_index){

	for(int i =0; i<destinations.size(); i++){
		int travel_time = W[city_index][destinations[i]];
		if(available_time < travel_time)
			break;

		available_time -= travel_time;

		if(selectAction(destinations[i]))
			return true;

		else
			available_time+=travel_time;
	}

	return false;
}


template <class T>
void Graph<T>::filterAndOrder(vector<int> destinations, vector<int> city_tc){
	int control = destinations[0];
	int ctr_it = 0;

	for(int i =0; i<city_tc.size(); i++){
		if(i != control)
		{
			city_tc.erase(city_tc.begin() + i);
		}
		else{
			ctr_it++;
			control = destinations[ctr_it];
		}
	}

	for(int i =0; i<destinations.size(); i++){
		for(int j =0; j<destinations.size(); j++){
			if(city_tc[j] < city_tc[i]){
				int tmp = city_tc[i];
				city_tc[i] = city_tc[j];
				city_tc[j] = tmp;
				tmp = destinations[i];
				destinations[i] = destinations[j];
				destinations[j] = tmp;

			}
		}
	}
}


#endif /* GRAPH_H_ */
