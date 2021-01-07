// Developed by: Axel Mercado Gasque
// Date: December 15th 2020

/*--------------
This file contains a test of the methods declared and implemented in the file "Search.cpp"
Besides, some additional methods (generate a vector of random and consecutive integers) 
are declared and implemented. 
----------------*/

// Declaration of utilized libraries
#include <iostream>
#include "Search.cpp"
#include "mytimer.h"

// Libraries used to generate random number
#include <stdio.h>     
#include <stdlib.h>  
#include <time.h>
//
using namespace std;


// Declaration and implementation of additional methods

// Method that receives a number and a vector, and generatesto generate a vector of random and consecutive integers
void randomConsecutiveInts(vector<int> &intVector, int n) {
    srand (time(NULL));
    int iRandom;
    for(int i = 0; i < n; i++) {
        iRandom = rand() % INT_MAX + i; // Generate a random integer between i and INT_MAX
        intVector.push_back(iRandom);
    }
}

// Equality comparison method
template <typename T>
bool equalityComparison(T a, T b) {
    return a == b;
}



// Code start
int main() {
   
   vector<int> testVector;
   int size;
   cout << "Enter the the size of the vector" << endl;
   cin >> size;
   randomConsecutiveInts(testVector, size); // Generate vector of random consecutive integers

   Search<int> search; // Instance of Search object
   int searchNum;
   cout << "Enter the number that you want to search" << endl;
   cin >> searchNum;


   // Declare timing and search number using sequential search 
   DECLARE_TIMING(sequentialSearch);
   START_TIMING(sequentialSearch);
   cout << search.sequentialSearch(testVector, searchNum, equalityComparison) << endl;
   STOP_TIMING(sequentialSearch);
   SHOW_TIMING(sequentialSearch, "Sequential Search");
   cout << endl;

   // Declare timing and search number using ordered sequential search 
   DECLARE_TIMING(orderedSequentialSearch1);
   START_TIMING(orderedSequentialSearch1);
   cout << search.orderedSequentialSearch1(testVector, searchNum) << endl;
   STOP_TIMING(orderedSequentialSearch1);
   SHOW_TIMING(orderedSequentialSearch1, "Ordered sequential search 1");
   cout << endl;

   // Declare timing and search number using binary search 
   DECLARE_TIMING(binarySearch);
   START_TIMING(binarySearch);
   cout << search.binarySearch(testVector, searchNum) << endl;
   STOP_TIMING(binarySearch);
   SHOW_TIMING(binarySearch, "Binary search");
   cout << endl; 




  
}