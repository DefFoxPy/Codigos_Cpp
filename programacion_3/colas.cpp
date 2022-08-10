/*
Desarrollar
un programa para simular la cola en un banco y determinar cuántas
personas de cada género son atendidas en un determinado periodo de
tiempo y cuántos depósitos y retiros se hacen. Se debe tomar como
entrada el cliente que llega, el cual debe aportar la edad, sexo, tipo
de transacción y condición de salud. Si el cliente es de la tercera edad
va a una cola, si es mujer y esta  embarazada va a otra cola junto con
los discapacitados, y el resto sin condiciones especiales entran a una
tercera cola. Se debe fijar un tiempo de duración por transacción. El
programa debe ser implementado en C++. Aparte de evaluar los
conocimientos teórico prácticos tendrán puntos extras por su ingenio y
creatividad. Deben entregar la explicación de como se ejecuta la cola
(instructivo), el algoritmo del mismo y su codificación (archivo cpp).
El programa debe correr
*/

#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

// Constantes usadas para los clientes
enum valores_cliente {
	CERO,
	HOMBRE,
	MUJER,
	DEPOSITO,
	RETIRO,
	NORMAL,       
	DISCAPACITADO,
	EMBARAZADA,
};

const int TIEMPO_DEPOSITO = 5;   // tiempo fijo que se tarda en antender a alguien que va a depositar
const int TIEMPO_RETIRO = 5;     // tiempo fijo que se tarda en antender a alguien que va a retirar
const int TIEMPO_MIN_CLIENTE = 1;// rango minimo para que llegue un nuevo cliente
const int TIEMPO_MAX_CLIENTE = 3;// rango máximo para que llegue un nuevo cliente
const int MAYOREDAD = 60;
const bool INGRESARAUTOMATICAMENTE = true; // si desea ingresar los datos de forma manual igualelo a true
string lineaDivisora = "-----------------------------------";

