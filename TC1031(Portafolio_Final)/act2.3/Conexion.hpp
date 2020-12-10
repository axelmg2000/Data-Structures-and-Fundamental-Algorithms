// Developed by: Axel Mercado Gasque
// Start Date: October 15th 2020
// End date: October 15th 2020

/* ******************** 
    This file contains the definition of the class "Conexion"
    This class defines the abstract data type "Conexion" which when instanced
    stores all atributes of each register
   ******************** */

#ifndef Conexion_hpp
#define Conexion_hpp

#include <string>
using namespace std;

class Conexion {

  private:
    string fecha;
    string hora;
    string IpOrigen;
    string conexion1;
    string nomOrigen;
    string IpDestino;
    string conexion2;
    string nomDestino;


  public:
    // Constructor y Destructor
    Conexion();
    Conexion(string, string, string, string, string, string, string, string);
    

    // Métdos set
    void setFecha(string);
    void setHora(string);
    void setIpOrigen(string);
    void setConexion1(string);
    void setNomOrigen(string);
    void setIpDestino(string);
    void setConexion2(string);
    void setNomDestino(string);

    // Métodos get
    string getFecha();
    string getHora();
    string getIpOrigen();
    string getConexion1();
    string getNomOrigen();
    string getIpDestino();
    string getConexion2();
    string getNomDestino();
    
    // Método str
    string str();

};
#endif