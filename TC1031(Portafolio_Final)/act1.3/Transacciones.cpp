#include "Transacciones.hpp"
#include "Transaccion.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ********** //
// Method that reaads file and stores all the records in the vector
// ********** //
void Transacciones::leerArchivo() {
  // File pointer
  fstream transactionFile;
  // Open existing file
  transactionFile.open("equipo13.csv", ios::in);

  string line, word;
  string row[8];
  
  while(getline(transactionFile, line)) {
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
    // Create Transaction type object and add it to the vector
    Transaccion transaccion(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
    transacciones.push_back(transaccion);
  }
  transactionFile.close();
}

int Transacciones::numeroTransacciones() {
  return transacciones.size();
}

// ********** //
// Method that returns the number records in the second day and the day
// Time complexity O(log(n)^2)
// ********** //
string Transacciones::transaccionesSegundoDia() {
  int firstDay = stoi(transacciones.at(0).getFecha().substr(0, 2));
  int greaterIndex = transacciones.size() - 1;
  int smallerIndex = 0;
  bool lastTransactionFirstDay = false;
  int aux, secondDay;
  int numOfTransactions = 0;

  
  if(stoi(transacciones.at(greaterIndex).getFecha().substr(0, 2)) == firstDay)
      return "No hay segundo día";
  else {
    greaterIndex /= 2;
    // Binary search for the last transaction of the first day
    while(lastTransactionFirstDay == false) {
      if(stoi(transacciones.at(greaterIndex).getFecha().substr(0, 2)) == firstDay) {
        if(stoi(transacciones.at(greaterIndex + 1).getFecha().substr(0, 2)) == firstDay) {
          aux = greaterIndex;
          greaterIndex += (greaterIndex + smallerIndex) / 2;
          smallerIndex = aux;
        }
        else {
          lastTransactionFirstDay = true;
          greaterIndex++;
        }
      }
      else 
        greaterIndex = (greaterIndex + smallerIndex) / 2;
    }
    // Now greaterIndex has the index of the fitst transaction of the second day
    secondDay = stoi(transacciones.at(greaterIndex).getFecha().substr(0,4));
    // Now we have to count the number of transactions on this day
    smallerIndex = greaterIndex;
    greaterIndex = transacciones.size() - 1;
    bool lastTransactionSecondDay = false;
    
    if(stoi(transacciones.at(greaterIndex).getFecha().substr(0, 2)) == secondDay)
      numOfTransactions = greaterIndex - smallerIndex + 1;
    else {
      greaterIndex /= 2;
      // Binary search for the last transaction of the first day
      while(lastTransactionSecondDay == false) {
        if(stoi(transacciones.at(greaterIndex).getFecha().substr(0, 2)) == secondDay) {
          numOfTransactions += (greaterIndex - smallerIndex);
          if(stoi(transacciones.at(greaterIndex + 1).getFecha().substr(0, 2)) == secondDay) {
            aux = greaterIndex;
            greaterIndex += (greaterIndex + smallerIndex) / 2;
            smallerIndex = aux;
          }
          else {
            lastTransactionSecondDay = true;
            greaterIndex++;
          }
        }
        else 
          greaterIndex = (greaterIndex + smallerIndex) / 2;
      }
    }
  }
  return "DAY: " + to_string(secondDay) + ", number of transactions: " + to_string(numOfTransactions);
  
}

// ********** //
// Auxiliar methods
// ********** //
void swapElements(vector<Transaccion> &vector, int iPosX, int iPosY) { 
  Transaccion iAuxiliar = vector.at(iPosX);
  vector.at(iPosX) = vector.at(iPosY);
  vector.at(iPosY) = iAuxiliar;
}

bool compareNameSource(Transaccion &a, Transaccion &b) {
  string first = "";
  string second = "";
  for(char c: a.getNomOrigen()) {
    if(c == '.')
      break;
    else
      first += c;
  }
  for(char c: b.getNomOrigen()) {
    if(c == '.')
      break;
    else
      second += c;
  }
  return first < second;
}

bool compareNameDestiny(Transaccion &a, Transaccion &b) {
  string first = "";
  string second = "";
  for(char c: a.getNomDestino()) {
    if(c == '.')
      break;
    else
      first += c;
  }
  for(char c: b.getNomDestino()) {
    if(c == '.')
      break;
    else
      second += c;
  }
  return first < second;
}

bool comparePort(Transaccion &a, Transaccion &b) {
  return a.getTransaccion2() < b.getTransaccion2();
}

int partition(vector<Transaccion> &vector, int low, int high, bool(*compare)(Transaccion &a, Transaccion &b)) { 
  Transaccion pivot = vector.at(high);
  int i = low - 1; // Since we haven't found an element smaller than pivot we use -1
  for(int j = low; j < high; j++) {
    if((*compare)(vector.at(j),pivot)) {
      i++;
      swapElements(vector, i, j);
    }
  }
  swapElements(vector, i + 1, high);
  return (i + 1);
}

void quickSort(vector<Transaccion> &vector, int low, int high, string sd) {
  if(low < high) {
    int piv;
    if(sd == "s") 
      piv = partition(vector, low, high, &compareNameSource);
    else if(sd == "d")
      piv = partition(vector, low, high, &compareNameDestiny);
    else
      piv = partition(vector, low, high, &comparePort);
    quickSort(vector, low, piv - 1, sd);
    quickSort(vector, piv + 1, high, sd);
    
  }
}


int findNameBinary(vector<Transaccion> vector, string name, int first, int last, string sd) {
  if(last < first)
    return -1;
  int half = (first + last) / 2;
  string word = "";
  if(sd == "s") {
    for(char c: vector.at(half).getNomOrigen()) {
      if(c == '.')
        break;
      else
        word += c;
    }
  }
  else {
    for(char c: vector.at(half).getNomDestino()) {
      if(c == '.')
        break;
      else
        word += c;
    }
  }
  if(name == word)
    return half;
  else if(name < word)
    return findNameBinary(vector, name, first, half - 1, sd);
  else
    return findNameBinary(vector, name, half + 1, last, sd);
}
// ********** //
// End of auxiliar methods
// ********** //

// ********** //
// Method that sorts transactions according to source host name
// ********** //
void Transacciones::alphabeticalQuickSort() {
  quickSort(transacciones, 0, transacciones.size() - 1, "s");
  int nameFoundInt;
   nameFoundInt = findNameBinary(transacciones, "server", 0, transacciones.size() - 1, "s");
}

string Transacciones::findNames() {
    string names[7] = {"jeffrey", "betty", "katherine", "scott", "benjamin", "samuel", "raymond"};
    int numOfLoops = 0;
    int nameFoundInt = 0;
    while(numOfLoops < 7) {
      nameFoundInt = findNameBinary(transacciones, names[numOfLoops], 0, transacciones.size() - 1, "s");
      if(nameFoundInt != -1) 
        return "The name " + names[numOfLoops] + " was found!";
      else 
        numOfLoops++;
    }
    return "Sorry none of the names was found!";
  
}

string Transacciones::nameServer() {
  /*
  quickSort(transacciones, 0, transacciones.size() - 1, "s");
  int nameFoundInt;
  nameFoundInt = findNameBinary(transacciones, "server", 0, transacciones.size() - 1, "s");
  cout << "yessss" << endl;
  if(nameFoundInt != -1)
    return true;
  else {
    quickSort(transacciones, 0, transacciones.size() - 1, "d");
    cout << "yes" << endl;
    nameFoundInt = findNameBinary(transacciones, "server", 0, transacciones.size() - 1, "d"); 
    cout << "yes" << endl;
    if(nameFoundInt != -1)
      return true;
  }
  return false;
  */
  
  for(int i = 0; i < transacciones.size(); i++) {
    if(transacciones.at(i).getNomDestino() == "server.reto.com")
      return "server.reto.com was found!";
  }
  for(int i = 0; i < transacciones.size(); i++) {
    if(transacciones.at(i).getNomOrigen() == "server.reto.com")
      return "server.reto.com was found!";
  }

  return "server.reto.com was NOT found!";
  
}

string Transacciones::findDomains() {
  string names[4] = {"gmail.com", "hotmail.com", "outlook.com", "protonmail.com"};
    string domains = "";
    int numOfLoops = 0;
    int gmail = 0;
    int hotmail = 0;
    int outlook = 0;
    int protonmail = 0;
    while(numOfLoops < 4) {
      for(int i = 0; i < transacciones.size(); i++) {
        if(transacciones.at(i).getNomDestino() == names[numOfLoops])
          if(numOfLoops == 0)
            gmail++;
          else if(numOfLoops == 1)
            hotmail++;
          else if(numOfLoops == 2)
            outlook++;
          else
            protonmail++;
      }
      numOfLoops++;
    }
    domains += "Gmail: " + to_string(gmail) + ", Hotmail: " + to_string(hotmail) + ", Outlook: " + to_string(outlook) + ", Protonmail: " + to_string(protonmail);

    return "The found domains are as follows: " + domains;
}


string Transacciones::ports() {
  bool lessThan1000 = true;
  vector<string> ports;
  string portsRet = "";
  for(int i = 0; i < transacciones.size(); i++){
    if(transacciones.at(i).getTransaccion2() != "-") {
      if(stoi(transacciones.at(i).getTransaccion2()) <= 1000)
        if(find(ports.begin(), ports.end(), transacciones.at(i).getTransaccion2()) == ports.end())
          ports.push_back(transacciones.at(i).getTransaccion2());
    }
  }
  for(auto port: ports)
    portsRet += port + ", ";
  return portsRet;
  
}

/*
string Transacciones::companyIP() {
  string ip = "Company IP is: ";
  for(int i = 0; i < transacciones.size(); i++) {
    ip = transacciones.at(i).getIpOrigen().back();
    if(ip == "0") {
      ip.erase(ip.size() - 1);
      string ipB = ip.back();
      if(ipB == ".")
      return transacciones.at(i).getIpOrigen();
    }
      
      
  }
}
*/


Transaccion Transacciones::getTransaccion(int index) {
  return transacciones.at(index);
}

















































