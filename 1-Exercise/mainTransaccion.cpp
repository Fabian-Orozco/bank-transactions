#include <iostream>
#include "Transaccion.h"

using namespace std;

int main(){
    cout << endl;

    //Prueba constructores
    Transaccion t1((char*)"Antonio",(char*) "Benito", 1500.50); //por parámetros
    cout << "t1: " << t1 << endl; //Prueba sobrecarga de << y métodos get();
    
    Transaccion t2; //por omisión
    cout << "t2: " << t2 << endl;
    t2 = t1; //por copia
    cout << "t2: " << t2 << endl;
    
    Transaccion t3 = t2; //por copia en declaración
    cout << "t3: " << t3 << endl;
    
    //prueba que tienen direcciones de memoria distintas
    cout << "&t1: " << &t1 << "\t&t2: " << &t2 << "\t&t3: " << &t3  << endl;

    //Prueba método cargar
    Transaccion t4;
    cout << "Digite el nombre de la primer persona, segunda persona y monto de la transacción: ";
    cin >> t4;
    cout << "t4: " << t4 << endl;

    //Prueba liberación de memoria
    Transaccion * t5 = new Transaccion((char*)"name",(char*) "name2", 3.14);
    cout << "t5: " << *t5 << endl;
    delete t5;
    

    //prueba metodos ==, !=, <.
    Transaccion t6((char*) "Carla", (char*) "Denisha",2000.6);
    cout << "t6: " << t6 << endl;
    Transaccion t7((char*) "Carla", (char*) "Denisha",3000.7);
    cout << "t7: " << t7 << endl;
    
    if(t1==t2){ //es verdadero a propósito
        cout << "t1 igual que t2" << endl;
    }

    if(t1!=t6){ //es verdadero a propósito
        cout << "t1 diferente a t6" << endl;
    }

    if(t1<t7){ //es verdadero a propósito
        cout << "t1 menor que t7" << endl;
    }
    else{ //es falso a propósito
        cout << "t6 menor que t1" << endl;
    }
    if(t6<t7){ //es verdadero a propósito. Compara por saldos ya que los nombres son iguales
        cout << "t6 es menor que t7" << endl;
    }
    
    cout << endl;
    return 0;
}