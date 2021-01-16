// Developed by: Axel Mercado Gasque
// Date: October 20th 2020

/*--------------
Development of an Abstract Data Type (ADT) that has the implementation of the
data structure binary search tree, and some common methods of BSTs: inserting a node,
finding a node, deleting a node, finding the sucessor of a node, and printing the nodes
of a BST
----------------*/

// Header guards
#ifndef BST_hpp
#define BST_hpp

// Declaration of utilized libraries
#include <iostream>
using namespace std;

// Declaration of ADT for Binary Searche Tree Node
template <class T> // Generic programming so that the BTreeNode ADT can be used for different ADT's
class BTreeNode 
{
private:
    T val;
    BTreeNode<T>* left;
    BTreeNode<T>* right;

public:
    ~BTreeNode<T>() {};
    BTreeNode<T>() {};
    BTreeNode<T>(T _val) {
        val = _val;
        left = NULL;
        right = NULL;
    };
    BTreeNode<T>(T _val, BTreeNode<T> *_left, BTreeNode<T> *_right) {
        val = _val;
        left = _left;
        right = _right;
    };

    T get_val() {return val;};
    BTreeNode<T>* get_left() {return left;};
    BTreeNode<T>* get_right() {return right;};

    void set_val(T _val) {val = _val;};
    void set_left(BTreeNode<T> * node) {left = node;};
    void set_right(BTreeNode<T> * node) {right = node;};
};

// Declaration of ADT for Binary Searche Tree
template <class T> // Generic programming so that the BST ADT can be used for different ADT's
class BinarySearchTree
{
private:
    BTreeNode<T> *root;

public:
    ~BinarySearchTree() {};
    BinarySearchTree() { root = NULL;};

    // Method to find a node in the BST
    // Time complexity: O(log(n)) if BST is balanced, otherwise O(n)
    BTreeNode<T>* find(T val)
    {
        BTreeNode<T> *ptr = root;
        while(ptr != NULL)
        {
            if (ptr->get_val() == val)
                return ptr;

            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }
        return NULL;
    };

    // Method to insert a node in the BST
    // Time complexity: O(log(n)) if BST is balanced, otherwise O(n)
    bool insert_node(T val)
    {
        BTreeNode<T> *ptr = root;
        BTreeNode<T> *pre = NULL;

        while(ptr != NULL)
        {
            if (ptr->get_val() == val)
                return false;
            pre = ptr;
            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }

        BTreeNode<T> *new_node = new BTreeNode<T>(val);

        if (pre == NULL)
            root = new_node;
        else
        {
            if (pre->get_val() < val)
                pre->set_right(new_node);
            else
                pre->set_left(new_node);            
        }
        return true;
    };

    // Method to recursively insert a node in the BST
    // Time complexity: O(log(n)) if BST is balanced, otherwise O(n)
    BTreeNode<T>* insert_node_recursive(BTreeNode<T>* node, T val)
    {
        if (node == NULL)
            return new BTreeNode<T>(val);

        if (val < node->get_val())
            node->set_left(insert_node_recursive(node->get_left(), val));
        else
            node->set_right(insert_node_recursive(node->get_right(), val));

        return node;
    };

    bool insert_node_recursive(T val)
    {
        root = insert_node_recursive(root, val);
        return true;
    };

    // Method to find the succesor node (if exists) of a given node in the BST
    // Time complexity: O(log(n)) if BST is balanced, otherwise O(n)
    BTreeNode<T>* sucessor(BTreeNode<T> *node)
    {
        BTreeNode<T> *ptr = node->get_right();
        while (ptr->get_left() != NULL)
        {
            ptr = ptr->get_left();
        }
        return ptr;        
    };

    // Method to delete a given node from the BST
    // Time complexity: O(log(n)) if BST is balanced, otherwise O(n)
    BTreeNode<T>* delete_node(BTreeNode<T>* node, int key) 
    { 
        // base case
        if (node == NULL) return node; 
    
        
        // if value of node to eliminate is smaller than value of node
        // then it is in the left subtree
        if (key < node->get_val()) 
            node->set_left(delete_node(node->get_left(), key)); 
    
        
        // if value of node to eliminate is greater than value of node
        // then it is in the right subtree
        else if (key > node->get_val()) 
            node->set_right(delete_node(node->get_right(), key)); 
    
        
        // if value to eliminate is equal to value of node
        // then this is the node we want to eliminate
        else
        { 
            
            // nodes with only one child or without children
            if (node->get_left() == NULL) 
            { 
                BTreeNode<T> *temp = node->get_right(); 
                delete node; 
                return temp; 
            } 
            else if (node->get_right() == NULL) 
            { 
                BTreeNode<T> *temp = node->get_left(); 
                delete node;
                return temp; 
            } 
    
            // node with two children, then we obtain sucessor 
            BTreeNode<T> *temp = sucessor(node);
    
            
            // copy the value of the sucessor of the node that has the element we want to eliminate
            node->set_val(temp->get_val()); 
    
            // eliminate sucessor
            node->set_right(delete_node(node->get_right(), temp->get_val()));
        } 
        return node; 
    };

    void delete_node(T val)
    {
        root = delete_node(root, val);
    };

    // Method to print the values of the nodes of the BST
    // Time complexity: O(n)
    void print_preorder(BTreeNode<T> *node)
    {
        if (node != NULL)
        {
            cout << node->get_val() << ", ";
            print_preorder(node->get_left());
            print_preorder(node->get_right());
        }
    };

    void print_preorder()
    {
        print_preorder(root);
        cout << endl;
    }

    
    
};

#endif