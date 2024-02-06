#include "ListaSaldo.h"
#include <iostream>

using namespace std;

/**
 * Constructor de la clase Celda.
 * @param elemento es el saldo que se quiere crear dentro de la celda.
 */
ListaSaldo::Celda::Celda(Saldo  elemento){
   Saldo * nuevo = new Saldo(elemento);
   this->elemento = *nuevo;
   anterior = 0;
   siguiente = 0;
}

/**
 * Destructor de la clase Celda.
 * Destruce la celda siguiente si ésta existe.
 */
ListaSaldo::Celda::~Celda(){
   if (siguiente)
      delete siguiente;
}

/**
 * Constructor por omisión de la clase Iterador.
 * Inicializa el puntero de celda a 0
 */
ListaSaldo::Iterador::Iterador(){
   actual = 0;
}

/**
 * Constructor por parámetros de la clase Iterador
 * @param actual es el puntero a la celda celda que estará "apuntando" el iterador.
 */
ListaSaldo::Iterador::Iterador(Celda *actual){
   this->actual = actual;
}

/**
 * Método sobrecargado de desreferenciamiento
 * Sirve para obtener el elemento de la celda a la cual apunta el iterador
 * @return el elemento saldo de la celda a la cual "apunta" el iterador.
 */
Saldo &ListaSaldo::Iterador::operator*(){
   return actual->elemento;
}

/**
 * Método sobrecargado de preincremento
 * Hace que el iterador apunte a la celda siguiente.
 * @return la misma instancia iterador pero modificada (apunta a la celda siguiente).
 */
ListaSaldo::Iterador &ListaSaldo::Iterador::operator++(){
   if(actual)
      actual = actual->siguiente;
   return *this;
}

/**
 * Método sobrecargado de posincremento
 * Hace que el iterador apunte a la celda siguiente mediante el preincremento.
 * Luego retorna su valor antiguo
 * @param desambiguador funciona para desambiguar entre el preincremento y el posIncremento ya que utiliza el mismo operador. (sobrecarga de parámetros)
 * @return retorna su valor anterior.
 */
ListaSaldo::Iterador ListaSaldo::Iterador::operator++(int desambiguador){
   Iterador viejo(actual);
   ++(*this);
   return viejo;
}

/**
 * Método sobrecargado de igualdad
 * Compara entre iteradores mediante la comparación de sus elementos (celdas). 
 * @param otro es con el iterador que se desea comparar.
 * @return int booleano. 1 si son iguales 0 si son distintas.
 */
int ListaSaldo::Iterador::operator==(Iterador otro){
   return this->actual == otro.actual;
}

/**
 * Método sobrecargado de desigualdad
 * Compara entre iteradores mediante la comparación de sus elementos (celdas). 
 * @param otro es con el iterador que se desea comparar.
 * @return int booleano. 1 si son distintas 0 si son iguales.
 */
int ListaSaldo::Iterador::operator!=(Iterador otro){
   return !(*this == otro);
}

/**
 * Metodo que retorna un iterador que apunta al inicio de la lista
 * @return iterador que apunta a la primer celda de la lista.
 */
ListaSaldo::Iterador ListaSaldo::begin(){
   Iterador inicio(primera);
   return inicio;
}

/**
 * Metodo que retorna un iterador que apunta nulo (constructor por omisión)
 * @return iterador que no apunta nada. (al final, después del último elemento).
 */
ListaSaldo::Iterador ListaSaldo::end(){
   Iterador fin;
   return fin;
}

/**
 * Constructor por omisión de la clase ListaSaldo
 * Inicializa los atributos (punteros a celda) con nulo (0).
 */
ListaSaldo::ListaSaldo(){
   primera = 0;
   ultima = 0;
}

/**
 * Constructor de copia de la clase ListaSaldo
 * Inicializa los atributos de la clase con 0.
 * Hace una copia de la instancia pasada por referencia en la instancia actual.
 * Utiliza push_back() para ir creando los elementos de la lista.
 * @param otra lista de saldos de la que se quiere hacer la copia
 */
ListaSaldo::ListaSaldo(const ListaSaldo &otra){
   primera = 0;
   ultima = 0;
   Celda *actual = otra.primera;
   while (actual){
      this->push_back(actual->elemento);
      actual = actual->siguiente;
   }
}

/**
 * Destructor de la clase
 * Si existe al menos una celda, llama a su destructor y su destructor se encarga de liberar las demás.
 */
ListaSaldo::~ListaSaldo(){
   if(primera)
      delete primera;
}

