// Developed by: Axel Mercado Gasque
// Start Date: 21 September 2020
// End Date: 


// Declaration of utilized libraries
#include <iostream>
#include <vector>
#include <string>
#include "Transaccion.hpp"
#include "Transacciones.hpp"
using namespace std;





int main() {

  Transacciones transactions;
  transactions.leerArchivo();

  
  
  // 1. ¿Cuantos registros tiene el archivo?
  cout << transactions.numeroTransacciones() << endl;
  cout << endl;

  // 2. ¿Cuántos récords hay del segundo día registrado? ¿Qué día es este?
  cout << transactions.transaccionesSegundoDia() << endl;
  cout << endl;

  // 3. ¿Alguna de las computadoras pertenece a Jeffrey, Betty, Katherine, Scott, Benjamin, Samuel o Raymond?
  // Ordenar de acuerdo a nombre y hacer una búsqueda binaria de cada nombre
  // ********************* //
  // NOTA: ESTE MÉTODO TARDA CASI 2 MINUTOS EN EJECUTAR
  // ********************* // 
  transactions.alphabeticalQuickSort();
  cout << transactions.findNames();
  cout << endl;
  

  // 4. ¿Cuál es la dirección de la red interna de la compañía?
  // 
 

  
  // 5. ¿Alguna computadora se llama server.reto.com?
  // Ordenar de acuerdo a hostname fuente, realizar busqueda binaria
   cout << transactions.nameServer() << endl;
   cout << endl;

  // 6. ¿Qué servicio de mail utilizan (algunas ideas: Gmail, Hotmail, Outlook, Protonmail)?
  // Ordenar de acuerdo al mail, y hacer una búsqueda binaria
   cout << transactions.findDomains() << endl;
   cout << endl;

  // 7. Considerando solamente los puertos destino ¿Qué puertos abajo del 1000 se están usando? Lista los puertos e investiga que aplicación/servicio lo utiliza generalmente.
  // Ordenar de acuerdo a puertos de destino. hacer búsqueda secuencial hasta llegar a 1000
   cout << transactions.ports() << endl;
   cout << endl;
  
}

