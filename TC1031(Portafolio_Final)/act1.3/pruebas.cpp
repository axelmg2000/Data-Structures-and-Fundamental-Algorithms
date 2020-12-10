#include <iostream>
#include <vector>
#include <iostream>
using namespace std;


/*
int main() {
  vector<int> a = {10, 10, 10, 10, 10, 12 , 12, 12, 14, 14, 14, 15};


  int primerDia = a.at(0);
  int delta = a.size() - 1;
  bool lastTransactionFirstDay = false;
  

  if(a.at(delta) == primerDia)
      cout << "No hay segundo día" << endl;
  else {
    delta /= 2;
    // Binary search for the last transaction of the first day
    while(lastTransactionFirstDay == false) {
      if(a.at(delta) == primerDia) {
        if(a.at(delta + 1) == primerDia) 
          delta += (delta / 2);
        else {
          lastTransactionFirstDay = true;
          delta = delta + 1;
        }
      }
      else 
        delta -= (delta / 2);

      cout << delta << endl;
    }
    // Now delta has the first 
  }
  cout << delta;

}
*/  








