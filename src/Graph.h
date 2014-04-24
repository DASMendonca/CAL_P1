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
	bool selectAction(int city_index);
	bool visitRestGo(int city_index);
	bool visitGo(int city_index);
	bool restGo(int city_index);
	bool travel(vector<int> destinations, int city_index);
	bool toAirportFrom(int city_index);
	bool selectReturnAtion(int city_index,int airport_city);
	bool backFromRp(int city_index, int airport_city);
	bool backFromCity(int city_index, int airport_city);


	void updateEdges();
	void floydWarshallShortestPath();
	void setDailyTime(int time_to_spend);
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
	vector<int> getAirportCitys();
	vector<int> cityTravelCosts(int city_index);
	vector<int> cityTravelCosts(int city_index, vector<int> indexs);
	vector<int> restingTravelCosts(int city_index);
	vector<int> restingTravelCosts(int city_index, vector<int> indexs);
	vector<int> getCostsFromTo(int city_index, vector<int> destinations);

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
bool Graph<T>::allVisited(){
	typename vector<Vertex<T> *>::iterator it = vertexSet.begin();
	typename vector<Vertex<T> *>::iterator ite= vertexSet.end();

	for(; it!=ite; it++)
		if(!(*it)->isVisited() && (*it)->info.isInterestPoint())
			return false;

	return true;
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
		if((*it)->info.hasAirport())
		{
			if((is_possible=selectAction(index)))
				break;
			else{
				available_time = daily_time;
			}
		}
		index++;
	}

	for(int i =0; i<solution.size(); i++)
		cout<<solution[i]->info.getName()<<endl;

	cout<<"days: "<<days<<endl<<"hours: "<<daily_time - available_time<<endl;

	return is_possible;
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
vector<int> Graph<T>::cityTravelCosts(int city_index, vector<int> indexs){
	vector<int> city_tc;
	for(int i=0; i<indexs.size(); i++)
	{
		city_tc.push_back(W[city_index][indexs[i]]);
	}
	return city_tc;
}


