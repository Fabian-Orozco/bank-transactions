#include <iostream>
#include "Saldo.h"

using namespace std;

int main(){
    cout << endl;
    
    //Prueba constructores
    Saldo s1((char*)"Antonio",1000.1); //por parámetros
    cout << "s1: " << s1 << endl; //prueba sobrecarga << y métodos get().

    Saldo s2; //por omisión
    cout << "s2: " << s2 << endl;

    s2 = s1; //por copia
    cout << "s2: " << s2 << endl;

    Saldo s3 = s1; //por copia en declaración
    cout << "s3: " << s3 << endl;

    //prueba que tienen direcciones de memoria distintas
    cout << "Dirección de memoria de cada instancia: &s1: " << &s1 << "\t&s2: " << &s2 << "\t&s3: " << &s3  << endl;
    
    //Prueba método cargar
    Saldo s4;
    cout << "Digite el nombre de la persona y su monto: ";
    cin >> s4;
    cout << "s4: " << s4 << endl;

    //Prueba liberación de memoria
    Saldo * s5 = new Saldo((char*)"Beatriz", 2000.2);
    cout << "s5: " << *s5 << endl;
    delete s5;

    //prueba metodos ==, !=, <.
    Saldo s6((char*) "Carla", 3000.3);
    cout << "s6: " << s6 << endl;
    Saldo s7((char*) "Carla", 4000.4);
    cout << "s7: " << s7 << endl;

    if(s1==s2){ //es verdadero a propósito
        cout << "s1 igual que s2" << endl;
    }

    if(s1!=s6){ //es verdadero a propósiso
        cout << "s1 diferente a s6" << endl;
    }

    if(s1<s7){ //es verdadero a propósito
        cout << "s1 menor que s7" << endl;
    }

    else{ //es falso a propósito
        cout << "s6 menor que s1" << endl;
    }

    if(s6<s7){ //es verdadero a propósito. Compara por saldos ya que los nombres son iguales
        cout << "s6 es menor que s7" << endl;
    }

    cout << endl;
    return 0;
}