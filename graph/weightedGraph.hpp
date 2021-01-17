#ifndef weightedGraph_hpp
#define weightedGraph_hpp

#include <iostream> 
#include <utility> 
#include <limits.h>
#include <vector>
#include <list>
#include <queue>
#include <stack>
using namespace std;

template <class T>
class GraphVertexWeighted
{
private:
    T val;
    vector<pair<int, float> > adj;
public: 
    ~GraphVertexWeighted() {};
    GraphVertexWeighted() {};
    GraphVertexWeighted(T _val) {val = _val;};

    T get_val() {return val;};
    void set_val(T _val) {val = _val;};

    vector<pair<int, float> > get_adj() {return adj;};
    void add_to_adj(int idx, float weight) {adj.push_back(make_pair(idx, weight));};
};


template <class T>
class GraphWeighted
{
private:
    vector<GraphVertexWeighted<T>> nodes;
    bool is_directed;

public:
    ~GraphWeighted() {};
    GraphWeighted() {is_directed=false;};

    void add_node(T val)
    {
        GraphVertexWeighted<T> node(val);
        nodes.push_back(node);
    };

    void add_edge(int src, int dst, float weight)
    {
        nodes[src].add_to_adj(dst, weight);
        if (!is_directed)
            nodes[dst].add_to_adj(src, weight);
    };

    T get_node_val(int i)
    {
        return nodes[i].get_val();
    };


    
    vector<float> shortest_path(int s) {
        // Vector donde cada posición corresponde a los nodos del grafo
        // Se inicializa la distancia mínima como infinito (ya que no sabemos si podemos llegar)
        vector<float> shortestPathToVertex(nodes.size(), INT_MAX);
        // Vector de booleanos en donde cada posición corresponde a cada nodo del grafo y se inicializan a falso porque no estamos seguros del camino mas corto a ellos.
        vector<bool> sureNodes(nodes.size(), false);
      
        int vecinoMasCercano, distMasCorta; // Variable que almacenará el vecino más cercano de un nodo dado y distancia mas corta
        int flag = 0;
        int min;
        // Se inicializa una variable que indica que aún hay nodos de los cuales no se sabe
        // cual es la distancia mínima cuando esta es "true"
        bool notSureNodes = true;

        // La distancia mínima al nodo dado es 0, ya que para llegar a sí mismo tiene que hacer nada
        shortestPathToVertex.at(s) = 0; 
        int u = s; // u hace referencia al nodo del cual se está seguro la distancia mínimo
        int n = nodes.size() * nodes.size();
        // Se repite el proceso de abajo n^2 veces n representando el número de nodos del grafo
        for(int iter = 0; iter < n; iter++) {
            // Se recorre el vector con las distancias minimas registradas a todos los nodos, para seleccionar el nodo del cual no se está seguro con la menor distancia estimada
            min = INT_MAX;
            for(int i = 0; i < sureNodes.size(); i++) {
                if(sureNodes.at(i) == false && shortestPathToVertex.at(i) < min) {
                    u = i;
                    min = shortestPathToVertex.at(i);
                }
            }
            // Se obtiene el vector de los nodos vecinos al nodo u
            vector<pair<int, float>> nodosVecinos = nodes.at(u).get_adj();
            
            // Antes de visitar los vecinos de un nodo se declara que el más cercano es el primero
            distMasCorta = nodosVecinos.at(0).second; 
            vecinoMasCercano = nodosVecinos.at(0).first;

            // Se recorren los nodos vecinos
            for (int i = 0; i < nodosVecinos.size(); i++) {
                // Si se encuentra un nodo con menor distancia
                if(nodosVecinos.at(i).second < distMasCorta) {
                    distMasCorta = nodosVecinos.at(i).second; 
                    vecinoMasCercano = nodosVecinos.at(i).first;
                }
                // Se obtiene el número del nodo vecino y se checa en el vector en esa posición cual es la distancia mínima registrada. Si esta distancia es mayor que la suma de la distancia mínima registrada del nodo al cual se estan recorriendo sus vecinos MÁS la distancia de ese nodo al nodo vecino que se esta revisando, entonces se actualiza la distancia mínima del nodo vecino 
                if(shortestPathToVertex.at(nodosVecinos.at(i).first) >  shortestPathToVertex.at(u) + nodosVecinos.at(i).second)
                    shortestPathToVertex.at(nodosVecinos.at(i).first) = shortestPathToVertex.at(u) + nodosVecinos.at(i).second;
            }
            sureNodes.at(u) = true;
        }
        return shortestPathToVertex;
    };
};



#endif