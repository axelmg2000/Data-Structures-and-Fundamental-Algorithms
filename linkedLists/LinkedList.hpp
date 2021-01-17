// Developed by: Axel Mercado Gasque
// Date: October 1st 2020

/*--------------
Development of an Abstract Data Type (ADT) that has the implementation of the
data structure linked list. Besides, some common methods of linked lists are declared and implemented:
length, printing, appending a node, inserting a node in a given position, eliminating a node, getting 
the value in the node of nth position, counting the nodes, deleting the linked list, inseting a node in a 
sorted linked list (numerical), removing duplicates, and reversing a linked list
----------------*/

// Header guards
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

// Declaration of utilized libraries
#include <stddef.h>
#include <iostream>
#include <vector>
using namespace std;

// Declaration of ADT for Linked List node
template <class T> // Generic programming so that the Linked List node ADT can be used for different ADT's
class Node {

  private:
      T val;
      Node<T> *next;

  public:
      ~Node<T>() {};
      Node<T>(T value) {
        val = value;
        next = NULL;
      }
      Node<T>(T pVal, Node<T> *pNext) {
          val = pVal;
          next = pNext;
      };

      T get_val() {return val;};
      void set_val(T pVal) {val = pVal;};
      Node<T> *get_next() {return next;};
      void set_next(Node<T> *pNext) {next = pNext;};
};

// Declaration of ADT for Linked List
template <class T> //Generic programming so that the Linked List ADT can be used for different ADT's
class LinkedList {

  protected:
      Node<T> *head;

  public:
      ~LinkedList() {
          // to be implemented
      };
      LinkedList() {
          head = NULL;
      };

      // Method that returns number of nodes in linked list
      // Time complexity: O(n)
      int length() {
          int length = 0;
          Node<T> *ptr = head;
          while (ptr != NULL) {
              length++;
              ptr = ptr->get_next();
          }
          return length;
      };

      // Method that prints values of nodes in linked list
      // Time complexity: O(n)
      void print() {
          Node<T> *ptr = head;
          while (ptr != NULL) {
              cout << ptr->get_val() << ", ";
              ptr = ptr->get_next();
          }
          cout << endl;        
      }

      // Method that inserts a node in the beginning of linked list
      // Time complexity: O(1)
      void push(T pVal) {
          Node<T> *node = new Node<T>(pVal, head);
          head = node;
      };

      // Method that inserts a node at the end of linked list
      // Time complexity: O(n)
      void append(T pVal) {
          Node<T> *ptr = head;            
          while (ptr->get_next() != NULL) {
              ptr = ptr->get_next();
          }
          Node<T> *node = new Node<T>(pVal, NULL);
          ptr->set_next(node);
      };

      // Method that inserts a node in a given position in linked list
      // Time complexity: O(n)
      int insert_item(T pVal, int index) {
          if (index > length())
              return -1;
          if (index < 0)
              return -2;
          if (index == 0) {
              push(pVal);
              return 1;
          }

          int i = 0;
          Node<T> *ptr = head;
          Node<T> *pre = NULL;
          while (ptr != NULL && index > i) {
              pre = ptr;
              ptr = ptr->get_next();
              i++;
          }
          Node<T> *node = new Node<T>(pVal, ptr);
          pre->set_next(node);
          return 1;
      };

      // Method that returns true or false depending on if linked list is empty or not
      // Time complexity: O(1)
      bool is_empty() {    
          return head == NULL;
      };

      // Method that deletes the node of the given position in linked list
      // Time complexity: O(n)
      int delete_item(int index) {
          if (is_empty())
              return -1;
          if (index >= length())
              return -1;
          if (index < 0)
              return -2;
          if (index == 0) {
              Node<T> *temp = head;
              head = head->get_next();
              delete temp;
              return 1;
          }

          int i = 0;
          Node<T> *ptr = head;
          Node<T> *pre = NULL;
          while (ptr->get_next() != NULL && index > i) {
              pre = ptr;
              ptr = ptr->get_next();
              i++;
          }
          pre->set_next(ptr->get_next());
          delete ptr;
          return 1;
      };

