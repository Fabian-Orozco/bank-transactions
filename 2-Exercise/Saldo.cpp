#include "Saldo.h"
#include <iostream>
using namespace std;

/**
 * Toma los datos de un flujo de entrada (cin)
 * Les asigna los datos del flujo a los atributos de la clase
 * Retorna la entrada.
 * @param entrada de flujo de datos
 * @return entrada de flujo de datos
 */
istream &Saldo::cargar(istream &entrada){
    //INFORMACION IMPORTANTE: 
    //si inicializo con 0 se cae el programa (no entiendo el por qué).
    //Si no inicializo se ejecuta sin problemas.
    //Agradezco explicación. Supongo que es porque en el constructor lo inicializo siempre en 0 y con tamaño pero no estoy seguro.

    //n_PersonaPtr = 0;
    entrada >> n_PersonaPtr;
    entrada >> s_monto;
    return entrada;
}

/**
 * Toma un flujo de datos de salida (cout)
 * Le pasa los atributos de la clase mediante métodos get()
 * Retorna el flujo de datos de salida para ser impresos en consola.
 * @param salida usualmente es cout
 * @return salida de flujo de datos
 */
ostream &Saldo::imprimir(ostream &salida){
    salida << getNombre() << " " << getMonto();
    return salida;
}

/**
 * Cuenta la longitud de un vector de caracteres pasado por parámetro para crear uno nuevo
 * Asigna los caracteres del vector pasado por parámetros un vector dinámico
 * Retorna el vector dinámico
 * @param hilera vector de caracteres que será copiado.
 * @return el vector copia.
 */
char* Saldo::copiar(char* hilera){
    int length = getLength(hilera);
    char*nuevo = new char[length + 1];
    
    for(int i=0; i < length; ++i){
        nuevo[i] = hilera[i];
    }
    nuevo[length] = '\0';
    return nuevo;
}

/**
 * Compara un vector de caracteres con otro.
 * Lo hace restando el valor ascii de cada caracter entre vectores.
 * retorna esa diferencia para saber cuál vector es mayor alfabeticamente que otro
 * @param otro es un saldo pasado por referencia, del cual se tomará su n_PersonaPtr para comparar con el del objeto actual.
 * @return int -1(nombre2 es mayor) | 0(iguales) | +1(nombre1 es mayor).
 */
int Saldo::compararNombres(Saldo &otro){
    int diferencia = 0;
    int i = 0;

    do
    {
        diferencia = (int)this->n_PersonaPtr[i] - (int)otro.n_PersonaPtr[i];
    } while (!diferencia && this->n_PersonaPtr[i] && otro.n_PersonaPtr[i++]);
    
    return diferencia;
}

/**
 * Compara por nombres de dos saldos si estos son distintos. De no ser así retorna la diferencia entre los montos.
 * @param otro saldo con el que se quiere comparar.
 * @return la diferencia entre montos si los nombres son iguales
 * @return la diferencia entre nombres si son distintos. 
 */
int Saldo::compararTodo(Saldo &otro){
    if ( (*this)==otro){ //son iguales por nombres.
        return this->s_monto - otro.s_monto;
    }
    return compararNombres(otro);
}

/**
 * Libera la memoria de los atributos si estos existen.
 * Les asigna un valor nulo.
 */
void Saldo::liberarMemoria(){
    if (n_PersonaPtr){
        delete[] n_PersonaPtr;
        n_PersonaPtr = 0;
    }
    s_monto = 0;
}

/**
 * Toma una hilera de caracteres y cuenta su longitud.
 * @param hilera hilera de caracteres de la que se quiere saber la longitud
 * @return int longitud de la cadena de caracteres pasada por parámetro
 */
int Saldo::getLength(char *hilera){
    int length = 0;
    while (hilera[length]){
        ++length;
    }
    return length;
}

/**
 * Constructor por omisión de la clase Saldo
 * Inicializa los atributos de la clase en nulos
 */
Saldo::Saldo()
{
    n_PersonaPtr = 0;
    n_PersonaPtr = new char[1];
    n_PersonaPtr[0] = '\0';

    s_monto = 0;
}

/**
 * Constructor de copia
 * Hace una copia a la instancia actual desde otra pasada por parámetro.
 * @param otro saldo del que se quiere copiar.
 */ 
Saldo::Saldo(Saldo &otro)
{
    n_PersonaPtr = copiar(otro.n_PersonaPtr);
    s_monto = otro.s_monto;
}

/**
 * Constructor por parámetros.
 * Inicializa los atributos de la clase con los datos pasados por parámetro.
 * @param nombre vector de caracteres que representa el nombre de la persona que posee el monto
 * @param monto cantidad de dinero que tiene una persona en un momento específico
 *
 */
Saldo::Saldo(char *nombre, double monto)
{
    n_PersonaPtr = 0;
    n_PersonaPtr = copiar(nombre);
    s_monto = monto;
}

/**
 * Destructor de la clase
 * Llama a liberarMemoria() para que se encargue.
 */
Saldo::~Saldo()
{
    liberarMemoria();
}

/**
 * Retorna por referencia el atributo n_PersonaPtr
 */
char *& Saldo::getNombre(){
    return n_PersonaPtr;
}

/**
 * Retorna por referencia el atributo s_monto
 */
double & Saldo::getMonto(){
    return s_monto;
}

/**
 * Retorna el resultado booleano de lo que retorne (compararTodo(param) < 0)
 * Si el metodo compararTodo() retorna un valor menor a cero quiere decir que el saldo es menor al que se quiere comparar
 * Por lo que la operación booleana tomará el valor de 1. Lo cual hace que se cumpla la propiedad del operador <
 * @param otro saldo con el que se quiere comparar la instancia actual
 * @return el resultado booleano.
 */
int Saldo::operator<(Saldo & otro){
    return (compararTodo(otro) < 0);
}

/**
 * Retorna lo opuesto a compararNombres() ya que este retorna 0 si los nombres son iguales
 * Si los saldos son iguales retorna 1 (true).
 * @return int resultado booleano de comparar dos saldos
 */
int Saldo::operator==(Saldo & otro){
    return !(compararNombres(otro));
}

/**
 * Retorna el valor dado por compararNombres() ya que este retorna 0 si los nombres son iguales
 * Si los saldos son diferentes retorna 1 (true).
 * @return int resultado booleano de comparar dos saldos
 */
int Saldo::operator!=(Saldo & otro){
    return compararNombres(otro);
}