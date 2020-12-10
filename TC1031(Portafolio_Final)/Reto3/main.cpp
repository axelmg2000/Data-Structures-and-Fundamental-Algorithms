// Developed by: Axel Mercado Gasque
// Start Date: October 26th 2020
// End date: 

/* ******************** 
    This file contains the answer to the following questions using the implementation of the methods defined in the class "ConexionesComputadora" and some other methods defined next

    1. Is there a domain name that is abnormal (This can be by visual inspection)?
    2. From the domain names found in the previous step, what is the ip? How would you determine this information in the most efficient way in terms of time complexity?
    3. From the computers belonging to the reto.com domain, determine the number of ips that have at least one incoming connection. 
    (Remember that you already have the network address and the last octet can have computers from .1 to .254). Print the number of computers.
    4. Take some computers other than server.reto.com or dhcp server. They can be between 5 and 150. Get the unique IPs of the incoming connections.
    5. Considering the result of questions 3 and 4, what do you think is happening in this network? (Question without code)
    6. For the ips found in the previous step, determine if they have communicated with the data found in question 1.
    7. (Extra): In case you have found that the computers from step 1 and 4 communicate, determine on what date the first communication occurs between these 2 and what protocol was used.

    Cree un conjunto de strings. En este debes agregar los nombres de los dominios/computadoras que no pertenezcan al dominio reto.com.
    Crea una diccionario de pares <string,ConexionesComputadora> usando la clase creada en el reto pasado. Este diccionario debe ser llenado con todas las ips en los datos. Por cada una, es necesario registrar todas las conexiones que hayan salido desde esta ip o hayan sido recibidas por la misma.
   ******************** */


// DECLARATION OF UTILIZED LIBRARIES

#include <iostream>
#include <vector>
#include <fstream> // File stream library
#include <sstream> // String stream library
#include <set> // library included for sets
#include <iterator> // Library to access elements in sets
#include <map> // Library included for dictionaries
#include "ConexionesComputadora.hpp"


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

// Method that stores domains names different to "reto.com" and unique IPs in sets received as parameters
// Parameters: set of string to store domains, set of string to store IP addresses, vector of Conexion type form which connections are read, set pf string in which all domains will be stored
void storeDomainsAndIps(set<string> &domains, set<string> &ips, vector<Conexion> &conexiones, set<string> &allDomains) {
    string nomDestino;
    // Loop through vector of connections
    for(int i = 0; i < conexiones.size(); i++) {
        nomDestino = conexiones.at(i).getNomDestino();
        // If the IP address is longer than 1 and it is different to "reto.com" it is added to set
        if(nomDestino.find("reto.com") == string::npos && nomDestino != "-") 
            // nomDestino does not contain the substring "reto.com"
            domains.insert(nomDestino);  // It is added to the set
        if(conexiones.at(i).getNomOrigen() != "-") 
            allDomains.insert(conexiones.at(i).getNomOrigen()); // insert origin domain to set
        if(conexiones.at(i).getNomDestino() != "-") 
            allDomains.insert(conexiones.at(i).getNomDestino()); // insert destiny domain to set
        if(conexiones.at(i).getIpOrigen() != "-")
            ips.insert(conexiones.at(i).getIpOrigen());
        if(conexiones.at(i).getIpDestino() != "-")
            ips.insert(conexiones.at(i).getIpDestino());
    }
}

// Method that creates a dictionary with all the IP addresses as keys and their connections as values.
// Parameters: vector of Conecion type from which connections are read, map of string as keys and ConexionesComputadora as values, set of string that contins all the IP addresses
void createDictionary(vector<Conexion> &conexiones, map<string, ConexionesComputadora> &IpsConConexiones, set<string> &allDomains) {
    set<string>::iterator itr; // Way to initialize an iterator
    for(itr = allDomains.begin(); itr != allDomains.end(); itr++) {
        ConexionesComputadora conexionesComputadora;
        conexionesComputadora.setNombre(*itr);
        conexionesComputadora.guardarConexiones(conexiones);
        IpsConConexiones.insert(pair<string, ConexionesComputadora>(*itr, conexionesComputadora));
    }
}

