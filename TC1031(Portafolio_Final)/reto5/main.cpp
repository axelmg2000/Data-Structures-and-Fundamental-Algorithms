// Developed by: Axel Mercado Gasque
// Start Date: November 23th 2020
// End date: November 26th 2020

/* ********************
This file contains the implementation and answer to the following questions.

En los retos pasados encontraste la siguiente información:

Una ip interna, que llamaremos A, la cual se comunica con algunas otras computadoras internas.
Algún sitio con nombre raro, al cual denominaremos B.
Un sitio web normal que tiene un volumen de tráfico anómalo en un día, el cual denominaremos C.
En este reto vamos a trabajar en encontrar la cantidad de computadoras que se han conectado a estos sitios/ips. Para ello tienes que resolver las siguientes preguntas:

- Utilizando un grafo con las conexiones entre las ip de la red interna, determina la cantidad de computadoras con las que se ha conectado A por día. ¿Es A el vértice que más conexiones salientes hacia la red interna tiene?
- Utilizando el grafo del punto anterior, ubica la cantidad de computadoras que se han conectado hacia A por día. ¿Existen conexiones de las demás computadoras hacia A?
- Utilizando un grafo de conexiones a sitios web, determina cuántas computadoras se han conectado a B por día.
- Utilizando el mismo grafo del punto anterior, indica cuántas computadoras se han conectado a C por día.
- (Pregunta sin código): Investiga que es un ping sweep, un DDoS, un servidor de comando y control y un botmaster. ¿Ves estos elementos en tus datos?
******************** */


// IP interna - A: 172.31.224
// Sitios anómalos - B: "li44wsvsoyx7vukfvuu5.xxx", "lnrar56w11linjvv5bnj.net"
// Sitio web normal con un volumen de tráfico anómalo - C: "protonmail.com"


// DECLARATION OF UTILIZED LIBRARIES
#include <iostream>
#include <fstream> // File stream library
#include <sstream> // String stream library
#include <set> 
#include <iterator>
#include <vector>
#include <map>
#include "Conexion.hpp"
#include "graph.hpp"

// DECLARATION AND IMPLEMENTATION OF UTILIZED METHODS

