#include "Transaccion.h"
#include <iostream>
using namespace std;

/**
 * Toma los datos de un flujo de entrada (cin)
 * Les asigna los datos del flujo a los atributos de la clase
 * Retorna la entrada.
 * @param entrada de flujo de datos
 * @return entrada de flujo de datos
 */
istream &Transaccion::cargar(istream &entrada){
    //Nota: 
    //si inicializo con 0 se cae el programa (no entiendo el por qué).
    //Si no inicializo se ejecuta sin problemas.
    //Agradezco explicación. Supongo que es porque en el constructor lo inicializo siempre en 0 y con tamaño pero no estoy seguro.

    //n_Persona1Ptr = 0;
    //n_Persona2Ptr = 0;
    entrada >> n_Persona1Ptr;
    entrada >> n_Persona2Ptr;
    entrada >> t_monto;

    return entrada;
}

/**
 * Toma un flujo de datos de salida (cout)
 * Le pasa los atributos de la clase mediante métodos get()
 * Retorna el flujo de datos de salida para ser impresos en consola.
 * @param salida usualmente es cout
 * @return salida de flujo de datos
 */
ostream &Transaccion::imprimir(ostream &salida)
{
    salida << getPersona1() << " " << getPersona2() << " " << getMonto();
    return salida;
}

/**
 * Compara un vector de caracteres con otro. (2 veces)
 * Lo hace restando el valor ascii de cada caracter entre vectores.
 * retorna esa diferencia para saber cuál vector es mayor alfabeticamente que otro.
 * @param otro es una transacción pasada por referencia, del cual se tomará su n_Persona1Ptr y n_Persona2Ptr para comparar con el del objeto actual.
 * @return int -1(nombre2 es mayor) | 0(iguales) | +1(nombre1 es mayor).
 */
int Transaccion::compararNombres(Transaccion &otra){

    //INFORMACIÓN IMPORTANTE:
    //sé que quizá se pueda modularizar pero no pude diseñar la manera.    
    int diferencia = 0;
    int i = 0;

    //por primer nombre de cada transferencia.
    do
    {
        diferencia = (int)this->n_Persona1Ptr[i] - (int)otra.n_Persona1Ptr[i];
    } while (!diferencia && this->n_Persona1Ptr[i] && otra.n_Persona1Ptr[i++]);

    //por segundo nombre de cada transferencia
    //el primer nombre de ambas transacciones es igual, entonces compara por el segundo nombre de ambas transacciones.   
    if (diferencia == 0){ 
        i = 0;
        do
        {
            diferencia = (int)this->n_Persona2Ptr[i] - (int)otra.n_Persona2Ptr[i];
        } while (!diferencia && this->n_Persona2Ptr[i] && otra.n_Persona2Ptr[i++]);
    }

    return diferencia;
}

/**
 * Compara por nombres de dos transacciones si estos son distintos. De no ser así retorna la diferencia entre los montos.
 * @param otra transaccion con el que se quiere comparar.
 * @return la diferencia entre montos si los nombres son iguales
 * @return la diferencia entre nombres si son distintos. 
 */
int Transaccion::compararTodo(Transaccion &otra){
    if ( (*this) == otra){ //si son iguales por nombres
        return this->t_monto - otra.t_monto;
    }

    return compararNombres(otra); //al no ser nombres iguales entre transacciones, los compara por nombres.
}

/**
 * Cuenta la longitud de un vector de caracteres pasado por parámetro para crear uno nuevo
 * Asigna los caracteres del vector pasado por parámetros un vector dinámico
 * Retorna el vector dinámico
 * @param hilera vector de caracteres que será copiado.
 * @return el vector copia.
 */
char* Transaccion::copiar(char* hilera){
    int length = getLength(hilera);

    char*nuevo = new char[length +1];

    for(int i=0; i < length; ++i){
        nuevo[i] = hilera[i];
    }
    nuevo[length] = '\0';
    return nuevo;
}

/**
 * Libera la memoria de los atributos si estos existen.
 * Les asigna un valor nulo.
 */
