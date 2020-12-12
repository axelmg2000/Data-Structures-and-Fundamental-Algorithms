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

    void swap(int i, int j, vector<T> &tVector) {
        T aux = tVector[i];
        tVector[i] = tVector[j];
        tVector[j] = aux;
    };

    virtual void sort(vector<T> &arr) {};
};

// Class SelectionSort
template <typename T>
class SelectionSort : public Sorter<T> {

    public:
    SelectionSort() {};
    ~SelectionSort() {};

    // For the sort method of SelectionSort a function as argument is used
    void sort(vector<T> &tVector, bool (*compare)(T &a, T &b)) {
        for (size_t i = 0; i < tVector.size() - 1; i++) {
            size_t min = i;
            for (size_t j = i+1; j < tVector.size(); j++) {
                if ((*compare)(tVector[j] < tVector[min]))
                    min = j;
            }
            Sorter<T>::swap(i, min, tVector);
        }        
    };
};

// Class BubbleSort
template <typename T>
class BubbleSort : public Sorter<T> {

    public:
    BubbleSort() {};
    ~BubbleSort() {};

    void sort(vector<T> &tVector) {
        bool bSwap;
        for (size_t i = 0; i < tVector.size(); i++) {
            bSwap = false;
            for (size_t j = 0; j < tVector.size() - i; j++) {
                if(tVector[j] < tVector[j - 1]) {
                    Sorter<T>::swap(j, j - 1, tVector);
                    bSwap = true; // The list is not ordered; we know we swapped elements
                }
              // At the end of loop biggest number will be at the end
            }
            if(!bSwap) // If there was no swap, the list is ordered 
                break; // Exit the method
        }      
    };
};

// Class InsertionSort
template <typename T>
class InsertionSort : public Sorter<T> {

    public:
    InsertionSort() {};
    ~InsertionSort() {};
    void sort(vector<T> &tVector) {
        T key;
        int j;
        for (size_t i = 1; i < tVector.size(); i++) {
            key = tVector[i];
            j = i - 1;
            while(j >= 0 && tVector[j] > key) {
                tVector[j + 1] = tVector[j];
                j--;
            }
            tVector[j + 1] = key;
        }      
    };
};


// Class MergeSort
template <typename T>
class MergeSort : public Sorter<T> {

    public:
    MergeSort() {};
    ~MergeSort() {};

    void sort(vector<T> &tVector) {
        mergeSort(tVector, 0, tVector.size() - 1);
    };

    // Note: unsigned long is used to represent an 8 byte int (0 to 4,294,967,295)
    // Note: size_t guarantees to be big enough to contain the size of the biggest object the host system can handle.


    void mergeSort(vector<T> &tVector, unsigned long iLeft, unsigned long iRight) {
        if(iLeft < iRight) {
            unsigned long iMiddle = iLeft + (iRight - iLeft) / 2; // to avoid overflow // (l + r) / 2;

            mergeSort(tVector, iLeft, iMiddle);
            mergeSort(tVector, iMiddle + 1, iRight);

            merge(tVector, iLeft, iMiddle, iRight);
        }
    }

    void merge(vector<T> &tVector, unsigned long iLeft, unsigned long iMiddle, unsigned long iRight) {
        size_t i, j, k;
        size_t n1 = iMiddle - iLeft + 1;
        size_t n2 = iRight - iMiddle;

        // Create temporary arrays
        T left[n1], right[n2];

        // Copy data to temporary arrays left[] and right[]
        for(i = 0; i < n1; i++)
            left[i] = tVector[iLeft + i];
        for(j = 0; j < n2; j++)
            right[j] = tVector[iMiddle + j + 1];

        // Merge temporary arrays back into tVector [l..r]
        i = 0;
        j = 0;
        k = iLeft;
        while(i < n1 && j < n2) {
            if(left[i] <= right[j]) {
                tVector.at(k) = left[i];
                i++;
            }
            else {
                tVector.at(k) = right[j];
                j++;
            }
            k++;
        } 
        // Copy the remaining elements of left[] (if there are any)
        while(i < n1) {
            tVector.at(k) = left[i];
            i++;
            k++;
        }
        // Copy the remaining elements of right[] (if there are any)
        while(j < n2) {
            tVector.at(k) = right[j];
            j++;
            k++;
        }
    };
};

// Class Quicksort
template<typename T>
class QuickSort : public Sorter<T> {
    public:
    QuickSort() {};
    ~QuickSort() {};

    void sort(vector<T> &tVector, bool (*compare)(T &a, T &b)) {
        quickSort(tVector, 0, tVector.size() - 1, compare);
    };

    void quickSort(vector<T> &tVector, int low, int high, bool (*compare)(T &a, T &b)) {
        if(low < high) {
            // pi refers to partitioning index, tVector.at(p) is now at right place
            int pi = partition(tVector, low, high, compare);

            // Seperately sort elements before partition and after partition
            quickSort(tVector, low, pi - 1, compare);
            quickSort(tVector, pi + 1, high, compare);
        }
    };

    // This function takes last element as pivot, places the pivot element at its correct
    // position in sorted vector, and places all smaller (than pivot) to left of pivot 
    // and all greater (than pivot) to right of pivot
    int partition(vector<T> &tVector, int low, int high, bool (*compare)(T &a, T &b)) {
        T pivot = tVector.at(high); // pivot
        int i = low - 1; // Index of smaller element

        for(int j = low; j <= high - 1; j++) {
            // If current element is smaller than the pivot
            if((*compare)(tVector.at(j), pivot)) {
                i++; // Increment index of smaller element
                Sorter<T>::swap(i, j, tVector);
            }
        }
        Sorter<T>::swap(i + 1, high, tVector);
        return(i + 1);
    };
};
#endif