/**
 * @return int booleano si la lista posee al menos una celda retorna 0, si la lista no posee una celda retorna 1.
 */
int ListaSaldo::isEmpty(){
   return !primera;
}

/**
 * Toma un flujo de datos de salida (cout)
 * Le pasa los elementos de la lista
 * Retorna el flujo de datos de salida para ser impresos en consola mediante sobrecarga de <<.
 * @param salida usualmente es cout
 * @return salida de flujo de datos pasados a la salida.
 */
ostream & ListaSaldo::imprimir(ostream &salida){
   Celda *actual = primera;
   while (actual){
      salida << actual->elemento << endl;
      actual = actual->siguiente;
   }
   return salida;
}

/**
 * Busca un saldo entre todos los elementos de la lista.
 * @param saldoABuscar es el elemento que se busca dentro de la lista
 * @return iterador que apunta a la celda donde se encuentra el saldo que se busca (de ser encontrado). 0 de ser que no se haya encontrado.
 */
ListaSaldo::Iterador ListaSaldo::buscar(Saldo saldoABuscar){
   Celda *actual = primera;
   while (actual && actual->elemento != saldoABuscar){
      actual = actual->siguiente;
   }
   Iterador posicion(actual); //se crea ya sea que lo haya encontrado o que esté en nulo porque no lo encontró.
   return posicion;
}

/**
 * Inserta un elemento nuevo a la lista en una posición específica, mueve el elemento (de ser que lo haya) que se encuentra allí hacia la derecha.
 * @param posicionAInsertar es la posición en la lista donde se desea insertar el nuevo elemento.
 * @param saldoAInsertar es el elemento que se desea insertar en la lista.
 * @return la misma instancia pero modificada (con el nuevo elemento en ella).
 */
ListaSaldo &ListaSaldo::insertar(Iterador posicionAInsertar, Saldo saldoAInsertar){
   Iterador inicio = this->begin();
   Iterador fin = this->end();

   if (isEmpty() && posicionAInsertar == fin)
      push_front(saldoAInsertar);

   else{ //si no está vacía o la posición a insertar no era nula
      if (posicionAInsertar == fin)  //si no está vacía y se desea insertar al final
         push_back(saldoAInsertar);

      else{ //si no está vacía y se desea insertar en otra posición distinta al final.
         if (posicionAInsertar == inicio)
            push_front(saldoAInsertar);
            
         else{ //se desea insertar en el medio de otras dos celdas
            Celda *nueva = new Celda(saldoAInsertar);
            nueva->siguiente = posicionAInsertar.actual;
            nueva->anterior = posicionAInsertar.actual->anterior;
            posicionAInsertar.actual->anterior->siguiente = nueva;
            posicionAInsertar.actual->anterior = nueva;
         }
      }
   }
   return *this;
}

/**
 * Crea/agrega un elemento al inicio de la lista.
 * @param elemento el saldo que se quiere agregar a la lista
 * @return ListaSaldo por referencia, la misma lista pero con modificaciones (el nuevo elemento).
 */
ListaSaldo &ListaSaldo::push_front(Saldo saldoAInsertar){
   Celda *nueva = new Celda(saldoAInsertar);
   if (primera){
      nueva->siguiente = primera;
      primera->anterior = nueva;
      primera = nueva;
   }
   else{
      primera = nueva;
      ultima = nueva;
   }
   return *this;
}

/**
 * Crea/agrega un elemento al final de la lista.
 * @param elemento el saldo que se quiere agregar a la lista
 * @return ListaSaldo por referencia, la misma lista pero con modificaciones (el nuevo elemento).
 */
ListaSaldo & ListaSaldo::push_back(Saldo elemento){
   Celda *nueva = new Celda(elemento);
   if (isEmpty()){
      primera = nueva;
      ultima = nueva;
   }
   else{
      ultima->siguiente = nueva;
      nueva->anterior = ultima;
      ultima = nueva;
   }
   return *this;
}

/**
 * Inserta un elemento en orden de menor a mayor (ascendente).
 * @param saldoAInsertar es el saldo que se desea insertar en la lista de manera ordenada
 * @return ListaSaldo por referencia, la misma lista pero con modificaciones (el nuevo elemento).
 */
ListaSaldo& ListaSaldo::insertarOrdenMenorAMayor(Saldo saldoAInsertar){
   Celda *actual = primera;
   while(actual && !(saldoAInsertar < actual->elemento)){
      actual = actual->siguiente;
   }
   Iterador posicionActual(actual);
   insertar(posicionActual, saldoAInsertar);
   return (*this);
}