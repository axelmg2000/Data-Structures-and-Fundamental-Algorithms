#ifndef sorter_h
#define sorter_h

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Sorter {

    public:
        Sorter() {};
        ~Sorter() {};

        void swap(int i, int j, vector<T> &arr) {
            T tAuxiliar = arr[i];
            arr[i] = arr[j];
            arr[j] = tAuxiliar;

        };

        virtual void sort(vector<T> &arr) {};

};

template <typename T>
class selectionSort : public Sorter<T> {

    public:
        selectionSort() {};
        ~selectionSort() {};

        void sort(vector<T> &arr) {
            for(size_t i = 0; i < arr.size() - 1; ++i) {
                
                size_t min = i;
                for(size_t j = i + 1; j < arr.size(); ++j) {
                    if(arr[j] < arr[min])
                        min = j;
                }
                Sorter<T>::swap(i, min, arr);
            }
        };

};


#endif