#include "Separador.h"
#include <iostream>

using namespace std;

/**
 * Toma una oración y cuenta la cantidad de espacios en blanco que posee, suma 1 a esa cantidad para evaluar la cantidad de palabras que tiene.
 * @param hilera es la frase u oración representada por un vector de caracteres del cual se quiere saber la cantidad de palabras.
 * @return int es la cantidad de palabras que contiene la oración.
 */
int Separador::cuentePalabras(const char * hilera){
    int i=0;
    int cantidadBlancos = 0;

    while(hilera[i]){
        if(hilera[i] == ' ' || hilera[i] == '\t'){
            ++cantidadBlancos;
        }
        ++i;
    }
    return cantidadBlancos+1;
}
/**
 * Toma una frase y una posición (para saber cuál es la palabra deseada) y cuenta sus caracteres, retorna la cantidad contada (su longitud).
 * @param hilera es un vector constante de caracteres que representa una hilera o frase de la que se desea saber la longitud(cantidad de caracteres) de una palabra en específico.
 * @param posicion es la posición en notación de vector del primer caracter de la palabra que se desea saber su longitud.
 * @return la longitud de una palabra que está dentro de una oración.
 */
int Separador::getLengthPalabra(const char * hilera, int posicion ){ 
    int length = 0;
    while(hilera[posicion] && hilera[posicion] != ' ' && hilera[posicion] != '\t'){
        ++posicion;
        ++length;
    }
    return length;
}

/**
 * Pide memoria para cada vector de caracteres de manera dinámica
 * @param hilera es la hilera de la que se quiere pedir memoria (según la longitud de cada palabra).
 */
void Separador::pedirMemoria(const char * hilera){
    puntero = new char*[palabras + 1];
    int palabrasRecorridas = 0; 
    int cantidadDeLetras = 0;
    int letraActual = 0;
    
    for(int i=0; palabrasRecorridas < palabras-1; ++i){ 
        if (&hilera[0] == &hilera[i] || hilera[i] == ' ' || hilera[i] == '\t'){ //si hay nueva palabra
            
            if(&hilera[i] != &hilera[0]){ //si se encuentra en el primer caracter de una palabra distinta a la primer palabra de la hilera.
                ++palabrasRecorridas;
                letraActual = i+1;
                } 
            cantidadDeLetras = getLengthPalabra(hilera,letraActual);
            puntero[palabrasRecorridas] = new char[cantidadDeLetras+1];
            }
    }
}

/**
 * Toma una hilera, la recorre, y escribe cada palabra dentro de vectores de caracteres ya existentes y con tamaño definido.
 * @param hilera es la hilera de la cual se tomarán las palabras para rellenar los vectores.
 */
void Separador::rellenarCeldas(const char * hilera){
    
    //NOTA: la asistente me recomendó dejar los cout porque se ven ordenados y muestran el funcionamiento del programa. Me pareció buena idea.
    
    int palabrasRecorridas = 0;
    int cantidadDeLetras = 0;
    int letraActual = 0;

    for(int i=0; palabrasRecorridas < palabras-1; ++i){ 
        if (&hilera[0] == &hilera[i] || hilera[i] == ' ' || hilera[i] == '\t'){//si hay nueva palabra
            cout << "Comienza una palabra" << endl;
            if(&hilera[i] != &hilera[0]){ //si se encuentra en el primer caracter de una palabra distinta a la primer palabra de la hilera.
                ++palabrasRecorridas; 
                letraActual = i+1; 
                }
            cantidadDeLetras = getLengthPalabra(hilera,letraActual);
            cout << "Cantidad de letras: " << cantidadDeLetras << endl;
            cout << "\nRellenando: " << endl;
            for(int j = 0; j < cantidadDeLetras; ++j){
                cout << "celda[" << palabrasRecorridas << "][" << j << "] con ";
                cout << hilera[letraActual] << endl;
                puntero[palabrasRecorridas][j] = hilera[letraActual];
                ++letraActual;
            }
            cout << "celda[" << palabrasRecorridas << "][" << cantidadDeLetras << "] con '\\0'" << endl;
            cout << endl;
            puntero[palabrasRecorridas][cantidadDeLetras] = '\0';
            }
    }
    puntero[palabras] = 0;
    cout << "celda[" << palabras << "] con 0\n" << endl;

}

/**
 * Toma un puntero de punteros a char y lo libera
 * Comienza por liberar los vectores de caracteres de cada uno de los punteros.
 * Después libera el vector de punteros.
 * Por último declara al puntero a nulo.
 * @param punteroALiberar es el puntero de punteros a char del que se quiere liberar memoria.
 * 
 */
void Separador::liberar(char ** punteroALiberar)
{   
    cout << "Liberando los vectores char"<< endl;
    for (int i = palabras-1; i >= 0; --i)
        {
            cout << "punteroALiberar[" << i<< "]: " << punteroALiberar[i] << endl;
            delete[] punteroALiberar[i];
        }
        cout << "Liberando el vector de punteros con dirección: " << punteroALiberar << endl;
        delete[] punteroALiberar;
        palabras = 0;
        punteroALiberar = 0;
}

/**
 * Toma una salida de flujo <<cout>> y envía por ella los datos(cada vector de caracteres) del atributo <<puntero>>. Retorna esa salida para mostrarla en consola.
 * @return salida con los datos del atributo <<puntero>>
 */ 
ostream& Separador::imprimir(ostream & salida){
    int j = 0;
    for(int i = 0; i < palabras; ++i){
        while(puntero[i][j] != '\0'){
            salida << puntero[i][j];
            ++j;
        }
        j = 0;
        salida << "\n";
    }
    return salida;
}

/**
 * Constructor por omisión de la clase Separador. Inicializa el puntero como nulo.
 */
Separador::Separador(){
    puntero = new char*[1];
    puntero = 0;
    palabras = 0;
}

/**
 * Constructor por parámetros de la clase Separador. 
 * Inicializa el atributo <<palabras>> con la cantidad de palabras de la hilera.
 * Inicializa el atributo <<puntero>> con el método pedirMemoria(param).
 */
Separador::Separador(char * hilera){
    palabras = cuentePalabras(hilera);
    pedirMemoria(hilera);
}

/**
 * Destructor de la clase Separador.
 * Libera memoria mediante un método llamado liberar(param);
 */
Separador::~Separador(){
    liberar(puntero);
}

/**
 * Separa una hilera en vectores de caracteres (un vector por palabra).
 * Utiliza el método rellenarCeldas(param) para ello.
 * @return retorna un puntero de punteros a char que será el atributo de la clase Separador, es decir <<puntero>>.
 */
char ** Separador::separar(const char * hilera){
    rellenarCeldas(hilera);
    return puntero;
}