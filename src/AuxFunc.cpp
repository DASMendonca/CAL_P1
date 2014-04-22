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
		for(int j=1; j<size; j++){
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

void quickSortIndex(vector<int> vec){}

int* getMatrixColumn(int** matrix, int column_index, int nr_rows){
	int arr[nr_rows];

	for(int i =0; i< nr_rows; i++)
	{
		arr[i]= matrix[column_index][i];
	}

	return arr;
}


