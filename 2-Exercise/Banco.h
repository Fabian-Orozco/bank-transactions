#ifndef _BANCOHA_B95690_
#define _BANCOHA_B95690_

#include "Saldo.h"
#include "Transaccion.h"
#include "ListaTransaccion.h"
#include "ListaSaldo.h"

#include <fstream>
#include <iostream>
using namespace std;

class Banco{
    private:
        ListaTransaccion * listaTransacciones; //lista con las transacciones realizadas.
        ListaSaldo * listaSaldos; //lista con los pares (persona, monto).
        ListaSaldo * listaBalances; //lista con los balances (persona, monto).

    public:
        Banco(); //inicializa el banco creando las listas.
        ~Banco(); //libera la memoria ocupada por las listas.

        void cargueTransacciones();
        void genereSaldos();
        void genereBalances();

        void imprimir();
};

#endif