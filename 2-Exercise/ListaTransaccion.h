#ifndef LISTATRANSACCION_B95690
#define LISTATRANSACCION_B95690
#include <iostream>
#include "Transaccion.h"

using namespace std;

class ListaTransaccion
{
    friend class Iterador;
    friend ostream &operator<<(ostream &salida, ListaTransaccion &lista){
        return lista.imprimir(salida);
    }

private:
    class Celda{
    public:
        Transaccion elemento;
        Celda *anterior;
        Celda *siguiente;
        Celda(Transaccion);
        ~Celda();
    };

    Celda *primera;
    Celda *ultima;

public:
    class Iterador{
        friend class ListaTransaccion;

    private:
        Celda *actual;

    public:
        Iterador();
        Iterador(Celda *);
        Transaccion &operator*();
        Iterador &operator++();
        Iterador operator++(int);
        int operator==(Iterador);
        int operator!=(Iterador);
    };

    ListaTransaccion();             
    ListaTransaccion(const ListaTransaccion &); 
    ~ListaTransaccion();
    int isEmpty();

    ostream &imprimir(ostream &);
    Iterador buscar(Transaccion); 
    
    ListaTransaccion &insertar(Iterador, Transaccion& );
    ListaTransaccion &push_front(Transaccion);
    ListaTransaccion &push_back(Transaccion); 
    ListaTransaccion& insertarOrdenMenorAMayor(Transaccion);

    Iterador begin();
    Iterador end();
};

#endif