// Method that returns the IP addresses of the anomalous domains found in the previous step
// Parameters: two strings which represent the domains, and a vector of Conexion type with all the connections
string Ips(string domain1, string domain2, vector<Conexion> &conexiones) {
        bool condition, firstFound, secondFound = false;
        string ips;
        int index = 0;
        while(!condition) {
            if(!firstFound) {
                if(conexiones.at(index).getNomDestino() == "li44wsvsoyx7vukfvuu5.xxx") {
                    ips += " // Domain: li44wsvsoyx7vukfvuu5.xxx, IP address: " + conexiones.at(index).getIpDestino();
                    firstFound = true;
                    if(secondFound)
                        condition = true;
                }
            }
            if(!secondFound) {
                if(conexiones.at(index).getNomDestino() == "lnrar56w11linjvv5bnj.net") {
                    ips += " // Domain: lnrar56w11linjvv5bnj.net, IP address: " + conexiones.at(index).getIpDestino();
                    secondFound = true;
                    if(firstFound)
                        condition = true;
                }
            }
            index++; 
        }
      return ips;
    }

// Method that returns the number IPs that belong to reto.com domain and that have at least 1 incoming connection
// Parameters: vector of Conexion type from which connections are read, map or dictionary with all the IP addresses and their connections
int numIpsMoreThanOneIncoming(vector<Conexion> &conexiones, map<string, ConexionesComputadora> IpsConConexiones) {
    int numOfIps = 0;
    map<string, ConexionesComputadora>::iterator itr;
    set<string> ips;
    // Loop through vector of connections
    for(int i = 0; i < conexiones.size(); i++) {
        itr = IpsConConexiones.find(conexiones.at(i).getNomOrigen()); // iterator to every IP address in dictionary
        if(itr->second.numConexionesEntrantes() > 0) { // If incoming connections of a certain IP > 0
            numOfIps++;
        }
        if(conexiones.at(i).getNomDestino().find("reto.com") != string::npos) {
          // Destiny domain contains the substring "reto.com"
            itr = IpsConConexiones.find(conexiones.at(i).getNomDestino());
            if(itr->second.numConexionesEntrantes() > 0) { // If incoming connections of a certain IP > 0
                numOfIps++;
            }
            IpsConConexiones.erase(conexiones.at(i).getNomDestino());
        } 
        IpsConConexiones.erase(conexiones.at(i).getNomOrigen());

    }
    return numOfIps;
}


// Method that returns the unique IP addresses of the computers different to the "server.reto.com" domain and dhcp server
// Parameters: vector of Conexion type from which connections are read, map or dictionary with all the IP addresses and their connections
set<string> IpsOtherThanServer(vector<Conexion> &conexiones, map<string, ConexionesComputadora> &IpsConConexiones) {
    string ipOrigen;
    int lastDigits;
    set<string> domains;
    set<string> incoming;
    set<string>::iterator setItr;
    stack<Conexion> pilaEntrantes;
    map<string, ConexionesComputadora>::iterator mapItr;
    for(int i = 0; i < conexiones.size(); i++) {
        if(conexiones.at(i).getConexion1() != "68" && conexiones.at(i).getConexion2() != "67" && domains.size() <= 150)
            domains.insert(conexiones.at(i).getNomOrigen());
    }
    
    for(setItr = domains.begin(); setItr != domains.end(); setItr++) {
        mapItr = IpsConConexiones.find(*setItr); // find domain in the dictionary
        pilaEntrantes = mapItr->second.getConexionesEntrantes();
        while(!pilaEntrantes.empty())  { // while stack of incoming connections not empty
            incoming.insert(pilaEntrantes.top().getIpOrigen());
            pilaEntrantes.pop();   
        }
        
    }
    return incoming;
          
}

