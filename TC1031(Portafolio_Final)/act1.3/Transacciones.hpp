#ifndef Transacciones_hpp
#define Transacciones_hpp

#include <vector>
#include "Transaccion.hpp"
using namespace std;


class Transacciones {

  private:
    // Vector of pinters to "Transaccion" objects
    vector<Transaccion> transacciones;



  public:
    // Method to read transaction file and store the transactions in the vector of Transaction objects
    void leerArchivo();

    // Method that returns the number of trsansactions
    int numeroTransacciones();

    // Method that returns the number records in the second day and the day
    string transaccionesSegundoDia();

    // Find given names
    string findNames();

    // Sort according to source names
    void alphabeticalQuickSort();

    // Find if there is a computer named server
    string nameServer();

    // Find given email domains
    string findDomains();
    
    // Find ports less than 1000
    string ports();

    // Finf IP of company
    //string companyIP();

    Transaccion getTransaccion(int index);



};



#endif



