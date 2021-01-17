// Developed by: Axel Mercado Gasque
// Date: October 1st 2020

/*--------------
This file contains a test of some methods implementes in the file "LinkedList.hpp"
----------------*/

// Declaration of utilized libraries
#include <iostream>
#include <cmath>
#include "LinkedList.hpp"

using namespace std;


int main() {
  
 
  LinkedList<int> list;
  
  list.push(2);
  list.append(4);
  list.append(5);
  list.append(6);

  list.print();
  
  
  Node<int> node(8);
  list.SortedInsert(&node);
  list.append(10);
  list.append(10);
  list.append(10);
  list.print();

  cout << list.Count(10) << endl;

  list.RemoveDuplicates();
  list.Reverse();

  list.print();

 

 

  

  
  

  
  
  

  
  
 
  
}