// Method that returns true or false depending on whether the unique IP addresses of the computers different to the "server.reto.com" domain and dhcp server have communicated with two given domains
// Parameters: two strings which represent the domain names, dictionary of domains as keys and their connections as values, a set with the unique IP addresses. 
bool anomalousCommunication(string domain1, string domain2, map<string, ConexionesComputadora> IpsConConexiones, set<string> &incomingIps) {
    map<string, ConexionesComputadora>::iterator mapItr;
    set<string>::iterator setItr;
    mapItr = IpsConConexiones.find(domain1);
    stack<Conexion> incoming = mapItr->second.getConexionesEntrantes();
    queue<Conexion> outgoing = mapItr->second.getConexionesSalientes();

    for(setItr = incomingIps.begin(); setItr != incomingIps.end(); setItr++) {
        while(!incoming.empty()) {
            if(*setItr == incoming.top().getIpOrigen())
                return true;
            incoming.pop();
        }
        while(!outgoing.empty()) {
            if(*setItr == outgoing.front().getIpDestino())
                return true;
            outgoing.pop();
        }
    }

    mapItr = IpsConConexiones.find(domain2);
    stack<Conexion> incoming1 = mapItr->second.getConexionesEntrantes();
    queue<Conexion> outgoing1 = mapItr->second.getConexionesSalientes();
    
    for(setItr = incomingIps.begin(); setItr != incomingIps.end(); setItr++) {
        while(!incoming1.empty()) {
            if(*setItr == incoming1.top().getIpOrigen())
                return true;
            incoming1.pop();
        }
        while(!outgoing1.empty()) {
            if(*setItr == outgoing1.front().getIpDestino())
                return true;
            outgoing1.pop();
        }
    }
    return false;
}

// Method that returns the date of the ifrst connection betweem anomalous domains and certain IP addresses
// Parameters: two strings which represent the domain names, dictionary of domains as keys and their connections as values, a set with the unique IP addresses. 
string dateOfFirstCommunication(string domain1, string domain2, map<string, ConexionesComputadora> IpsConConexiones, set<string> &incomingIps) {
        int date = 0;
        map<string, ConexionesComputadora>::iterator mapItr;
        mapItr = IpsConConexiones.find(domain1);
        string protocolOrigin, protocolDestiny;
        date = stoi(mapItr->second.getConexionesEntrantes().top().getFecha().substr(0, 2));
        protocolOrigin = mapItr->second.getConexionesEntrantes().top().getConexion1();
        protocolDestiny = mapItr->second.getConexionesEntrantes().top().getConexion2();
        mapItr = IpsConConexiones.find(domain2);
        stack<Conexion> incoming = mapItr->second.getConexionesEntrantes();
        while(!incoming.empty()) {
            if(incomingIps.count(incoming.top().getIpOrigen()) > 0 && stoi(mapItr->second.getConexionesEntrantes().top().getFecha().substr(0, 2)) < date) {
                date = stoi(mapItr->second.getConexionesEntrantes().top().getFecha().substr(0, 2));
                protocolOrigin = mapItr->second.getConexionesEntrantes().top().getConexion1();
                protocolDestiny = mapItr->second.getConexionesEntrantes().top().getConexion2();
            }
            incoming.pop();
        }
        return "Date: " + to_string(date) + "-8-2020" + ", Puerto Origen: " + protocolOrigin + ", Puerto Destino: " + protocolDestiny;
    }

// Code start