void Transaccion::liberarMemoria()
{
    if (n_Persona1Ptr){
        delete[] n_Persona1Ptr;
        n_Persona1Ptr = 0;
    }
    if (n_Persona2Ptr){
        delete[] n_Persona2Ptr;
        n_Persona2Ptr = 0;
    }
    t_monto = 0;
}

/**
 * Toma una hilera de caracteres y cuenta su longitud.
 * @param hilera hilera de caracteres de la que se quiere saber la longitud
 * @return int longitud de la cadena de caracteres pasada por parámetro
 */
int Transaccion::getLength(char *hilera){
    int length = 0;
    while (hilera[length]){
        ++length;
    }
    return length;
}

/**
 * Constructor por omisión de la clase Transaccion
 * Inicializa los atributos de la clase en nulos
 */
Transaccion::Transaccion(){
    n_Persona1Ptr = 0;
    n_Persona1Ptr = new char[1];
    n_Persona1Ptr[0] = '\0';

    n_Persona2Ptr = 0;
    n_Persona2Ptr = new char[1];
    n_Persona2Ptr[0] = '\0';

    t_monto = 0;
}

/**
 * Constructor de copia
 * Hace una copia a la instancia actual desde otra pasada por parámetro.
 * @param otra transaccion de la que se quiere copiar.
 */ 
Transaccion::Transaccion(Transaccion &otra){
    n_Persona1Ptr = 0;
    n_Persona2Ptr = 0;

    n_Persona1Ptr = copiar(otra.n_Persona1Ptr);
    n_Persona2Ptr = copiar(otra.n_Persona2Ptr);
    t_monto = otra.t_monto;
}

/**
 * Constructor por parámetros.
 * Inicializa los atributos de la clase con los datos pasados por parámetro.
 * @param persona1 vector de caracteres que representa el nombre de la persona1 que debe el monto
 * @param persona2 vector de caracteres que representa el nombre de la persona2 que recibe el monto
 * @param monto cantidad de dinero que se transfiere
 */
Transaccion::Transaccion(char *persona1, char *persona2, double monto){
    n_Persona1Ptr = 0;
    n_Persona2Ptr = 0;

    n_Persona1Ptr = copiar(persona1);
    n_Persona2Ptr = copiar(persona2);
    t_monto = monto;
}

/**
 * Destructor de la clase
 * Llama a liberarMemoria() para que se encargue.
 */
Transaccion::~Transaccion(){
    liberarMemoria();
}

/**
 * Retorna por referencia el atributo n_Persona1Ptr
 */
char *&Transaccion::getPersona1(){
    return n_Persona1Ptr;
}

/**
 * Retorna por referencia el atributo n_Persona2Ptr
 */
char *&Transaccion::getPersona2(){
    return n_Persona2Ptr;
}

/**
 * Retorna por referencia el atributo t_monto
 */
double &Transaccion::getMonto(){
    return t_monto;
}

/**
 * Retorna el resultado booleano de lo que retorne (compararTodo(param) < 0)
 * Si el metodo compararTodo() retorna un valor menor a cero quiere decir que la transaccion es menor al que se quiere comparar
 * Por lo que la operación booleana tomará el valor de 1. Lo cual hace que se cumpla la propiedad del operador <
 * @param otra transaccion con la que se quiere comparar la instancia actual
 * @return el resultado booleano.
 */
int Transaccion::operator<(Transaccion &otra){
    return (compararTodo(otra) < 0);
}

/**
 * Retorna lo opuesto a compararNombres() ya que este retorna 0 si los nombres son iguales
 * Si las transacciones son iguales retorna 1 (true).
 * @return int resultado booleano de comparar dos transacciones
 */
int Transaccion::operator==(Transaccion &otra){
    return !(compararNombres(otra));
}

/**
 * Retorna el valor dado por compararNombres() ya que este retorna 0 si los nombres son iguales
 * Si las transacciones son diferentes retorna 1 (true).
 * @return int resultado booleano de comparar dos transacciones 
 */
int Transaccion::operator!=(Transaccion &otra){
    return compararNombres(otra);
}
