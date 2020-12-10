// Developed by: Axel Mercado Gasque
// Start Date: November 9th 2020
// End date: November 11th 2020

/* ********************
This file contains the implementation and answer to the following questions.

Contenga una función llamada conexionesPorDia, la cual reciba una fecha (puede ser string, int o un objeto que hayas definido tú en la primera etapa del reto). Dicha función debe regresar un map<string, int> conteniendo la cantidad de conexiones entrantes a cada sitio/página que no sea "-" y que no pertenezca al dominio "reto.com" del día especificado por la fecha de entrada. Por ejemplo:
outlook.com: 45
mail.google.com: 234
tacos-a-domicilio.mx: 1298

Contenga una función llamada top, la cual recibe un parámetro n de tipo int y una fecha. Esta función debe imprimir los n sitios con más accesos en esa fecha. Para ello, puedes usar la función conexionesPorDia y debes agregar los sitios a un BST utilizando como parámetro de ordenamiento la cantidad de conexiones entrantes.
Utiliza estas funciones para imprimir por cada día de las bitácoras el top 5.
Responde las siguientes preguntas:

¿Existe algún sitio que se mantenga en el top 5 en todos los días?
¿Existe algún sitio que entre al top 5 a partir de un día y de ahí aparezca en todos los días subsecuentes?
¿Existe algún sitio que aparezca en el top 5 con una cantidad más alta de tráfico que lo normal?

******************** */


///////////////////////
/*
NOTAS IMPORTANTES

----
¿Qué es?: Se le agrega un atributo de tipo string el cual almacena el dominio (el valor tipo T almacena entonces el número de conexiones entrantes en ese dominio en un día determinado), y se actualizan respectivamente los constructores y los métodos que utilicen al constructor del tipo "BTreeNode"

¿Por qué?: Este cambio se hace para que cuando se itere por los elementos del árbol, se pueda reconocer a que dominio pertenece un cierto valor numérico (ya que representa el numero de conexiones entrantes para un cierto dominio).
----

----
¿Qué es?: Se modifica el método "insert_node_recursive" para que no inserte valores repetidos al árbol

¿Por qué?: Este cambio se hace para que no se obtengan valores máximos repetidos al momento de buscar por el valor máximo del árbol.
----

*/
///////////////////////


// DECLARATION OF UTILIZED LIBRARIES

#include <iostream>
#include <vector>
#include <fstream> // File stream library
#include <sstream> // String stream library
#include <set> // library included for sets
#include <iterator> // Library to access elements in sets
#include <map> // Library included for dictionaries
#include "Conexion.hpp"
#include "BinarySearchTree.hpp"


// DECLARATION AND IMPLEMENTATION OF UTILIZED METHODS

// Method that reads file and stores "Conexion" objects in vector
// Parameters: vector of Conexion type in which read connections are stored
void readAndStore(vector<Conexion> &conexiones) {
    // File pointer
    fstream recordFile;
    // Open existing file
    recordFile.open("nuevo13.csv", ios::in);

    string line, word;
    string row[8];
    int iCant;
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
        
    }
    
    recordFile.close();
}

// Method that receives a date and returns a dictionary with the domains different to "reto.com" as keys and the number of incoming connections on that day as values. 
// Parameters: vector of type "Conexion" and a string which represents the date
map<string, int> conexionesPorDia(string fecha, vector<Conexion> &conexiones) {
    // Recorrer el vector y si la fecha de la conexion es igual a la recibida
    // Si es así, Se checa si el dominio destino es diferente a reto.com y la longitud mayor a 1
    // Si es así, se busca el dominio en el diccionario
    // Si esta, se le agrega 1 a las conexiones entrantes, si no, se agrega como llave y valor 0
    // Se regresa el diccionario 
    map<string, int> domNumConexionesEntrantes;
    map<string, int>::iterator mapItr;

    for(int i = 0; i < conexiones.size(); i++) {
        // Si la fecha es igual a la recibida y el nombre destino no contiene "reto.com" y el tamaño es mayor a 1 (para asegurar que no es un guión)
        if(conexiones.at(i).getFecha() == fecha && conexiones.at(i).getNomDestino().find("reto.com") == string::npos && conexiones.at(i).getNomDestino().size() > 1) {
            // Si el dominio existe en el diccionario
            if(domNumConexionesEntrantes.find(conexiones.at(i).getNomDestino()) != domNumConexionesEntrantes.end()) {
                mapItr = domNumConexionesEntrantes.find(conexiones.at(i).getNomDestino());
                mapItr->second++;
            }
            else 
                domNumConexionesEntrantes.insert(pair<string, int>(conexiones.at(i).getNomDestino(), 1));
        }
    }
    return domNumConexionesEntrantes;
}