int main() {
  
    
    // DECLARATION ON NEEDED OBJECTS ANSWER THE PREVIOUS QUESTIONS //
    
    vector<Conexion> conexiones; // Vector that stores connections read from file
    set<string> domains; // Set data structure that stores domains names different to "reto.com"
    set<string> allDomains; // Set data structure that stores domains names different to "reto.com"
    set<string> ips; // Set data structure tp store every IP address in a set
    map<string, ConexionesComputadora> IpsConConexiones; // Dictionary that stores IP addresses as keys and the connections each key has as value
    set<string>::iterator itr;

    


    // CALLING NEEDED METHODS TO ANSWER QUESTIONS


    // Calling method to store connections
    readAndStore(conexiones); 
    cout << "Done!" << endl;

    // Calls method to store domains different to "reto.com" and unique Ips
    storeDomainsAndIps(domains, ips, conexiones, allDomains);
    cout << "Done!" << endl;

    // Creates a dictionary with all the IP addresses as keys and their connections as values.
    createDictionary(conexiones, IpsConConexiones, allDomains);
    cout << "Done!" << endl;
    
    
    // 1. Is there a domain name that is abnormal (This can be by visual inspection)?
    // As seen when displaying the domains, there are two domains which can be considered abnormal
    // "li44wsvsoyx7vukfvuu5.xxx" and "lnrar56w11linjvv5bnj.net"
    for(itr = domains.begin(); itr != domains.end(); itr++)
        cout << *itr << endl;
    cout << "Done!" << endl;

    // 2. From the domain names found in the previous step, what is the ip? How would you determine this information in the most efficient way in terms of time complexity?
    // The most efficient way in terms of time complexity is simply to loop thorugh the vector of connections to search for the IP addresses (O(n))
    // Domain: li44wsvsoyx7vukfvuu5.xxx, IP address: 174.212.39.249
    // Domain: lnrar56w11linjvv5bnj.net, IP address: 96.149.110.226
    //cout << Ips("li44wsvsoyx7vukfvuu5.xxx", "lnrar56w11linjvv5bnj.net", conexiones) << endl;
    cout << "Done!" << endl;
    
    // 3. From the computers belonging to the reto.com domain, determine the number of ips that have at least one incoming connection. 
    cout << numIpsMoreThanOneIncoming(conexiones, IpsConConexiones) << endl; 
    cout << "Done!" << endl;

    // 4. Take some computers other than server.reto.com or dhcp server. They can be between 5 and 150. Get the unique IPs of the incoming connections.
    
    set<string> incomingIps = IpsOtherThanServer(conexiones, IpsConConexiones);
    for(itr = incomingIps.begin(); itr != incomingIps.end(); itr++)
        cout << *itr << endl;
    cout << "Done!" << endl;
    
   
    // 5. Considering the result of questions 3 and 4, what do you think is happening in this network? (Question without code)
    // Primero que nada, es importante notar que únicamente 34 computadoras pertenecientes al dominio "reto.com" tienen conexiones entrantes. Puede ser que estos IPs reciban muchas conexiones. O bien, hayan conexiones muchos diferentes dominios. O bien, alguna combinación entre ambos. De igual manera, de las cien computadoras elegidos en el paso anterior, en encontró que están recibiendo conexiones de 34 direcciones IP distintas. 

    // 6. For the ips found in the previous step, determine if they have communicated with the data found in question 1a
    if(anomalousCommunication("li44wsvsoyx7vukfvuu5.xxx", "lnrar56w11linjvv5bnj.net", IpsConConexiones, incomingIps)) {
        cout << "IP addresses found have communicated with domains found in question 1" << endl;
    }
    else {
        cout << "IP addresses found have not communicated with domains found in question 1" << endl;
    }
    cout << "Done!" << endl;
    

    //  7. (Extra): In case you have found that the computers from step 1 and 4 communicate, determine on what date the first communication occurs between these 2 and what protocol was used.
    cout << dateOfFirstCommunication("li44wsvsoyx7vukfvuu5.xxx", "lnrar56w11linjvv5bnj.net", IpsConConexiones, incomingIps) << endl;
    cout << "Done!" << endl;


    return 0;
}