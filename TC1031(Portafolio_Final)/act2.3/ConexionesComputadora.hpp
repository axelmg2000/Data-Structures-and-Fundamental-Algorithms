// Developed by: Axel Mercado Gasque
// Start Date: October 10th 2020
// End date: October 14th 2020

/* ******************** 
    This file contains the definition of the class "ConexionesComputadora"
   ******************** */

#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp

#include <vector>
#include <string>
#include <stack> // Library for data structure stack is included (pila)
#include <queue> // Library for data structure queue is included (fila o cola)
#include "Conexion.hpp"
using namespace std;


class ConexionesComputadora {

    private:
        string IP;
        string nombre;
        stack<Conexion> conexionesEntrantes;
        queue<Conexion> conexionesSalientes;

    public:
        // Constructor and destructor
        ConexionesComputadora();
        ~ConexionesComputadora();

        // Get methods
        string getIP();
        string getNombre();
        stack<Conexion> getConexionesEntrantes();
        queue<Conexion> getConexionesSalientes();

        // Set Methods
        void setIP(string);
        void setNombre(string);
        void setConexionesEntrantes(stack<Conexion>);
        void setConexionesSalientes(queue<Conexion>);


        // Additional Methods

        // Method that asks the user to enter either known IP or last digits of IP
        void ingresaIP(vector<Conexion> &conexiones);

        // Method that reads file and stores IP addresses into vectors
        void leerArchivo(vector<Conexion> &conexiones);

        // Method that stores outgoing and incoming connections into object
        void guardarConexiones(vector<Conexion> &conexiones);

        // Method that returns last incoming connection
        string ultimaConexionEntrante();

        // Method that returns first outgoing connection
        string primeraConexionSaliente();

        // Method that returns the number of incoming connections
        int numConexionesEntrantes();

        // Method that returns the number of outgoing connections
        int numConexionesSalientes();

        // Method that returns if an IP has three consecutive connections to one web server
        string tresConexionesSeguidas();


};

#endif