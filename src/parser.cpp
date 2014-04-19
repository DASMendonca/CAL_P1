#include "parser.h"

vector<vector<string> > readVertex(string filename) {
	ifstream file(filename.c_str());
	vector<vector<string> > vertexlist;
	vector<string> temp;
	string info;
	while(file.good()) {
		temp.clear();
		for (int i = 0; i < 3; i++) {
			getline(file, info, ';');
			temp.push_back(info);
		}
		getline(file, info);
		temp.push_back(info);
		vertexlist.push_back(temp);
	}
	file.close();
	return vertexlist;
}

vector<vector<string> > readEdge(string filename, int nvertex) {
	ifstream file(filename.c_str());
	vector<vector<string> > edgelist;
	vector<string> temp;
	string info;
	while(file.good()) {
		temp.clear();
		for (int i = 0; i < nvertex; i++) {
			getline(file, info);
			temp.push_back(info);
		}
		edgelist.push_back(temp);
	}
	file.close();
	return edgelist;
}
