#include "Saldo.h"
#include "Transaccion.h"
#include "ListaTransaccion.h"
#include "ListaSaldo.h"
#include "Banco.h"

#include <fstream>
#include <iostream>
using namespace std;

/**
 * Carga las transacciones (una por línea) desde un archivo de texto.
 * Las almacena en una lista de transacciones (atributo de la clase).
 */
void Banco::cargueTransacciones(){
    ifstream entradaDeDatos; 
    entradaDeDatos.open("Transacciones.txt");
    Transaccion * nueva = 0;

    while(!entradaDeDatos.eof()){
        nueva = new Transaccion();
        entradaDeDatos >> (*nueva);
        listaTransacciones->insertarOrdenMenorAMayor(*nueva);
        delete nueva;
    }
}

/**
 * Genera dos saldos por cada transacción de la lista de transacciones ya generada.
 * Se utiliza la fórmula a-a*2 para darle un valor negativo al saldo de la persona deudora.
 * Después de generarlos, los agrega a una lista de saldos en forma ordenada.
 */
void Banco::genereSaldos(){
    ListaTransaccion::Iterador inicio = listaTransacciones->begin();
    ListaTransaccion::Iterador fin = listaTransacciones->end();
    Saldo *nuevo = 0;

    while(inicio != fin){
        nuevo = new Saldo( (*inicio).getPersona1() , ((*inicio).getMonto()-(*inicio).getMonto()*2));
        listaSaldos->insertarOrdenMenorAMayor(*nuevo);
        delete nuevo;

        nuevo = new Saldo( (*inicio).getPersona2() , ((*inicio).getMonto()));
        listaSaldos->insertarOrdenMenorAMayor(*nuevo);
        
        delete nuevo;
        ++inicio;
    }
}

/**
 * Genera balances (saldos) con el monto que posee cada persona en total (cobrado y que debe).
 * Lo hace a partir de la lista de saldos.
 * Recorre toda la lista con un elemento comparando un saldo "estático" <<actual>> con un saldo <<inicio>> "variante".
 * Suma a la variable b_monto si define que son saldos iguales (de la misma persona).
 * Al final del recorrido genera un saldo con el nombre de la persona y el b_monto que tiene.
 * Y aumenta el iterador de saldo <<actual>> para volver a hacer la comparación pero con otra persona.
 * Esto lo hace hasta terminar de comparar todos los saldos.
 */
void Banco::genereBalances(){
    ListaSaldo::Iterador inicio = listaSaldos->begin();
    ListaSaldo::Iterador fin = listaSaldos->end();
    ListaSaldo::Iterador actual = listaSaldos->begin();
    Saldo *nuevo = 0;
    double b_monto = 0;

    while(actual != fin){
        while(inicio != fin){
            if( (*actual) == (*inicio)){                
                b_monto += (*inicio).getMonto();
            }
            ++inicio;
        }
        if( listaBalances->buscar(*actual) == 0){
            nuevo = new Saldo( (*actual).getNombre() , b_monto);
            listaBalances->insertarOrdenMenorAMayor(*nuevo);
            delete nuevo;
            
        }
        b_monto = 0;
        ++actual;
        inicio = listaSaldos->begin();
    }
}

/**
 * Crea las listas de manera dinámica para que puedan ser manipuladas desde fuera por medio de los métodos.
 */
Banco::Banco(){
    listaTransacciones = new ListaTransaccion();
    listaSaldos = new ListaSaldo();
    listaBalances = new ListaSaldo();
}

/**
 * Destructor de la clase
 * Libera la memoria de las listas
 */
Banco::~Banco(){
    delete listaTransacciones;
    delete listaSaldos;
    delete listaBalances;
}

/**
 * Imprime las listas que poseen los bancos si éstas existen.
 */
void Banco::imprimir(){
    cout << "Lista de transacciones: " << endl;
    if( !(listaTransacciones->isEmpty()))
        cout << (*listaTransacciones) << endl;
    else{cout << "Está vacía, genere transacciones primero" << endl;}

    cout << "Lista de saldos: " << endl;
    if( !(listaSaldos->isEmpty()))
        cout << (*listaSaldos) << endl;
    else{cout << "Está vacía, genere saldos primero" << endl;}
    
    cout << "Lista de balances: " << endl;
    if( !(listaBalances->isEmpty()))
        cout << (*listaBalances) << endl;
    else{cout << "Está vacía, genere balances primero" << endl;}
}