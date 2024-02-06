#ifndef _TRANSACCION_B95690_
#define _TRANSACCION_B95690_

#include <iostream>
using namespace std;

class Transaccion{

   friend istream & operator>>(istream & entrada, Transaccion & transaccion){ //método amigo que sobrecarga el operador >> para cargar valores en una transacción.
       return transaccion.cargar(entrada);
   }
   friend ostream & operator<<(ostream & salida, Transaccion & transaccion){ //método amigo que sobrecarga el operador << para leer/imprimir los valores de una transacción.
       return transaccion.imprimir(salida);
   }
    private:
        char * n_Persona1Ptr; //puntero a vector de caracteres (nombre de persona1).
        char * n_Persona2Ptr; //puntero a vector de caracteres (nombre de persona2).
        double t_monto;       //monto que se transfiere de persona1 a persona2.

        istream& cargar(istream &); //asigna/carga los valores pasados por parámetro en los atributos de la transacción
        ostream& imprimir(ostream &); //Retorna los valores de la transacción.

        int compararNombres(Transaccion&); //Compara por nombres. Retorna un int dependiendo de: -1(persona2 es mayor) | 0(igual) | +1(persona1 es mayor).
        int compararTodo(Transaccion&); //Compara por nombres y luego por saldo (para operator <).
        char* copiar(char *); //libera memoria y copia los nombres pasados por parámetro a los nombres de la transacción.
        void liberarMemoria(); //elimina los vectores (si los hay). Y reinicia el valor de monto a 0.
        int getLength(char *); //retorna la longitud de una cadena de caracteres.
    
    public:

    Transaccion(); //Constructor por omisión.
    Transaccion(Transaccion&); //Constructor de copia.
    Transaccion(char*, char*, double); //Constructor por parámetros (recibe nombre de persona1 y persona2, además del monto que se transfiere).
    ~Transaccion(); //Destructor de la clase. Libera memoria de ambos vectores y asigna a los atributos un nulo (0).

    char* & getPersona1(); //retorna el nombre de la persona1 por referencia.
    char* & getPersona2(); //retorna el nombre de la persona2 por referencia.
    double& getMonto(); //retorna el monto que posee la persona por referencia.

    int operator<(Transaccion &); //compara entre dos transacciones (primero por nombre y si son iguales, compara por monto) para saber si una es menor que la otra.
    int operator==(Transaccion &); //compara entre dos transacciones (por nombres) para saber si son iguales. Retorna booleano (0 o 1).
    int operator!=(Transaccion &); //utiliza el metodo == sobre cargado, retorna su opuesto. Retorna booleano (0 o 1).

};

#endif