// Method that receives a number "n" and a date; then the n sites with the most connections on that day are displayed. Also, this method returns a string with the domains and the number of incoming connections; different domaisn are seperated by commas. Example: "gmail.com-43,yahoo.es-24"
// Parameters: an integer that represents the number, and a string that represents date
void top(int numeroSitios, string fecha, vector<Conexion> conexiones) {
    // diccionario con los dominios como llaves y el número de conexiones entrantes como valores
    map<string, int> domNumConexionesEntrantes = conexionesPorDia(fecha, conexiones);
    map<string, int>::iterator mapItr; // iterador para recorrer diccionario
    BinarySearchTree<int> binaryTree;
 
    for(mapItr = domNumConexionesEntrantes.begin(); mapItr != domNumConexionesEntrantes.end(); mapItr++) 
        // Agregar cada dominio y numero de conexiones entrantes al árbol
        binaryTree.insert_node_recursive(mapItr->second, mapItr->first); 
    
    // Hacer un while para iterar "numeroSitios" veces
    // En cada iteración obtener el valor máximo del árbol, imprimirlo y eliminarlo
    int count = 0;
    string domNumConexiones;
    while(count < numeroSitios) {
        domNumConexiones = binaryTree.get_max();
        cout << domNumConexiones << endl;
        // Se manda a llamar al método delete_node con el valor máximo como parámetro
        binaryTree.delete_node(stoi(domNumConexiones.substr(domNumConexiones.find("-") + 1)));
        count++;
    }
}

// Method that finds all different days in which connections are made and indirectly prints top five domains in terms of which has more incoming connections. It also returns a vector that holds top 5 visted domains of every day. 
// Parameters: vector of Conexion type which holds all the connections
void topFiveEachDay(vector<Conexion> &conexiones) {
    vector<string> days; // Almacenará los distintos días de las conexiones
    string day = conexiones.at(0).getFecha();
    days.push_back(day);
    for(int i = 0; i < conexiones.size(); i++) {
        if(conexiones.at(i).getFecha() != day) {
            day = conexiones.at(i).getFecha();
            days.push_back(day);
        }
    }
    // Una vez se tiene un vector con los días, se recorre el vector
    // Y se llama al método top con 5, cada posición del vector (las fechas) y el vector con las conexiones
    for(int i = 0; i < days.size(); i++) {
        cout << "Day: " + days.at(i) << endl;
        top(5, days.at(i), conexiones); // ya se tiene un vector con  los 5 dominios con mas conexiones recibidas para cada día.

        cout << endl;
    }
}

  
// Code start

int main() {
    
    // DECLARATION ON NEEDED OBJECTS TO ANSWER THE PREVIOUS QUESTIONS //
    vector<Conexion> conexiones; // Vector that stores connections read from file
    map<string, int> domNumConexionesEntrantes; // dictionary with the domains different to "reto.com" as keys and the number of incoming connections on a certain day as values.  
    map<string, int>::iterator mapItr; // iterator of map type
    

    // CALLING NEEDED METHODS TO ANSWER QUESTIONS

    // Calling method to store connections
    readAndStore(conexiones); 
    cout << "File read and stored!" << endl;
    cout << endl;

    // Calling method to display top 5 domains in terms of which has more incoming connections each day
    topFiveEachDay(conexiones);
    
  
}