/*
Practica: Pilas
Desarrollar un programa en C++ que permita realizar las siguientes operaciones en una Pila que tiene n elementos (4pts c/u):

● Contar cuántos elementos hay en una pila. 
● obtener la inversa de una pila. 
● Si se tiene una Pila de n elementos crear una nueva pila que contenga los elementos en orden de mayor a menor (el mayor debería estar en el fondo de la pila, y el menor en la cima). 
● Si se tiene una Pila de n elementos crear una nueva pila que contenga los elementos en orden de menor a mayor  (el menor debería estar en el fondo de la pila, y el mayor en la cima). 
● eliminar el elemento que se encuentre en el fondo de la pila.   

Realizar los metodos necesarios para realizar las operaciones anteriores.
*/
#include <iostream>
using namespace std;

#define TAMANIO 10   // Capacidad de la pila
typedef int TipoDato;

/** Clase Pila
 *  Se encarga de simular una pila de tamaño "TAMANIO"
 */
class Pila {
public:
	Pila();    					 	 
	void insertar(TipoDato elemento);
	TipoDato quitar();
	bool estaVacia() const;        
	bool estaLlena() const;
	int obtenerValorCima() const;
	void quitarFondo();       
private:
	int cima;     			  
	TipoDato array[TAMANIO];
};

Pila::Pila() 
	: cima(-1) {
}

/** 
 * Agrega un elemento a la pila
 * en caso de que la pila esté llena, finaliza el programa 
 */
void Pila::insertar(TipoDato elemento) {

	if (estaLlena()) {
		cout << "Desbordamiento de pila" << endl;
		exit(1);	
	}
	cima++;
	array[cima] = elemento;
}

/** quitar
 * Eliminar el último elemento agregado a la pila
 * en caso de que la pila esté vacia, finaliza el programa
 */
TipoDato Pila::quitar() {

	TipoDato aux;

	if (estaVacia()) {
		cout << "Intento de sacar un elemento de una lista vacía" << endl;
		exit(1);
	}
	aux = array[cima];
	cima--;
	return aux;
}

bool Pila::estaVacia() const {
	return cima == -1;
}

bool Pila::estaLlena() const {
	return cima == TAMANIO;
}

int Pila::obtenerValorCima() const {
	return cima;
}

/** quitarFondo
 * Elimina el primer elemento de la pila (corresponde al fondo)
 * Guardamos n-1 elementos de la pila en un vector
 * y por último los regresamos
 */
void Pila::quitarFondo() {

	if (estaVacia()) 
		return; 

	TipoDato array_aux[TAMANIO];
	int indice_array = 0;

	while (!estaVacia()) { // guardamos los n-1 elementos de la pila

		if (cima != 0) { 
			array_aux[indice_array++] = quitar();	
		}
		else
			quitar();
	}
	while(indice_array > 0) { // regresamos los n-1 elementos a la pila
		insertar(array_aux[--indice_array]);
	}
}

/** ContarElementos
 * Obtenemos la cantidad de elementos que hay en la pila usando el valor de "cima" 
 */ 
void contarElementos(Pila p) {

	int cimaPila = p.obtenerValorCima();
	if (p.estaVacia())
		cout << "No hay elementos en la pila" << endl;
	else
		cout << "hay " << cimaPila + 1 << " elementos en la pila" << endl;  
}

void mostrar_pila(Pila entrada){

	while (!entrada.estaVacia()) {
		cout << entrada.quitar() << " ";
	}
	cout << endl;
}

/** Obtener la inversa de una pila
 * se crea una pila auxiliar, el último elemento de la pila "entrada"
 * será el primero (fondo) del auxiliar
 */
Pila obtenerInversa(Pila entrada) {

	Pila aux_pila;
	TipoDato aux_elemento;

	while (!entrada.estaVacia()) {
		aux_elemento = entrada.quitar();
		aux_pila.insertar(aux_elemento);
	}

	return aux_pila;
}

void ordenarMayorAMenor(TipoDato array[], int TAM){

	for (int indice = 0; indice < TAM; indice++) {
		int posicion = indice;
		int aux = array[indice];

		while ((posicion > 0) && (array[posicion-1] < aux)) {
			array[posicion] = array[posicion-1];
			posicion--;
		}
		array[posicion] = aux;
	}
}

void ordenarMenorAMayor(TipoDato array[], int TAM){

	for (int indice = 0; indice < TAM; indice++) {
		int posicion = indice;
		int aux = array[indice];

		while((posicion > 0) && (array[posicion-1] > aux)) {
			array[posicion] = array[posicion-1];
			posicion--;
		}
		array[posicion] = aux;
	}
}

/** mayor_a_menor
 * Si se tiene una Pila de n elementos crear una nueva pila que contenga 
 * los elementos en orden de mayor a menor 
 * (el mayor debería estar en el fondo de la pila, y el menor en la cima)
 */
Pila mayor_a_menor(Pila entrada) {
	
	TipoDato array_aux[TAMANIO];
	int num_elementos = 0;

	// primero sacamos todos los elementos de la pila en un array_aux
	while (!entrada.estaVacia()) {
		array_aux[num_elementos] = entrada.quitar();
		num_elementos++;
	}
	ordenarMayorAMenor(array_aux, num_elementos);

	Pila pila_aux;

	// insertamos los elementos a una pila auxiliar
	for (int restantes = num_elementos, i = 0; restantes > 0; restantes--, i++) {
		pila_aux.insertar(array_aux[i]);
	}
	return pila_aux;
}

/**
 * Si se tiene una Pila de n elementos crear una nueva pila que contenga 
 * los elementos en orden de menor a mayor  
 * (el menor debería estar en el fondo de la pila, y el mayor en la cima).
 */
Pila menor_a_mayor(Pila entrada) {

	TipoDato array_aux[TAMANIO];
	int num_elementos = 0;

	// primero sacamos todos los elementos de la pila en un array_aux
	while (!entrada.estaVacia()) {
		array_aux[num_elementos] = entrada.quitar();
		num_elementos++;
	}
	ordenarMenorAMayor(array_aux, num_elementos);

	Pila pila_aux;

	// insertamos los elementos a una pila auxiliar
	for (int restantes = num_elementos, i = 0; restantes > 0; restantes--, i++) {
		pila_aux.insertar(array_aux[i]);
	}
	return pila_aux;	
}

int main() {

	Pila pila_entrada, pila_aux;

	cout << "\nEl primer elemento de la pila es el que está más a la derecha" << endl;
	contarElementos(pila_entrada);
	
	// valores de prueba
	pila_entrada.insertar(10);
	pila_entrada.insertar(5);
	pila_entrada.insertar(7);
	pila_entrada.insertar(30);
	pila_entrada.insertar(1);
	
	contarElementos(pila_entrada);
	cout << "\nLa pila de entrada: ";
	mostrar_pila(pila_entrada);
	
	cout << "\nObtener la inversa" << endl;
	pila_aux = obtenerInversa(pila_entrada);
	mostrar_pila(pila_aux);
	mostrar_pila(pila_entrada);	

	cout << "\nObtener pila ordenada de mayor a menor" << endl;
	pila_aux = mayor_a_menor(pila_entrada);
	mostrar_pila(pila_aux);

	cout << "\nObtener pila ordenada de menor a mayor" << endl;
	pila_aux = menor_a_mayor(pila_entrada);
	mostrar_pila(pila_aux);

	cout << "\nQuitando el fondo de la pila" << endl;
	mostrar_pila(pila_entrada);
	pila_entrada.quitarFondo();
	mostrar_pila(pila_entrada);
	return 0;
}