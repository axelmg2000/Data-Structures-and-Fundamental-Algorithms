// Developed by: Axel Mercado Gasque
// Date: September 4th, 2020

/*--------------
Development and analysis of fundamental search and sort algorithms
----------------*/

// Declaration of utilized libraries
#include <iostream>
#include <vector>
#include <time.h> 
using namespace std;

void displayVector(vector<int> intVector) {
    for(size_t i = 0; i < intVector.size(); i++)
        cout << intVector.at(i) << ", ";
    cout << endl;
}

// Selection Sort
// 5 1 4 2
void ordenaIntercambio(vector<int> &intVector) {  // Vector passed by reference, since we want ot modify the actual passed vector

    int iMinNumberPosition, iAuxiliar, iPos;
    for(size_t i = 0; i < intVector.size() - 1; i++) {
        iMinNumberPosition = i;
        for(size_t j = i + 1; j < intVector.size(); j++) {
            if(intVector.at(j) < intVector.at(iMinNumberPosition)) 
                iMinNumberPosition = j;
        }
        iAuxiliar = intVector.at(i);
        intVector.at(i) = intVector.at(iMinNumberPosition);
        intVector.at(iMinNumberPosition) = iAuxiliar;
    }
    
}



int main() {

    vector<int> intVectorRand;
    srand (time(NULL));
    int count = 100, iRandom;
    for(int i = 0; i < count; i++) {
        iRandom = rand() % 100 + 0;
        intVectorRand.push_back(iRandom);
    }

    displayVector(intVectorRand);
    cout << endl;
    ordenaIntercambio(intVectorRand);
    cout << endl;
    displayVector(intVectorRand);

    


    return 0;
}