#ifndef LISTASALDO_B95690
#define LISTASALDO_B95690
#include <iostream>
#include "Saldo.h"

using namespace std;

class ListaSaldo{
    friend class Iterador;
    friend ostream &operator<<(ostream &salida, ListaSaldo &lista){
        return lista.imprimir(salida);
    }

private:
    class Celda{
    public:
        Saldo elemento;
        Celda *anterior;
        Celda *siguiente;
        Celda(Saldo);
        ~Celda();
    };
    Celda *primera;
    Celda *ultima;

public:
    class Iterador{
        friend class ListaSaldo;

    private:
        Celda *actual;

    public:
        Iterador();
        Iterador(Celda *);
        Saldo &operator*();
        Iterador &operator++();
        Iterador operator++(int);
        int operator==(Iterador);
        int operator!=(Iterador);
    };

    ListaSaldo();             
    ListaSaldo(const ListaSaldo &);
    ~ListaSaldo();
    int isEmpty();

    ostream &imprimir(ostream &);
    Iterador buscar(Saldo);
    
    ListaSaldo &insertar(Iterador, Saldo);
    ListaSaldo &push_front(Saldo);
    ListaSaldo &push_back(Saldo);
    ListaSaldo& insertarOrdenMenorAMayor(Saldo);

    Iterador begin();
    Iterador end();
};

#endif
