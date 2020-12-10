#ifndef Transaccion_hpp
#define Transaccion_hpp

#include <string>
using namespace std;

class Transaccion {

  private:
    string fecha;
    string hora;
    string IpOrigen;
    string transaccion1;
    string nomOrigen;
    string IpDestino;
    string transaccion2;
    string nomDestino;


  public:
    // Constructor y Destructor
    Transaccion();
    Transaccion(string, string, string, string, string, string, string, string);
    ~Transaccion();

    // Métdos set
    void setFecha(string);
    void setHora(string);
    void setIpOrigen(string);
    void setTransaccion1(string);
    void setNomOrigen(string);
    void setIpDestino(string);
    void setTransaccion2(string);
    void setNomDestino(string);

    // Métodos get
    string getFecha();
    string getHora();
    string getIpOrigen();
    string getTransaccion1();
    string getNomOrigen();
    string getIpDestino();
    string getTransaccion2();
    string getNomDestino();
    
    // Método str
    string str();

};
#endif