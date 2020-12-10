// Developed by: Axel Mercado Gasque
// Start Date: October 14th 2020
// End Date: October 14th 2020

/* ******************** 
    This file contains the implementation of the methods of the class "ConexionesComputadora"
   ******************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include "ConexionesComputadora.hpp"

// Implementation of Constructor Method
ConexionesComputadora::ConexionesComputadora() { 
    string IP;
    string nombre;
    stack<Conexion> conexionesEntrantes;
    queue<Conexion> conexionesSalientes;  
}

// Implementation of Destructor Method
ConexionesComputadora::~ConexionesComputadora() {
}

// Implementation of get methods
string ConexionesComputadora::getIP() {
  return IP;
}

string ConexionesComputadora::getNombre() {
  return nombre;
}

stack<Conexion> ConexionesComputadora::getConexionesEntrantes() {
  return conexionesEntrantes;
}

queue<Conexion> ConexionesComputadora::getConexionesSalientes() {
  return conexionesSalientes;
}
  

// Implementation of set methods
void ConexionesComputadora::setIP(string ip) {
  IP = ip;
}

void ConexionesComputadora::setNombre(string nom) {
  nombre = nom;
}


void ConexionesComputadora::setConexionesEntrantes(stack<Conexion> entrantes) {
  conexionesEntrantes = entrantes;
}

void ConexionesComputadora::setConexionesSalientes(queue<Conexion> salientes) {
  conexionesSalientes = salientes;
}




// Implementation of method "ingresaIP"
// This method asks to choose either a known IP or only last digits;
void ConexionesComputadora::ingresaIP(vector<Conexion> &conexiones) {
     // First the IP must be asked 
    string opcion;
    string ip;
    int index = 0;
    bool condition = true;
    cout << "¿Quiere ingresar un IP conocido o solo los dígitos depués del último punto? (Ingrese C para conocido y D para dígitos" << endl;
    cin >> opcion;
    while(opcion != "D" && opcion != "C") {
        cout << "Lo siento, no ingresaste ninguna de las opciones señaladas, ingrese D o C" << endl;
        cin >> opcion;
    }
    if(opcion == "D") {
        int digitos;
        cout << "Ingrese un número entre 1 y 150, y se generará el IP" << endl;
        cin >> digitos;
        // mientras no ingrese un número o que el numero sea < 1 o > 150
        while(cin.fail() || digitos < 1 || digitos > 150) {
            cout << "Incorrecto, por favor ingrese un número entre 1 y 150" << endl;
            cin >> digitos;
        }
        ip = "172.31.224." + to_string(digitos);
    }
    else {
        cout << "Ok ingrese la dirección IP conocida" << endl;
        cin >> ip;
        while(condition && index < conexiones.size()) {
            if((ip == conexiones.at(index).getIpOrigen() || ip == conexiones.at(index).getIpDestino()) && ip != "-")
                condition = false;
            index++;

        }
    }
    if(!condition) {
        IP = ip;
        index--;
        nombre = conexiones.at(index).getNomOrigen();
    }

}


// Implementation of method "leerArchivo"
// This method reads record file and stores records into "Conexion" type vector 
void ConexionesComputadora::leerArchivo(vector<Conexion> &conexiones) {
    // File pointer
    fstream recordFile;
    // Open existing file
    recordFile.open("nuevo13.csv", ios::in);

    string line, word;
    string row[8];
  
    while(getline(recordFile, line)) {
        // read an entire row and store it in a string variable 'line'
        // used to break the line into words
        stringstream s(line);

        // read every column data of a row and store it in a string variable , 'word'
        int iCant = 0;
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

// Implementation of method "guardarConexiones"
// Method that stores outgoing and incoming connections into object
void ConexionesComputadora::guardarConexiones(vector<Conexion> &conexiones) {
    for(int i = 0; i < conexiones.size(); i++) {
      if(nombre == conexiones.at(i).getNomOrigen())
          conexionesSalientes.push(conexiones.at(i));
      if(nombre == conexiones.at(i).getNomDestino())
          conexionesEntrantes.push(conexiones.at(i));
    }
}

// Implementation of method "ultimaConexionEntrante"
// Method that returns last incoming connection
string ConexionesComputadora::ultimaConexionEntrante() {
    if(conexionesEntrantes.empty())
        return "La computadora de IP: " + IP + " no tiene conexiones entrantes";
    else {
        string internaOExterna;
        Conexion ultimaConexion = conexionesEntrantes.top();
        string nomUltimaConexion = ultimaConexion.getNomOrigen();
        if(nomUltimaConexion.substr(nomUltimaConexion.length() - 8, nomUltimaConexion.length() - 1) == "reto.com")
            internaOExterna = "interna";
        else
            internaOExterna = "externa";
        return "Últiuma conexión entrante a " + IP + " vino de la IP: " + conexionesEntrantes.top().getIpOrigen() + " y es una conexión " + internaOExterna;
    }
}

// Implementation of method "ultimaConexionEntrante"
// Method that returns first outgoing connection
string ConexionesComputadora::primeraConexionSaliente() {
    return "Primera conexión saliente de la " + IP + " fue a la IP: " + conexionesEntrantes.top().getIpDestino();
}

// Implementation of method "numConexionesEntrantes"
// Method that returns the number of incoming connections
int ConexionesComputadora::numConexionesEntrantes() {
    return conexionesEntrantes.size();
}

// Implementation of method "numConexionesSalientes"
// Method that returns the number of outgoing connections
int ConexionesComputadora::numConexionesSalientes() {
    return conexionesSalientes.size();
}

// Implementation of method "tresConexionesSeguidas"
// Method that returns if an IP has three consecutive connections to one web server
string ConexionesComputadora::tresConexionesSeguidas() {
  queue<Conexion> aux;
  string conexionesSeguidas = "";
  if(conexionesSalientes.empty())
      return "La computadora de IP: " + IP + " no tiene conexiones salientes";
  else {
      bool condicion = true;
      int numConexionesSeguidas = 0;
      string webActual = conexionesSalientes.front().getNomDestino();
      while(condicion && !conexionesSalientes.empty()) {
          aux.push(conexionesSalientes.front());
          if(conexionesSalientes.front().getNomDestino() == webActual)
              numConexionesSeguidas++;
          if(numConexionesSeguidas == 3)
              condicion = false;
          conexionesSalientes.pop();
          if(webActual != conexionesSalientes.front().getNomDestino()) {
              numConexionesSeguidas = 0;
              webActual = conexionesSalientes.front().getNomDestino();
          }
      }
      if(!condicion) {
          while(!conexionesSalientes.empty()) {
              aux.push(conexionesSalientes.front());
              conexionesSalientes.pop();
          }
          conexionesSeguidas = "Sí";
      }
      else 
          conexionesSeguidas = "No";
      ConexionesComputadora::setConexionesSalientes(aux);
      return "La computadora de IP: " + IP + " " + conexionesSeguidas + " tiene 3 conexiones seguidas a un mismo sitio web";
  }
}