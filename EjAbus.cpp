#include <iostream>
#include <stdlib.h>
using namespace std;


template <class T>

class Busqueda {

    private:
        vector<T> list;


    public:
        Busqueda();
        ~Busqueda();

        int busquedaSecuencial(T val);





};
int iLevels = 0;

int tower(int [] arr, int elem) {
    if(arr[elem - 1] == 0)
        return elem;
    else {
        if(arr[elem / 2] == 0)
        iLevels += (elem / 2) + 1;
            return tower(arr, )
    }
}



int main() {



    return 0;
}