      // Method that gets the value of node in given position in linked list
      // Time complexity: O(n)
      int get_nth(int index, T &item) {
          if (index < 0)
              return -1;
          if (index >= length())
              return -2;
              
          int i = 0;
          Node<T> *ptr = head;
          while (ptr->get_next() != NULL && index > i) {
              ptr = ptr->get_next();
              i++;
          }
          item = ptr->get_val();
          return 1;
      };

      // *************** //
      // Métodos adicionales - Act 2.1
      // *************** //

      // Número de veces que aparece val en la lista
      // Complejidad temporal: O(n)
      int Count(T val) {
        Node<T> *ptr = head; // Apuntador a nodo que apunta a lo que apunta head
        int countVal = 0;
        while(ptr != NULL) { // Mientras se apunte a un nodo válido
          if(ptr->get_val() == val) // Si el valor del nodo apuntado es igual a val, 
            countVal++; // val se incrementa
          ptr = ptr->get_next(); // ahora ptr apunta al siguiente nodo en la lista
        }
        return countVal;
      };

      // Escriba una función DeleteList () que tome una lista, libere toda su memoria y establezca su puntero principal en NULL (la lista vacía).
      // Complejidad temporal: O(n)
      void DeleteList() {
        Node<T> *ptr = head; // Apuntador a nodo que apunta a lo que apunta head
        while(ptr != NULL) { // Mientras se apunte a un nodo válido
          Node<T> *nextn = ptr->get_next();
          delete ptr;
          ptr = nextn; 
        }
        head = NULL;
      };


      // Escriba una función SortedInsert() que, dada una lista ordenada en orden creciente y un nodo, inserte el nodo en la posición ordenada correcta en la lista. 
      // Complejidad temporal: O(n)
      void SortedInsert(Node<T> *newNode) {
        if(is_empty()) {
          head = newNode;
          return;
        }

        Node<T> *ptr = head;
        if(newNode->get_val() <= head->get_val()) {
          head = newNode;
          newNode->set_next(ptr);
          return;
        }

        while(newNode->get_val() > ptr->get_val()) {
          if(ptr->get_next() != NULL) {
            if(newNode->get_val() <= ptr->get_next()->get_val()) {
              Node<T> *ptrAux = ptr->get_next();
              ptr->set_next(newNode);
              newNode->set_next(ptrAux);
              return;
            }
            else 
              ptr = ptr->get_next();
          }
          else {
            ptr->set_next(newNode);
            newNode->set_next(NULL);
            return;
          }
        }   
      };

      // Escriba una función RemoveDuplicates() que toma una lista ordenada en orden creciente y elimina los nodos duplicados de la lista. Idealmente, la lista solo debería recorrerse una vez.
      // Complejidad temporal: O(n)
      void RemoveDuplicates() {
        Node<T> *ptr = head;
        while (ptr != NULL) {
            if (ptr->get_next() != NULL && ptr->get_val() == ptr->get_next()->get_val()) {
                Node<T> *temp = ptr->get_next()->get_next();
                delete ptr->get_next();
                ptr->set_next(temp);
            }
            else {
                ptr = ptr->get_next();
            }            
        }
      };

      // Escriba una función Reverse() iterativa que invierta una lista enlazada reorganizando todos los punteros .next y el puntero head. Idealmente, Reverse () solo debería necesitar hacer una pasada de la lista. 
      // Complejidad temporal: O(n)
      void Reverse() {
        if(head == NULL) return;
        Node<T> *prevPtr = NULL, *ptr = NULL, *nextPtr = NULL;
        ptr = head;
        while(ptr != NULL){
          nextPtr = ptr->get_next();
          ptr->set_next(prevPtr);
          prevPtr = ptr;
          ptr = nextPtr;
        }
        head = prevPtr;
      };

};

#endif