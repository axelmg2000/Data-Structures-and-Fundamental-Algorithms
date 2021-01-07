// Developed by: Axel Mercado Gasque
// Date: December 15th 2020

/*--------------
Development of an Abstract Data Type (ADT) that has the implementation of
four common search algorithms.
    1. Sequential search
    2. Ordered sequential search 1
    3. Ordered sequential search 2
    4. Binary search
----------------*/

// Header guards
#ifndef Search_hpp
#define Search_hpp

// Declaration of utilized libraries
#include <iostream>
#include <vector>
using namespace std;

// Declaration of ADT and implementation of search algorithms
template <typename T> // Generic programming so that different ADT's can be searched
class Search {
// Note: Since generic programming is being used, a comparison function as argument is used for the sequential search algorithm
// Explanation: In case the Search class is used for an ADT to which the "==" or "<, >" operators are not defined, a comparison 
// function can be used to compare the ADT instances as desired
    public:
        Search() {};
        ~Search() {};

        // Sequential search algorithm
        // Time complexity: O(n)
        int sequentialSearch(vector<T> tVector, T tElement, bool (*compare)(T &adtInstance1, T &adtInstance2)) {
            for(int index = 0; index < tVector.size(); index++) {
                if((*compare)(tElement, tVector.at(index)))
                    return index;
            }
            return -1;
        };

        // Ordered sequential search 1 algorithm
        // Time complexity: O(n)
        int orderedSequentialSearch1(vector<T> tVector, T tElement) {
            int index = 0;
            bool currentElementGreater = false;
            while(index < tVector.size()) {
                // First, we need to check if the current element is bigger than the element to find
                if(tElement < tVector.at(index))
                    return -1;
                if(tElement == tVector.at(index))
                    return index;
                index++;
            }
            return -1;
        };

        int busquedaSecuencialOrdenada2(int iNum) {int c;};

        // Binary search algorithm
        // Time complexity: O(log(n))
        int binarySearch(vector<T> tVector, T tElement, int low, int high) {
            if(low < high) {
                int middle = (high + low) / 2;
                if(tElement == tVector.at(middle))
                    return middle;
                else if(tElement < tVector.at(middle))
                    return binarySearch(tVector, tElement, low, middle - 1);
                else
                    return binarySearch(tVector, tElement, middle + 1, high);  
            }
            return -1;
        }
        int binarySearch(vector<T> tVector, T tElement) {
            return binarySearch(tVector, tElement, 0, tVector.size());
        };
        

};


#endif


/*
int Busqueda::busquedaSecuencialOrdenada2(int iNum) {
  if(iNum < elementos.at(0) || iNum > elementos.at(elementos.size() - 1))
    return -1; // if number is smaller than the smallest or larger than the largest, exit
  for(int i = 100; i < elementos.size(); i += 100) { // loop 100 by 100
    if(iNum == elementos.at(i))
      return i;
    else if(iNum > elementos.at(i))
      int c;
    else { // if number is less than ith element
      if(iNum == elementos.at(i - 50))
        return i - 50;
      else if(iNum > elementos.at(i - 50)) { // if number larger than i - 50 th element
        for(int j = i - 49; j < i; ++j) {
          if(iNum == elementos.at(j))
            return j;
        }
        return -1;
      }
      else { // if number smaller than i - 50 th element
        for(int j = i - 100; j < i - 51; ++j) {
          if(iNum == elementos.at(j))
            return j;
        }
        return -1;
      }
    }
    
  }
    
}
*/