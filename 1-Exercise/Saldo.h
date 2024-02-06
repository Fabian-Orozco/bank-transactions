#ifndef SALDO_B95690
#define SALDO_B95690

#include <iostream>
using namespace std;

class Saldo{

   friend istream & operator>>(istream & entrada, Saldo & saldo){ //método amigo que sobrecarga el operador >> para cargar valores en un saldo.
       return saldo.cargar(entrada);
   }
   friend ostream & operator<<(ostream & salida, Saldo & saldo){ //método amigo que sobrecarga el operador << para leer/imprimir los valores de un saldo.
       return saldo.imprimir(salida);
   }
    private:
        char * n_PersonaPtr; //puntero a vector de caracteres (contiene el nombre de la persona que posee el saldo)
        double s_monto; //double que contiene la cantidad de dinero que posee una persona
        
        istream& cargar(istream &); //asigna/carga los valores pasados por parámetro en los atributos del saldo.
        ostream& imprimir(ostream &); //Retorna los valores del saldo.

        char* copiar(char*); //Toma un vector de caracteres, cuenta su longitud, crea otro
        int compararNombres(Saldo&); //Compara por nombres. Retorna Retorna un int dependiendo de: -1(persona2 es mayor) | 0(igual) | +1(persona1 es mayor).
        int compararTodo(Saldo&); //compara por nombres y si es necesario, también por saldos. Funciona para operator<
        void liberarMemoria(); //elimina el vector (si existe). Y reinicia el valor de monto a 0.
        int getLength(char *); //retorna la longitud de una cadena de caracteres.
    public:

    Saldo(); //Constructor por omisión
    Saldo(Saldo&); //Constructor de copia  
    Saldo(char*, double); //Constructor por parámetros (recibe nombre de la persona, además del monto que posee)
    ~Saldo();       //destructor del saldo

    char*& getNombre(); //retorna el nombre de la persona por referencia
    double& getMonto(); //retorna el monto que posee la persona por referencia

    int operator<(Saldo &); //compara entre dos saldos (primero por nombre y si son iguales, compara por monto) para saber si una es menor que la otra.
    int operator==(Saldo &); //compara entre dos saldos (por nombres) para saber si son iguales. Retorna booleano
    int operator!=(Saldo &); //utiliza el metodo privado comparar(Saldo &).

};

#endif