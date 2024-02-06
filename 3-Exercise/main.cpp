#include <iostream>
#include "Separador.h"

using namespace std;

int main(){
    cout << endl;

    char * hilera = (char*) "que bueno\tser programador";
    
    Separador *s1 = new Separador(hilera);
    s1->separar(hilera);
    cout << "Cada palabra por separado:\n" << *s1;

    cout << endl;
    delete s1;
    return 0;
}