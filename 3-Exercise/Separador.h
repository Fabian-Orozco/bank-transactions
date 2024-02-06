#ifndef _SEPARADOR_B95690_
#define _SEPARADOR_B95690_

#include <iostream>
using namespace std;

class Separador{
    friend ostream& operator<<(ostream & entrada, Separador & separador){
        return separador.imprimir(entrada);
    }
    private:
        char ** puntero;
        int palabras;

        int cuentePalabras(const char *);
        int getLengthPalabra(const char *, int);
        void pedirMemoria(const char *);
        void rellenarCeldas(const char *);
        ostream& imprimir(ostream&);

    public:
        Separador();
        Separador(char *);
        ~Separador();
        char * * separar(const char *); 
        void liberar(char * * p);
};
#endif