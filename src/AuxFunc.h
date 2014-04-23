/*
 * AuxFunc.h
 *
 *  Created on: 22/04/2014
 *      Author: Daniel
 */

#ifndef AUXFUNC_H_
#define AUXFUNC_H_

#include <vector>

using namespace std;

void quicksortIndex(int arr[], int size);

void quickSortIndex(vector<int> index, vector<int> vals);

int* getMatrixColumn(int** matrix, int column_index, int nr_rows);


#endif /* AUXFUNC_H_ */
