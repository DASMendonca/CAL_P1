/*
 * AuxFunc.cpp
 *
 *  Created on: 22/04/2014
 *      Author: Daniel
 */

#include "AuxFunc.h"

void quicksortIndex(int arr[], int size){

	//arranges the arr[] with the indexs that have a lowest travel time
	int temp[size];
	for(int i=0; i<size; i++){
		temp[i]=i;
	}

	for(int i =0; i<size; i++)
		for(int j=0; j<size; j++){
			if(arr[j]<arr[i]){
				int temp_ = arr[i];
				arr[i]=arr[j];
				arr[j]= temp_;
				temp[i]=j;
				temp[j]=i;
			}
		}
	for(int i=0; i<size; i++)
		arr[i]= temp[i];
}

void quickSortIndex(vector<int> index, vector<int> vals){
	for(unsigned int i =0; i<index.size(); i++){
		for(unsigned int j =0; j<index.size(); j++){
			if(vals[j] < vals[i]){
				int tmp = vals[i];
				vals[i] = vals[j];
				vals[j] = tmp;
				tmp = index[i];
				index[i] = index[j];
				index[j] = tmp;

			}
		}
	}
}

void getMatrixColumn(int** matrix, int column_index, int nr_rows, int *column){

	for(int i =0; i< nr_rows; i++)
	{
		column[i]= matrix[column_index][i];
	}
}