// Metodo para la validacion de datos
// https://www.delftstack.com/es/howto/cpp/cpp-input-validation/
template<typename T>
T &validarEntrada(T &valor) {

	while (true) {
		if (cin >> valor) {
			break;
		}
		else {
			cout << "Ingrese un valor valido!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	return valor;
}

/* Clase cliente
Contiene sus datos básicos y funciones que permiten asignar su valores
ya sea de forma automatica o de forma manual
*/
class Cliente {
private:
	int edad;
	int sexo;
	int condicion;      
	int operacion;

public:
	Cliente(bool);
	Cliente(){}
	void setEdad();
	void setEdadAuto();
	void setSexo();
	void setSexoAuto();
	void setCondicion();
	void setCondicionAuto();
	void setOperacion();
	void setOperacionAuto();
	int getEdad() const {return edad;}
	string getSexo() const;
	string getCondicion() const;
	string getOperacion() const;
	int getTiempoAtender() const; // indica cuanto tiempo requieren atender al cliente según la operacion
	void mostrarDatos() const;
};

/* Clase Nodo
Usada para la cola, contiene como datos al cliente y un puntero
*/
class Nodo {
protected:
	Cliente elemento;
	Nodo* siguiente;
public:
	Nodo(){}
	~Nodo(){}
	Nodo(Cliente c) {elemento = c; siguiente = NULL;}
	Cliente getElemento() const {return elemento;}
	void setElemento(Cliente c) {elemento = c;}
	Nodo* getSiguiente()const {return siguiente;}
	void setSiguiente(Nodo *e) {siguiente = e;}
};

/*he ehstado 
*/
class Cola {
private:
	Nodo *frente, *final;
	int numero_elementos;
	int tiempoAtender; // indica en que tiempo pueden atender a otro cliente

public:
	Cola() {frente = NULL; final = NULL; numero_elementos = 0; tiempoAtender=0;}
	~Cola();
	int getNumeroElementos() const {return numero_elementos;}
	void setTiempoAtender(int t) {tiempoAtender = t;}
	int getTiempoAtender() const {return tiempoAtender;}
	void insertar(Cliente);
	Cliente quitar();
	bool estaVacia() const {return !frente;}
};

class Registro {
private:
	int cantidadRetiro;          // indica la cantidad de personas que retiraron dinero
	int cantidadDeposito;        // indica la cantidad de personas que depositaron dinero
	int hombresAtentidos;        // indica la cantidad de hombres atendidos
	int mujeresAtendidas;        // indica la cantidad de mujeres atendidas
	int cantidadPersonas;        // indica cuantas personas llegaron al banco

public:
	Registro() {cantidadRetiro = 0; cantidadDeposito = 0; hombresAtentidos = 0; mujeresAtendidas = 0;cantidadPersonas = 0;}
	~Registro(){}
	void mostrarResultados() const;
	int getCantidadPersonas() const {return cantidadPersonas;}
	void incrementarCantidadPersonas() {cantidadPersonas++;}
	void registrarCliente(Cliente);
};

Cola::~Cola() {
	while(frente != NULL) {
		Nodo *aux;
		aux = frente;
		frente = frente->getSiguiente();
		delete aux;
	}
}

void Cola::insertar(Cliente elemento) {
	
	Nodo *nuevo_nodo = new Nodo();

	nuevo_nodo->setElemento(elemento);
	nuevo_nodo->setSiguiente(NULL);

	if (estaVacia()) {
		frente = nuevo_nodo;
	} 
	else {
		final->setSiguiente(nuevo_nodo);
	}
	final = nuevo_nodo;
	numero_elementos++;
}

Cliente Cola::quitar() {
	
	Nodo *aux = frente;

	if (estaVacia()) {
		cout << "Intento de sacar un elemento en una cola vacía" << endl;
		exit(-1);
	}
	
	Cliente dato = frente->getElemento();

	if(frente == final) { // si hay un solo elemento
		frente = NULL;
		final = NULL;
	}
	else {
		frente = frente->getSiguiente();
	}
	delete aux;
	numero_elementos--;
	return dato;
}

Cliente::Cliente(bool asignarAutomaticamente) {
	
	if (asignarAutomaticamente == false){
		setEdad();
		setSexo();
		setCondicion();
		setOperacion();
	}
	else {
		setEdadAuto();
		setSexoAuto();
		setCondicionAuto();
		setOperacionAuto();
	}
}

void Cliente::setEdad() {
	int edad_aux;

	cout << "Ingrese la edad: ";
	edad_aux = validarEntrada(edad_aux);

	while (edad_aux < 18) {
		cout << "El cliente debe ser mayor de edad!" << endl;
		cout << "Ingrese la edad: ";
		edad_aux = validarEntrada(edad_aux);
	}
	cout << endl;
	edad = edad_aux; 
}

void Cliente::setEdadAuto() {
	edad = 18 + rand() % (90-18);
}

void Cliente::setSexo() {
	int sex_aux;
	cout << "Ingrese\n(" << HOMBRE << ") para hombre o (" << MUJER <<") para mujer: ";
	sex_aux = validarEntrada(sex_aux);

	while (sex_aux != HOMBRE && sex_aux != MUJER) {
		cout << "Ingresó un sexo no válido!" << endl;
		cout << "Ingrese(" << HOMBRE << ") para hombre o (" << MUJER <<") para mujer: ";
		sex_aux = validarEntrada(sex_aux);
	}
	cout << endl;
	sexo = sex_aux;
}

void Cliente::setSexoAuto() {
	sexo = HOMBRE + rand() % (MUJER+1);
}
	
void Cliente::setOperacion() {

	cout << "Ingrese\n(" << RETIRO << ") para retirar o (" << DEPOSITO << ") para depositar: ";
	int aux_op = validarEntrada(aux_op);

	while (aux_op != RETIRO && aux_op != DEPOSITO) {
		cout << "Ingreso una operacion invalida!" << endl;
		cout << "ingrese\n(" << RETIRO << ") para retirar o (" << DEPOSITO << ") para depositar: ";
		aux_op = validarEntrada(aux_op);
	}
	cout << endl;
	operacion = aux_op;
}

void Cliente::setOperacionAuto() {
	operacion = DEPOSITO + rand() % (RETIRO-DEPOSITO+1);
}

void Cliente::setCondicion() {
	int aux_cod = 0;

	if (getSexo() == "Mujer") {
		cout << "Ingrese:\n(" << NORMAL << ") si no posee ninguna condicion" << endl
		     << "(" << EMBARAZADA <<") si está embarazada" << endl
		     << "(" << DISCAPACITADO << ") si tiene una condicion (discapacitada)" << endl;
		aux_cod = validarEntrada(aux_cod);

		while (aux_cod != NORMAL && aux_cod != EMBARAZADA && aux_cod != DISCAPACITADO) {
			cout << "Ingresó una condicion invalida!" << endl;
			cout << "Ingrese:\n(" << NORMAL << ") si no posee ninguna condicion" << endl
	     		 << "(" << EMBARAZADA <<") si está embarazada" << endl
	    		 << "(" << DISCAPACITADO << ") si tiene una condicion (discapacitada)" << endl;
			aux_cod = validarEntrada(aux_cod);
		}
	}
	else {
		cout << "Ingrese:\n(" << NORMAL << ") si no posee ninguna condicion" << endl
		     << "(" << DISCAPACITADO << ") si tiene una condicion (discapacitado)" << endl;
		aux_cod = validarEntrada(aux_cod);

		while (aux_cod != NORMAL && aux_cod != DISCAPACITADO) {
			cout << "Ingresó una condicion invalida!" << endl;
			cout << "Ingrese:\n(" << NORMAL << ") si no posee ninguna condicion" << endl
	     		 << "(" << EMBARAZADA <<") si está embarazada" << endl
	    		 << "(" << DISCAPACITADO << ") si tiene una condicion (discapacitada)" << endl;
			aux_cod = validarEntrada(aux_cod);
		}
	}	
	cout << endl;
	condicion = aux_cod;
}

void Cliente::setCondicionAuto() {
	if (getSexo() == "Hombre") {
		condicion = NORMAL + rand() % (DISCAPACITADO-NORMAL+1);
	}
	else {
		condicion = NORMAL + rand() % (EMBARAZADA-NORMAL+1);
	}
}

string Cliente::getSexo() const {
	return sexo == HOMBRE ? "Hombre" : "Mujer";
}

string Cliente::getOperacion() const {
	return operacion == RETIRO ? "Retirar" : "Depositar";
}

string Cliente::getCondicion() const {
	
	if (condicion == NORMAL) return "Normal";
	if (condicion == DISCAPACITADO) return "Discapacitado";
	if (condicion == EMBARAZADA) return "Embarazada";
	return "None";
}

void Cliente::mostrarDatos() const {
	
	cout << "Datos del cliente:" << endl
	     << "Edad:      " << getEdad() << endl
	     << "Sexo:      " << getSexo() << endl
	     << "Operacion: " << getOperacion() << endl
	     << "Condicion: " << getCondicion() << endl;
}

int Cliente::getTiempoAtender() const {
	if (getOperacion() == "Retirar") return TIEMPO_RETIRO;
	else return TIEMPO_DEPOSITO;
}

void Registro::mostrarResultados() const {
	cout << lineaDivisora << endl
	     << "Personas total que llegaron       " << getCantidadPersonas() << endl
	     << "Hombres atendidos:                " << hombresAtentidos << endl
	     << "Mujeres atendidas:                " << mujeresAtendidas << endl
	     << "Cantidad retiros realizados:      " << cantidadRetiro << endl
	     << "Cantidad de depositos realizados: " << cantidadDeposito << endl
	     << lineaDivisora << endl;
}

void Registro::registrarCliente(Cliente cliente) {
	
	cliente.getSexo() == "Hombre" ? hombresAtentidos++ : mujeresAtendidas++;
	cliente.getOperacion() == "Retirar" ? cantidadRetiro++ : cantidadDeposito++; 
}

// funciones auxiliares para la simulación
int calcularTiempoNuevoCliente(int);
void atenderCliente(Cola&, Registro&, int);

int main() {
	
	int tiempoSimulacion;      // indica el tiempo de simulación en minutos 
	int tiempoNuevoCliente;    // tiempo en que llega un nuevo cliente
	int tiempoActual = 0;      // indica en que tiempo de la simulacion estamos
	Registro registroBanco;
	Cola colaTerceraEdad;
	Cola colaDiscapacitados;
	Cola colaNormal;
	srand(time(NULL)); // inicializar numeros aleatorios

	cout << "Ingrese el tiempo de simulación en minutos: ";
	cin >> tiempoSimulacion;
	tiempoNuevoCliente = calcularTiempoNuevoCliente(0);
	cout << "Inicio de la simulacion" << endl << lineaDivisora << endl;

	// ciclo principal de la simulacion
	while (tiempoActual <= tiempoSimulacion) {
		cout << "Tiempo: " << tiempoActual << endl;
		
		// ha llegado un nuevo cliente
		if (tiempoActual == tiempoNuevoCliente) { 
			cout << "Un nuevo cliente ha llegado al banco" << endl;
			Cliente cliente = Cliente(INGRESARAUTOMATICAMENTE);
			
			// segun los datos del cliente ira en una cola 
			if (cliente.getEdad() >= MAYOREDAD) {
				colaTerceraEdad.insertar(cliente);
				cout << "Cliente agregado a la cola de tercera edad" << endl;
			}
			else if (cliente.getCondicion() == "Discapacitado" || cliente.getCondicion() == "Embarazada") {
				colaDiscapacitados.insertar(cliente);
				cout << "Cliente agregado a la cola de discapacitados" << endl;
			} 
			else {
				colaNormal.insertar(cliente);
				cout << "Cliente agregado a la cola de gente normal" << endl;
			}
			tiempoNuevoCliente = calcularTiempoNuevoCliente(tiempoActual);
			registroBanco.incrementarCantidadPersonas();
		}
		
		// las colas son independientes
		atenderCliente(colaTerceraEdad, registroBanco, tiempoActual);
		atenderCliente(colaDiscapacitados, registroBanco, tiempoActual);
		atenderCliente(colaNormal, registroBanco, tiempoActual);
		
		tiempoActual++;
		cout << lineaDivisora << endl;
	}
	cout << "Simulacion Finalizada." << endl << endl;
	registroBanco.mostrarResultados();
	cout << "Cantidad de personas que quedaron en la cola al final de la simulacion:" << endl
	     << "Tercera edad: " << colaTerceraEdad.getNumeroElementos() << endl
	     << "Discapacitados:" << colaDiscapacitados.getNumeroElementos() << endl
	     << "Normal: " << colaNormal.getNumeroElementos() << endl;
	return 0;
}

int calcularTiempoNuevoCliente(int tiempoActual) {
	return tiempoActual + TIEMPO_MIN_CLIENTE + rand() % (TIEMPO_MAX_CLIENTE - TIEMPO_MIN_CLIENTE);
}

void atenderCliente(Cola &cola, Registro &registroBanco, int tiempoActual) {
	
	if (!cola.estaVacia() && cola.getTiempoAtender() <= tiempoActual){
		Cliente atender = cola.quitar();
		registroBanco.registrarCliente(atender);
		cout << "Cliente atendido" << endl;
		atender.mostrarDatos();
		cola.setTiempoAtender(tiempoActual + atender.getTiempoAtender()); 
	}
}

