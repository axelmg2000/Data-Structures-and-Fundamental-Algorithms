#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <iostream>

template <class T>
class BTreeNode 
{
private:
    T val;
    string domain;
    BTreeNode<T>* left;
    BTreeNode<T>* right;

public:
    ~BTreeNode<T>() {};
    BTreeNode<T>() {};
    BTreeNode<T>(T _val, string dom) {
        val = _val;
        domain = dom;
        left = NULL;
        right = NULL;
    };
    BTreeNode<T>(T _val, string dom, BTreeNode<T> *_left, BTreeNode<T> *_right) {
        val = _val;
        domain = dom;
        left = _left;
        right = _right;
    };

    T get_val() {return val;};
    string get_domain() {return domain;};
    BTreeNode<T>* get_left() {return left;};
    BTreeNode<T>* get_right() {return right;};

    void set_val(T _val) {val = _val;};
    void set_domain(string dom) {domain = dom;};
    void set_left(BTreeNode<T> * node) {left = node;};
    void set_right(BTreeNode<T> * node) {right = node;};
};

template <class T>
class BinarySearchTree
{
private:
    BTreeNode<T> *root;

public:
    ~BinarySearchTree() {};
    BinarySearchTree() { root = NULL;};

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

    bool insert_node(T val, string dom)
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

        BTreeNode<T> *new_node = new BTreeNode<T>(val, dom);

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

    BTreeNode<T>* insert_node_recursive(BTreeNode<T>* node, T val, string dom)
    {
        if (node == NULL)
            return new BTreeNode<T>(val, dom);

        if (val < node->get_val())
            node->set_left(insert_node_recursive(node->get_left(), val, dom));
        else if(val > node->get_val())
            node->set_right(insert_node_recursive(node->get_right(), val, dom));
  

        return node;
    };

    bool insert_node_recursive(T val, string dom)
    {
        root = insert_node_recursive(root, val, dom);
        if(root != NULL)
            return true;
        else
            return false;
    };

    BTreeNode<T>* sucessor(BTreeNode<T> *node)
    {
        BTreeNode<T> *ptr = node->get_right();
        while (ptr->get_left() != NULL)
        {
            ptr = ptr->get_left();
        }
        return ptr;        
    };

    BTreeNode<T>* delete_node(BTreeNode<T>* node, int key) 
    { 
        // caso base
        if (node == NULL) return node; 
    
        // si el valor a eliminar es menor que el valor del nodo
        // entonces está en el subarbol izquierdo
        if (key < node->get_val()) 
            node->set_left(delete_node(node->get_left(), key)); 
    
        // si el valor a eliminar es mayor que el valor del nodo
        // entonces está en el subarbol derecho
        else if (key > node->get_val()) 
            node->set_right(delete_node(node->get_right(), key)); 
    
        // si el valor a eliminar es igual que el valor del nodo
        // entonces este es el elemento que queremos eliminar
        else
        { 
            // nodos con solo un hijo o sin hijos
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
    
            // nodo con dos hijos, entonces obtener el sucesor
            BTreeNode<T> *temp = sucessor(node);
    
            // copiar el valor del sucesor al nodo que contiene el elemento a borrar
            node->set_val(temp->get_val()); 
    
            // borrar el sucesor
            node->set_right(delete_node(node->get_right(), temp->get_val()));
        } 
        return node; 
    };

    void delete_node(T val)
    {
        root = delete_node(root, val);
    };

    void print_preorder(BTreeNode<T> *node)
    {
        if (node != NULL)
        {
            std::cout << node->get_domain() << "-" << node->get_val() << ", ";
            print_preorder(node->get_left());
            print_preorder(node->get_right());
        }
    };

    void print_preorder()
    {
        print_preorder(root);
        std::cout << std::endl;
    }

    // Aditional methods used to answer questions

    // Method that recursively return a pointer to the node that holds the maximum value in BST
    BTreeNode<T>* get_max(BTreeNode<T>* node) {
        if(node->get_right() != NULL)
            return get_max(node->get_right());
        else 
            return node;
    };

    // Mehtod that returns flag is BST is empty and a string witht the domain and number of connections 
    // if BST is not empty
    string get_max() {
        if(root == NULL)
            return "BST is empty!";
        else {
            BTreeNode<T>* node = get_max(root);
            return node->get_domain() + "-" + to_string(node->get_val());
        }
    }

};

#endif