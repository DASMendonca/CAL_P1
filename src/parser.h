#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<string> > readVertex(string filename);

vector<vector<string> > readEdge(string filename, int nvertex);

#endif
