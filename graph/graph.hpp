#ifndef graph_hpp
#define graph_hpp

#include<iostream> 
#include <list>
#include <vector>
#include <queue>
#include <stack>

template <class T>
class GraphVertex
{
private:
    T val;
    std::vector<int> adj;
public: 
    ~GraphVertex() {};
    GraphVertex() {};
    GraphVertex(T _val) {val = _val;};

    T get_val() {return val;};
    void set_val(T _val) {val = _val;};

    std::vector<int> get_adj() {return adj;};
    void add_to_adj(int idx) {adj.push_back(idx);};
};

// A B C D E F G H
// 0 1 2 3 4 5 6 7
// A: 1, 2, 3
// B: 0
// C: 0, 3


template <class T>
class Graph
{
private:
    std::vector<GraphVertex<T> > nodes;
    bool is_directed;

public:
    ~Graph() {};
    Graph() {is_directed=false;};

    void add_node(T val)
    {
        GraphVertex<T> node(val);
        nodes.push_back(node);
    };

    void add_edge(int src, int dst)
    {
        nodes[src].add_to_adj(dst);
        if (!is_directed)
            nodes[dst].add_to_adj(src);
    };

   
    void BFS(int start_vertex)
    {
        // vector de booleanos se inicializa del tamaño del número de nodos que tiene el grafo
        // y con todos lso valores a falso
        std::vector<bool> visited(nodes.size(), false); 
        std::queue<int> queue;

        visited[start_vertex] = true; // El nodo/vértice correspondiente al número recibido ya esta visitado
        queue.push(start_vertex); // Se agrega el número al queue

        while (!queue.empty())
        {
            int s = queue.front();
            
            // Desplegar el valor del nodo/vértice que esta siendo visitado
            std::cout << nodes[s].get_val() << " "; 
            queue.pop(); // Como ya se visitó se eliminá del queue

            // Se hace un ciclo para obtener el apuntador a los vecinos del nodo/vértice 
            // que actualmente se está visitando
            for (std::vector<int>::iterator i = nodes[s].get_adj().begin();
                 i != nodes[s].get_adj().end(); i++)
            {
                if (!visited[*i]) // Si algún vecino no ha sido visitado
                {
                    queue.push(*i); // Se agrega el vecino al queue
                    visited[*i] = true; // Se actualiza en el vector de visitados como que yá fue visitado
                }
            }            
        }
        std::cout << std::endl;
    };

   
    void DFS(int start_vertex)
    {
        // vector de booleanos se inicializa del tamaño del número de nodos que tiene el grafo
        // y con todos lso valores a falso
        std::vector<bool> visited(nodes.size(), false);
        std::stack<int> stack;
        // Se agrega al stack el número recibido correspondiente al nodo/vértice por el cual se empieza
        stack.push(start_vertex); 

        while(!stack.empty())
        {
            int s = stack.top(); 
            stack.pop(); // Se elimina el valor del stack

            if (!visited[s]) // Si el nodo/vértice no ha sido visitado
            {
                // Se actualiza en el vector de visitados como que yá fue visitado
                visited[s] = true; 

                // Desplegar el valor del nodo/vértice que esta siendo visitado
                std::cout << nodes[s].get_val() << " ";
            }

            // Se hace un ciclo para obtener el apuntador a los vecinos del nodo/vértice 
            // que actualmente se está visitando
            for (std::vector<int>::iterator i = nodes[s].get_adj().begin();
                 i != nodes[s].get_adj().end(); i++)
            {
                if (!visited[*i]) // Si algún vecino no ha sido visitado
                {
                    stack.push(*i); // Se agrega el vecino al stack
                }
            }
        } 
        std::cout << std::endl;     
    };



    
};

#endif