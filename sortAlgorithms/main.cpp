#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include "sorter.h"
#include "mytimer.h"

using namespace std;

template <typename T>
void print_vector(vector<T> tVector, int n) {
    for(size_t i = 0; i < tVector.size() && i < n; ++i) {
        cout << tVector[i] << ",";
    }
    cout << endl;
}

template <typename T>
void compare_vectors(vector<T> a, vector<T> b, string message = "") {
    cout << endl << message << " ";
    // check if equal
    if (a == b)
        cout << "The implementation is correct" << endl;
    else
        cout << "The implementation is not correct" << endl;

}


template <typename T>
bool compare_lessthan(T &a, T &b) {
    return a < b;
}




int main() {

    int count;
    cout << "Enter array size: ";
    cin >> count;

    // generate a random vector array of float of size count
    vector<float> arr_f;
    for (size_t i = 0; i < count; i++)
    {
        arr_f.push_back((float)rand() / RAND_MAX);
    }

    // create copies of original vector to be sorted
    vector<float> arr_1(arr_f);
    vector<float> arr_2(arr_f);
    vector<float> arr_3(arr_f);
    vector<float> arr_4(arr_f);
    vector<float> arr_5(arr_f);
    
    /*
    // get a baseline using std::sort
    DECLARE_TIMING(t);
    START_TIMING(t);
    std::sort(arr_f.begin(), arr_f.end());
    STOP_TIMING(t);
    SHOW_TIMING(t, "std::sort");
    cout << endl;
    */

    /*
    // // create instance of SelectionSort
    DECLARE_TIMING(t1);
    START_TIMING(t1);
    SelectionSort<float> selsort;
    selsort.sort(arr_1, &compare_lessthan);
    STOP_TIMING(t1);
    compare_vectors(arr_f, arr_1, "Selection sort");
    SHOW_TIMING(t1, "SelectionSort:");
    cout << endl;
    */

    
    // // create instance of BubbleSort
    /*
    DECLARE_TIMING(t2);
    START_TIMING(t2);
    BubbleSort<float> bubsort;
    bubsort.sort(arr_2);
    STOP_TIMING(t2);
    compare_vectors(arr_f, arr_2, "Bubble sort:");
    SHOW_TIMING(t2, "BubbleSort");
    cout << endl;
    */
    
    /*
    // // create instance of InsertionSort
    DECLARE_TIMING(t3);
    START_TIMING(t3);
    InsertionSort<float> inssort;
    inssort.sort(arr_3);
    STOP_TIMING(t3);
    compare_vectors(arr_f, arr_3, "InsertionSort sort:");
    SHOW_TIMING(t3, "InsertionSort");
    cout << endl;
    */

    /*
    // create instance of Merge
    DECLARE_TIMING(t4);
    START_TIMING(t4);
    MergeSort<float> mergesort;
    mergesort.sort(arr_4);
    STOP_TIMING(t4);
    // compare_vectors(arr_f, arr_4, "Merge sort:");
    SHOW_TIMING(t4, "Merge sort");
    cout << endl;
    */

    /*
    // create instance of Quicksort
    DECLARE_TIMING(t5);
    START_TIMING(t5);
    QuickSort<float> quicksort;
    quicksort.sort(arr_5, &compare_lessthan);
    STOP_TIMING(t5);
    // compare_vectors(arr_f, arr_5, "Quicksort:");
    SHOW_TIMING(t5, "Quicksort");
    cout << endl;
    */

    return 0;

}