template <class T>
vector<int> Graph<T>::cityTravelCosts(int city_index){
	vector<int> city_tc;
	int size =vertexSet.size();
	for(int i =0; i<size; i++){
		if(vertexSet[i]->info.isInterestPoint() && !vertexSet[i]->isVisited() && i != city_index)
			city_tc.push_back( W[city_index][i]);
		else
			city_tc.push_back(INT_MAX);
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


template<class T>
vector<int> Graph<T>::restingTravelCosts(int city_index, vector<int> rest_indexs){
	int size =rest_indexs.size();
	vector<int> resting_tc;
	for(int i =0; i<size; i++)
	{
		resting_tc.push_back(W[city_index][rest_indexs[i]]);
	}
	return resting_tc;
}


template <class T>
vector<int> Graph<T>::getIpUnvisited(){
	// return a vector with interest points yet to visit
	vector<int> ip_u;
	for(int i =0; i<vertexSet.size(); i++)
		if(vertexSet[i]->info.isInterestPoint() && !vertexSet[i]->isVisited())
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
vector<int> Graph<T>::getAirportCitys(){
	vector<int> ac;
	for(int i = 0; i<vertexSet.size(); i++)
		if(vertexSet[i]->info.hasAirport())
			ac.push_back(i);

	return ac;
}


template <class T>
vector<int> Graph<T>::getBestCityTo(int city_index){
	int size = vertexSet.size();
	int *order_by_cost;
	vector<int> citys_index;

	int column[size];
	getMatrixColumn(W, city_index, size, column);
	order_by_cost = quicksortIndex(column, size);

	for(int i =0; i<size; i++)
		citys_index.push_back(order_by_cost[i]);

	return citys_index;
}


template <class T>
vector<int> Graph<T>::getCostsFromTo(int city_index, vector<int> destinations){
	vector<int> costs;
	for(int i=0; i<destinations.size(); i++)
	{
		costs.push_back(W[city_index][destinations[i]]);
	}
	return costs;
}


template <class T>
bool Graph<T>::restGo(int city_index){
	int tmp_available_time= available_time;
	available_time = daily_time;
	days++;
	solution.push_back(vertexSet[city_index]);

	vector<int> unvisited_ip = getIpUnvisited();
	vector<int> city_tc = cityTravelCosts(city_index, unvisited_ip);
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
	vertexSet[city_index]->setVisited();

	if(allVisited()){
		if(toAirportFrom(city_index))
			return true;
		return false;
	}

	vector<int> unvisited_ip = getIpUnvisited();
	vector<int> city_tc = cityTravelCosts(city_index, unvisited_ip);
	filterAndOrder(unvisited_ip, city_tc);
	//now we have the unvisited_ip ordered by the least costing travel

	if(travel(unvisited_ip, city_index))
		return true;

	//but now, we may have a resting place near, and using it may be usefull
	unvisited_ip = getRestingPlaces();
	city_tc = restingTravelCosts(city_index, unvisited_ip);
	//todo restingTravelCosts(city_index, vector<int> resting_indexs);
	filterAndOrder(unvisited_ip, city_tc);

	if(travel(unvisited_ip, city_index))
		return true;


	vertexSet[city_index]->unsetVisited();
	available_time = tmp_av_time;
	solution.pop_back();

	return false;

}


template <class T>
bool Graph<T>::visitRestGo(int city_index){
	int visit_time = vertexSet[city_index]->info.getVisitTime();
	int tmp_av_time = available_time;

	//as it is a resting place, it certanly will be possible to visit
	solution.push_back(vertexSet[city_index]);
	vertexSet[city_index]->setVisited();

	vector<int> unvisited_ip = getIpUnvisited();
	vector<int> city_tc = cityTravelCosts(city_index, unvisited_ip);
	filterAndOrder(unvisited_ip, city_tc);



	if(available_time > visit_time)
	{
		available_time -= visit_time;
		if(allVisited()){
			if(toAirportFrom(city_index))
				return true;
			return false;
		}


		if(travel(unvisited_ip, city_index))
			return true;
		else
		{
			available_time = daily_time;
			days++;
			if(travel(unvisited_ip, city_index))
				return true;
		}
	}
	else
	{
		available_time = daily_time;
		days++;
		available_time -= visit_time;

		if(allVisited()){
			if(toAirportFrom(city_index))
				return true;
			return false;
		}

		if(travel(unvisited_ip, city_index))
			return true;
	}

	vertexSet[city_index]->unsetVisited();
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
bool Graph<T>::toAirportFrom(int city_index){

	vector<int> airport_citys = getAirportCitys();
	vector<int> tc = getCostsFromTo(city_index, airport_citys);
	quickSortIndex(airport_citys, tc);
	int tmp_av_t = available_time;

	for(int i =0; i< airport_citys.size(); i++)
	{
		if(selectReturnAtion(city_index, airport_citys[i]))
			return true;
	}
	available_time =tmp_av_t;
	return false;
}


template <class T>
void Graph<T>::filterAndOrder(vector<int> destinations, vector<int> city_tc){
	int des_size = destinations.size()-1;
	int control = destinations[des_size-1];
	int size = city_tc.size() -1;

	//filter
	for(int i =size; i>=0; i--)
	{
		if(i != control)
		{
			city_tc.erase(city_tc.begin() + i);
		}
		else{
			des_size--;
			control = destinations[des_size];
		}
	}

	//order
	for(int i =0; i<destinations.size(); i++){
		for(int j =0; j<destinations.size(); j++)
		{
			if(city_tc[j] < city_tc[i])
			{
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


template <class T>
bool Graph<T>::selectReturnAtion(int city_index,int airport_city){
	if(vertexSet[city_index]->info.isRestingPlace())
		return backFromRp(city_index, airport_city);

	return backFromCity(city_index, airport_city);
}


template <class T>
bool Graph<T>::backFromRp(int city_index, int airport_city){
	if(vertexSet[city_index]->info.hasAirport())
		return true;

	int tc = W[city_index][airport_city];
	int tmp_av_t = available_time;

	//go directly
	if(available_time >= tc)
	{
		solution.push_back(vertexSet[airport_city]);
		available_time -= tc;
		return true;
	}

	//rest and go
	available_time = daily_time;
	days++;

	if(available_time>= tc)
	{
		solution.push_back(vertexSet[airport_city]);
		available_time -= tc;
		return true;
	}


	//go through best intermidiate
	int intermediate_index = P[city_index][airport_city];
	if(intermediate_index <=0)
	{
		days--;
		available_time = tmp_av_t;
		return false;
	}
	//there is an intermediate
	if(vertexSet[intermediate_index]->info.isRestingPlace())
	{
		available_time -= W[city_index][intermediate_index];
		solution.push_back(vertexSet[intermediate_index]);
		if(selectReturnAtion(intermediate_index, airport_city))
			return true;

		solution.pop_back();
		available_time = tmp_av_t;
	}

	return false;
}


template <class T>
bool Graph<T>::backFromCity(int city_index, int airport_city){
	if(vertexSet[city_index]->info.hasAirport())
		return true;

	int tc = W[city_index][airport_city];
	int tmp_av_t = available_time;

	if(available_time >=tc)
	{
		solution.push_back(vertexSet[airport_city]);
		available_time -= tc;
		return true;
	}

	int intermediate_index = P[city_index][airport_city];
	if(intermediate_index <=0)
	{
		available_time = tmp_av_t;
		return false;
	}
	//there is an intermediate
	if(vertexSet[intermediate_index]->info.isRestingPlace())
	{
		available_time -= W[city_index][intermediate_index];
		solution.push_back(vertexSet[intermediate_index]);
		if(selectReturnAtion(intermediate_index, airport_city))
			return true;

		solution.pop_back();
		available_time = tmp_av_t;
	}

	return false;
}
#endif /* GRAPH_H_ */
