#include <windows.h>
#include <iostream>
#include <fstream>

#include "ListaTransaccion.h"
#include "ListaSaldo.h"

#include "Transaccion.h"
#include "Saldo.h"

#include "Banco.h"

using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    cout << endl;

    Banco b1;
    b1.cargueTransacciones();
    b1.genereSaldos();
    b1.genereBalances();
    b1.imprimir();
    
    cout << endl;
    return 0;
}