// Method that reads file and stores "Conexion" objects in vector, stores all internal IP is set, and also stores all domains in set
// Parameters: vector of Conexion type in which read connections are stored, set of string in which IPs are stored
void readStore(vector<Conexion> &conexiones, set<string> &internalIps, set<string> &domains, set<string> &days) {
    // File pointer
    fstream recordFile;
    // Open existing file
    recordFile.open("nuevo13.csv", ios::in);
    string line, word;
    string row[8];
    int iCant;

    Graph<string> grafo;
    while(getline(recordFile, line)) {
        // read an entire row and store it in a string variable 'line'
        // used to break the line into words
        stringstream s(line);

        // read every column data of a row and store it in a string variable , 'word'
        iCant = 0;
        while(getline(s, word, ',')) {
            // add all the column data of a row to a vector
            row[iCant] = word;
            iCant++;
        }
        Conexion con(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
        conexiones.push_back(con);
        days.insert(row[0]);
        // Si el IP origen o destino de una conexion es un IP interno, se agrega al conjunto (set)
        if(row[2] != "-" && row[2].find("172.31.224") != string::npos)
            internalIps.insert(row[2]);
        if(row[5] != "-" && row[5].find("172.31.224") != string::npos)
            internalIps.insert(row[5]);
        if(row[4] != "-")
            domains.insert(row[4]);
        if(row[7] != "-")
            domains.insert(row[7]);     
    }
    
    recordFile.close();
}

// Method that adds all IPs in set as nodes to a graph, and the establishes connections iterating through vector of connections. The method return a dictionary with internal IPs as keys and the position they represent in the graph as values
// Parameters: set of string, Graph of string, and vector of Conexion
void createGraphVectors(vector<Conexion> &conexiones, set<string> &internalIps, set<string> &domains, set<string> &days, vector<Graph<string>> &internalConnections, vector<Graph<string>> &domainConnections, map<string, int> &ipIndex, map<string, int> &domIndex) {
    map<string, int>::iterator mapItr1, mapItr2;
    Graph<string> ips;
    int index = 0;
    // Recorro el set de IP internos para agregarlos como nodos al grafo
    for(set<string>::iterator itr = internalIps.begin(); itr != internalIps.end(); itr++) {
        ips.add_node(*itr);
        ipIndex.insert(pair<string, int>(*itr, index));
        index++;
    }
    Graph<string> doms;
    index = 0;
    // Recorro el set de dominios internos para agregarlos como nodos al grafo
    for(set<string>::iterator itr = domains.begin(); itr != domains.end(); itr++) {
        doms.add_node(*itr);
        domIndex.insert(pair<string, int>(*itr, index));
        index++;
    }
    // Se agregan tantos grafos a los vectores como hay fechas en las cuales ocurren las transacciones
    for(int i = 0; i < days.size(); i++) {
        internalConnections.push_back(ips);
        domainConnections.push_back(doms);
    }
    
    index = 0; // index indicará a que grafo del vector se le agregarán conexiones
    set<string> conexionesIp;
    set<string> conexionesDom;
    string fecha = conexiones.at(0).getFecha(); // la primer fecha es en la que ocurre la primera conexión en el registro
    
    // Se recorre el vector de conexiones para agregar las conexiones de cada día al grafo correspondiente
    for(int i = 0; i < conexiones.size(); i++) {
        // Si la fecha cambia
        if(conexiones.at(i).getFecha() != fecha) {
            fecha = conexiones.at(i).getFecha();
            index++; // Es un nuevo día y por lo tanto se agregan conexiones a otro grafo
            // Se borran las conexiones que hay entre ips y las conexiones que hay entre dominios 
            conexionesIp.clear();
            conexionesDom.clear();
        }
        // Si es una conexión entre ips internos
        if(conexiones.at(i).getIpOrigen().find("172.31.224") != string::npos && conexiones.at(i).getIpDestino().find("172.31.224") != string::npos) {
            // Si la conexión entre las dos IPs internas no existe, entonces se agrega la conexion al grafo
            if(conexionesIp.find(conexiones.at(i).getIpOrigen() + conexiones.at(i).getIpDestino()) == conexionesIp.end()) {
                // Apuntador a llave y valor del diccionario con los IPs y sus índices
                mapItr1 = ipIndex.find(conexiones.at(i).getIpOrigen()); 
                mapItr2 = ipIndex.find(conexiones.at(i).getIpDestino()); 
                internalConnections.at(index).add_edge(mapItr1->second, mapItr2->second);
            }
            conexionesIp.insert(conexiones.at(i).getIpOrigen() + conexiones.at(i).getIpDestino());
        }
        if(conexiones.at(i).getNomOrigen() != "-" && conexiones.at(i).getNomDestino() != "-") {
            // Si la conexión entre los dos dominios  no existe, entonces se agrega la conexion al grafo
            if(conexionesDom.find(conexiones.at(i).getNomOrigen() + conexiones.at(i).getNomDestino()) == conexionesDom.end()) {
                // Apuntador a llave y valor del diccionario con los IPs y sus índices
                mapItr1 = domIndex.find(conexiones.at(i).getNomOrigen()); 
                mapItr2 = domIndex.find(conexiones.at(i).getNomDestino()); 
                domainConnections.at(index).add_edge(mapItr1->second, mapItr2->second);
            }
            conexionesDom.insert(conexiones.at(i).getNomOrigen() + conexiones.at(i).getNomDestino());
        }
        
    }
}

// Mehtod that determines the number of computer with which IP "A" has connected each day, and whether it is a maximum
// Parameters: string A, vector of Graph of string, map<string, int>, set of string
map<string, int> connectionsAPerDay(string ipA, vector<Graph<string>> &internalConnections, map<string, int> &ipIndex, set<string> days) {
    int positionIpA = ipIndex.find(ipA)->second; // Posición que ocupa ipA en el grafo
    // Se recorre el vector de grafos
    map<string, int> neighborsEachDay;
    set<string>::iterator itr;
    int adjTotA = 0;
    int adjA = 0;
    vector<int> adjEachNode(internalConnections.at(0).get_nodes().size(), 0);
    
    for(int i = 0; i < internalConnections.size(); i++) {
        vector<GraphVertex<string>> graphNodes = internalConnections.at(i).get_nodes(); // vector de nodos del grafo de un día
        adjA = graphNodes.at(positionIpA).get_adj().size(); // Se accede al nodo que corresponde "A" y se guarda cuantos vecinos tiene
        itr = days.begin();
        neighborsEachDay.insert(pair<string, int>(*itr, adjA));
        days.erase(days.begin());
        adjTotA += adjA;
        for(int j = 0; j < graphNodes.size(); j++)
            adjEachNode.at(j) += graphNodes.at(j).get_adj().size();
    }
    int index = 0;
    bool condition = true;
    while(index < adjEachNode.size() && condition) {
        if(adjEachNode.at(index) > adjTotA)
            condition = false;
        index++;
    }
    if(condition) 
        cout << "A es el IP con más conexiones salientes a IP internos (en total)" << endl;
    else
        cout << "A no es el IP con más conexiones salientes a IP internos (en total)" << endl;
    return neighborsEachDay;
}

// Mehtod that determines the number of computer that connect to A each day
// Parameters: string A, vector of Graph of string, map<string, int>, set of string
map<string,int> connectionsToA(string ipA, vector<Graph<string>> &internalConnections, map<string, int> &ipIndex, set<string> days) {
     int positionIpA = ipIndex.find(ipA)->second; // Posición que ocupa ipA en el grafo
     set<string>::iterator itr;
     int connectionsWithA;
     map<string, int> connectionsAEachDay;
    // Se recorre el vector de grafos
    for(int i = 0; i < internalConnections.size(); i++) {
        // Se obtiene el vector con los nodos del grafo
        vector<GraphVertex<string>> graphNodes = internalConnections.at(i).get_nodes(); // vector de nodos del grafo de un día
        itr = days.begin();
        connectionsWithA = 0;
        // Se recorre el vector de de nodos del grafo
        for(int j = 0; j < graphNodes.size(); j++) {
            // Se obtiene el vector de vecinos del nodo
            vector<int> adj = graphNodes.at(j).get_adj();
            // Se recorren los vecinos de cada nodo para checar si está ipA
            int index = 0;
            bool foundA = false;
            while(index < adj.size() && !foundA) {
                if(adj.at(index) == positionIpA) {
                    connectionsWithA++;
                    foundA = true;
                }
                index++;
            }
        }
        connectionsAEachDay.insert(pair<string, int>(*itr, connectionsWithA));
        days.erase(days.begin());
    }
    return connectionsAEachDay;
}


// Code start

int main() {
    // DECLARATION ON NEEDED OBJECTS TO ANSWER THE PREVIOUS QUESTIONS //
    vector<Conexion> conexiones; // Vector that stores connections read from file
    vector<Graph<string>> internalConnections; // vector de grafos, en donde cada grafo tiene las conexiones de los IP en un día
    vector<Graph<string>> domainConnections; // vector de grafos, en donde cada grafo tiene las conexiones de los dominios en un día
    set<string> internalIps; // set to store unique internal IPs
    set<string> domains; // set to store unique internal IPs
    set<string> days; // set to store days in which connections occur
    string ipA; // string in which IP address asked to user will be stored
    map<string, int> ipIndex; // dictionary to store internal ip as keys and the position they occupy in graph as values
    map<string, int> domIndex; // dictionary to store domains as keys and the position they occupy in graph as values
    map<string, int> connectionsOfA; // dictionary that stores dates as keys and the number of IP "A" connected with as values
    map<string, int> connectionsToAEachDay; // dictionary that stores dates as keys and the number of IP that connect with "A" as values
    map<string, int> connectionsToB1EachDay; // dictionary that stores dates as keys and the number of IP that connect with "B" as values
    map<string, int> connectionsToB2EachDay; // dictionary that stores dates as keys and the number of IP that connect with "B" as values
    map<string, int> connectionsToCEachDay; // dictionary that stores dates as keys and the number of IP that connect with "C" as values
    


    // CALLING NEEDED METHODS TO ANSWER QUESTIONS
    cout << "Ingresa el dominio de la IP interna la cual denominaremos como A" << endl;
    cin >> ipA;
    // Calling method to store connections
    readStore(conexiones, internalIps, domains, days); 
    //for(set<string>::iterator itr = days.begin(); itr != days.end(); itr++)
        //cout << *itr << endl;
    
    // Calling method to create graph with all the connections within internal IPs
    cout << endl;
    createGraphVectors(conexiones, internalIps, domains, days, internalConnections, domainConnections, ipIndex, domIndex);
    
    // Calling method to determine the number of IPs with which A communicates, and if it has the maximum connections
    connectionsOfA = connectionsAPerDay(ipA, internalConnections, ipIndex, days);
    cout << "Número de direcciones IP internos con los que se conecta " <<ipA<< " cada día:" << endl;
    for(map<string, int>::iterator itr = connectionsOfA.begin(); itr != connectionsOfA.end(); itr++)
        cout << itr->first << "-" << itr->second << endl;
    cout << endl;
    
    // Calling method to determine the number of IPs that connecto to A (in case there are any) each day
    connectionsToAEachDay = connectionsToA(ipA, internalConnections, ipIndex, days);
    cout << "El número de direcciones IP que se conectan con " <<ipA<< " cada día son:" << endl;
    for(map<string, int>::iterator itr = connectionsToAEachDay.begin(); itr != connectionsToAEachDay.end(); itr++)
        cout << itr->first << "-" << itr->second << endl;
    cout << endl;

    // Calling method to determine the number of IPs that connecto to B1 (in case there are any) each day
    connectionsToB1EachDay = connectionsToA("li44wsvsoyx7vukfvuu5.xxx", domainConnections, domIndex, days);
    cout << "El número de dominios que se conectan con el dominio li44wsvsoyx7vukfvuu5.xxx cada día son:" << endl;
    for(map<string, int>::iterator itr = connectionsToB1EachDay.begin(); itr != connectionsToB1EachDay.end(); itr++)
        cout << itr->first << "-" << itr->second << endl;
    cout << endl;

    // Calling method to determine the number of IPs that connecto to B2 (in case there are any) each day
    connectionsToB2EachDay = connectionsToA("lnrar56w11linjvv5bnj.net", domainConnections, domIndex, days);
    cout << "El número de dominios que se conectan con el dominio lnrar56w11linjvv5bnj.net cada día son:" << endl;
    for(map<string, int>::iterator itr = connectionsToB2EachDay.begin(); itr != connectionsToB2EachDay.end(); itr++)
        cout << itr->first << "-" << itr->second << endl;
    cout << endl;

    // Calling method to determine the number of IPs that connecto to C (in case there are any) each day
    connectionsToCEachDay = connectionsToA("protonmail.com", domainConnections, domIndex, days);
    cout << "El número de dominios que se conectan con el dominio protonmail.com cada día son:" << endl;
    for(map<string, int>::iterator itr = connectionsToCEachDay.begin(); itr != connectionsToCEachDay.end(); itr++)
        cout << itr->first << "-" << itr->second << endl;
    cout << endl;






    
    

    







    return 0;
}