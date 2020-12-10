// Developed by: Axel Mercado Gasque
// Start Date: October 14th 2020
// End date: 

/* ******************** 
    This file contains the answer to the following questions using the implementation of the methods defined in the class "ConexionesComputadora"
    What IP address is being used?
    What was the IP of the last connection this computer received? Is it internal or external?
    How many incoming connections does this computer have?
    How many outbound connections does this computer have?
    Extra: Does this computer have 3 consecutive connections to the same website?
   ******************** */


// Declaration of utilized libraries

#include <iostream>
#include "ConexionesComputadora.hpp"


// Code start

int main() {

    bool condicion = true;
    string opcion;
    while(condicion) {
        // Solution to above questions
        ConexionesComputadora computadora;
        vector<Conexion> conexiones;
      
        // IP address is asked and incoming and outgoing connections are stored accorddingly
        computadora.leerArchivo(conexiones);
        computadora.ingresaIP(conexiones);
        computadora.guardarConexiones(conexiones);
        //172.31.224.17

        // 1. What IP address is being used?
        cout << "La dirección IP usada es: " << computadora.getIP() << endl;

        // 2. What was th IP of the last connection this computer received? Is it internal or external?
        cout << computadora.ultimaConexionEntrante() << endl;

        // 3. How many incoming connections does this computer have?
        cout << "La computadora de IP: " << computadora.getIP() << " tiene " <<
        computadora.numConexionesEntrantes() << " conexiones entrantes" << endl;

        // 4. How many outgoing connections does this computer have?
        cout << "La computadora de IP: " << computadora.getIP() << " tiene " <<
        computadora.numConexionesSalientes() << " conexiones salientes" << endl;

        // 5. Extra: Does this computer have 3 consecutive connections to the same website?
        cout << computadora.tresConexionesSeguidas() << endl;
        cout << endl;
        cout << "¿Desea ingresar otra IP? (S para si, N para no)" << endl;
        cin >> opcion;
        while(opcion != "S" && opcion != "N") {
            cout << "Ingrese una opción válida" << endl;
            cin >> opcion;
        }
        if(opcion == "N")
          condicion = false;
    }
    cout << "El programa ha terminado, que tenga buen día." << endl;

   return 0;
}


