#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream> 
#include <sstream>
#include <math.h>
#include <cstdlib>

using namespace std;

class NodoBinario {
public:

	NodoBinario(int i,int num, string nCiudad, NodoBinario *der = NULL, NodoBinario *izq = NULL, NodoBinario *sig = NULL, NodoBinario *ant = NULL) :
		indice(i),Hizq(izq), nombreCiudad(nCiudad), Hder(der), cedulaC(num), siguiente(sig), anterior(ant), FB(0) {}


	int cedulaC,indice;
	string nombreCiudad;
	int FB;
	NodoBinario *Hizq, *Hder, *siguiente, *anterior;

	friend class Pila;
	friend class ABB;

	void InsertaBinario(int num, string nombreCiudad);
	bool BuscarBinario(int num);
};

typedef NodoBinario *pnodo;
typedef NodoBinario *pNodoBinario;

void PreordenR(NodoBinario* R);
void InordenR(NodoBinario* R);
void PostordenR(NodoBinario* R);
int i = 0;
class ABB {
public:
	pNodoBinario raiz;

	ABB() :raiz(NULL) {}

	void InsertaCliente(int num, string nombreCiudad);
	void PreordenI();
	void InordenI();
	void PostordenI();
	bool Hh;
	void Borrar(NodoBinario *nodoB, bool);
	void BorrarBalanceado(NodoBinario *r, bool, int eliminar);
	void Equilibrar1(NodoBinario *n, bool);
	void Equilibrar2(NodoBinario *n, bool);
	void RotacionDobleIzquierda(NodoBinario *n1, NodoBinario *n2);
	void RotacionDobleDerecha(NodoBinario *n1, NodoBinario *n2);
	void RotacionSimpleIzquierda(NodoBinario *n1, NodoBinario *n2);
	void cargarClientes(string str);
	bool buscarCedula(int cedula);
	void RotacionSimpleDerecha(NodoBinario *n1, NodoBinario *n2);


};
bool ABB::buscarCedula(int cedula) {// Buscar un valor en el árbol
	if (raiz == NULL) {
		return false;
	}else {
		raiz->BuscarBinario(cedula);
	}
}

bool NodoBinario::BuscarBinario(int num) {
	if (num == cedulaC) {
		return true;
	}
	else {
		if (num < cedulaC) {
			if (Hizq == NULL) {
				return false;
			}
			else {
				Hizq->BuscarBinario(num);
			}
		}else {
			if (Hder == NULL) {
				return false;
			}
			else {
				Hder->BuscarBinario(num);
			}
		}
	}
}
string toString(int valor) {
	stringstream ss;
	ss << valor;
	string str = ss.str();
	return str;
}
class Pila {
public:
	Pila() : plista(NULL) {}

	void Push(pnodo);
	void Mostrar();
	bool Vacia() { return plista == NULL; }
	pnodo Pop();
	int Size();

	pnodo plista;
};
void Pila::Push(pnodo v)
{
	if (Vacia()) {
		plista = v;
	}
	else {
		NodoBinario *aux = plista;
		while (aux->siguiente) {
			aux = aux->siguiente;
		}
		aux->siguiente = v;
		v->anterior = aux;

	}
}

pnodo Pila::Pop() {
	pnodo borrar;
	pnodo salida = NULL;
	if (Vacia()) {
		cout << "Pila Vacia" << endl;
	}
	else {
		borrar = plista;
		while (borrar->siguiente) {
			borrar = borrar->siguiente;
		}
		if (Size() > 1) {
			salida = borrar;
			borrar->anterior->siguiente = NULL;
			borrar = NULL;
			delete borrar;
		}
		else {
			salida = plista;
			plista = NULL;
		}
	}
	return salida;
}

int Pila::Size() {
	while (plista && plista->anterior) plista = plista->anterior;
	int cont = 0;
	NodoBinario *aux;
	aux = plista;
	while (aux) {
		cont++;
		aux = aux->siguiente;
	}
	return cont;
}

void Pila::Mostrar() {
	if (Vacia()) {
		cout << "Vacia";
	}
	NodoBinario *aux = plista;
	while (aux) {
		cout << "Indice: "<<aux->indice<<" Cedula: " << aux->cedulaC << " Nombre: " + aux->nombreCiudad << " \n ";
		aux = aux->siguiente;
	}
}

void NodoBinario::InsertaBinario(int num, string nombreC)
{
	if (num < cedulaC) {
		if (Hizq == NULL) {
			Hizq = new NodoBinario(i,num, nombreC);
			i++;
		}
		else {
			Hizq->InsertaBinario(num, nombreC);
		}
	}
	else {
		if (Hder == NULL) {
			Hder = new NodoBinario(i, num, nombreC);
			i++;
		}
		else {
			Hder->InsertaBinario(num, nombreC);
		}
	}
}

void ABB::InsertaCliente(int num, string nombreCiudad){
	if (raiz == NULL) {
		raiz = new NodoBinario(i, num, nombreCiudad);
		i++;
	}
	else {
		raiz->InsertaBinario(num, nombreCiudad);
	}
}

void ABB::PreordenI() {
	NodoBinario *Act = raiz;
	Pila p;
	while (p.Vacia() == false || (Act != NULL)) {
		if (Act != NULL) {
			cout << "Indice: " << Act->indice << " Cedula: " << Act->cedulaC << " Nombre: " + Act->nombreCiudad << "\n";
			p.Push(Act);
			Act = Act->Hizq;
		}
		else {
			Act = p.Pop();
			Act = Act->Hder;
		}
	}
}

void ABB::InordenI() {
	NodoBinario *Act = raiz;
	Pila p;
	bool band = true;
	while (band) {

		while (Act != NULL) {
			p.Push(Act);
			Act = Act->Hizq;
		}
		if (!p.Vacia()) {
			Act = p.Pop();
			cout << "Indice: " << Act->indice << " Cedula: " << Act->cedulaC << " Nombre: " + Act->nombreCiudad << "\n";
			Act = Act->Hder;
		}
		if (p.Vacia() & Act == NULL) {
			break;
		}
	}
}

void ABB::PostordenI() {
	NodoBinario *Act = raiz;
	Pila p;
	Pila p2;
	while (!p.Vacia() || Act != NULL) {
		if (Act != NULL) {
			p2.Push(new NodoBinario(Act->indice,Act->cedulaC, Act->nombreCiudad));
			p.Push(Act);
			Act = Act->Hder;
		}
		else {
			Act = p.Pop();
			Act = Act->Hizq;
		}
	}
	while (!p2.Vacia()) {
		NodoBinario *salida = p2.Pop();
		cout << "Indice: " << salida->indice<< " Cedula: " << salida->cedulaC << "Nombre: " << salida->nombreCiudad << "\n";
	}
}

void PreordenR(NodoBinario *R) {

	if (R == NULL) {
		return;
	}
	else {
		cout << "Indice: " << R->indice << " Cedula: " << R->cedulaC << "Nombre: " << R->nombreCiudad << " - ";
		PreordenR(R->Hizq);
		PreordenR(R->Hder);
	}
}

void InordenR(NodoBinario *R) {

	if (R == NULL) {
		return;
	}
	else {
		InordenR(R->Hizq);
		cout << "Indice: " << R->indice << "Cedula: " << R->cedulaC << "Nombre: " << R->nombreCiudad << " - ";
		InordenR(R->Hder);
	}
}

void PostordenR(NodoBinario *R) {

	if (R == NULL) {
		return;
	}
	else {
		PostordenR(R->Hizq);
		PostordenR(R->Hder);
		cout << "Indice: " << R->indice << "Cedula: " << R->cedulaC << "Nombre: " << R->nombreCiudad << " - ";
	}
}

void ABB::Borrar(NodoBinario* D, bool Hh)
{
	pnodo q = NULL;
	if (D->Hder != NULL) {
		Borrar(D->Hder, Hh);
		if (Hh) {
			Equilibrar2(D, Hh);
		}
		else {
			q->cedulaC = D->cedulaC;
			q = D;
			D = D->Hizq;
			Hh = true;
		}
	}
}
void ABB::BorrarBalanceado(NodoBinario* raiz, bool Hh, int x)
{
	pnodo q = NULL;
	if (raiz != NULL) {
		if (x < raiz->cedulaC) {
			BorrarBalanceado(raiz->Hizq, Hh, x);
			if (Hh) {
				Equilibrar1(raiz, Hh);
			}
		}
		else {
			if (x > raiz->cedulaC) {
				BorrarBalanceado(raiz->Hder, Hh, x);
				if (Hh) {
					Equilibrar2(raiz, Hh);
				}
			}
			else {
				q = raiz;
			}
		}

		if (q->Hder == NULL) {
			raiz = q->Hizq;
			Hh = true;
		}
		else {
			if (q->Hizq == NULL) {
				raiz = q->Hder;
				Hh = true;
			}
			else {
				Borrar(q->Hizq, Hh);
			}
			if (Hh) {
				Equilibrar1(raiz, Hh);
			}
		}
	}
}

void ABB::Equilibrar1(NodoBinario* n, bool Hh) {
	NodoBinario *n1;
	switch (n->FB) {
	case -1: n->FB = 0;
		break;
	case 0: n->FB = 1;
		Hh = false;
		break;
	case 1: n1 = n->Hder;
		if (n1->FB >= 0) {
			if (n1->FB = 0) {
				Hh = false;
				RotacionSimpleDerecha(n, n1);
			}
			else {
				RotacionDobleDerecha(n, n1);
			}
		}
	}
}

void ABB::Equilibrar2(NodoBinario* n, bool Hh) {
	NodoBinario *n1;
	switch (n->FB) {
	case 1: n->FB = 0;
		break;
	case 0: n->FB = 1;
		Hh = false;
		break;
	case -1: n1 = n->Hizq;
		if (n1->FB <= 0) {
			if (n1->FB = 0) {
				Hh = false;
				RotacionSimpleIzquierda(n, n1);
			}
			else {
				RotacionDobleIzquierda(n, n1);
			}
		}
	}
}


void ABB::RotacionDobleIzquierda(NodoBinario* n, NodoBinario* n1) {
	NodoBinario *n2;
	n2 = n1->Hder;
	n->Hizq = n2->Hder;
	n2->Hder = n;
	n1->Hder = n2->Hizq;
	n2->Hizq = n1;

	if (n2->FB == 1) {
		n1->FB = -1;
	}
	else {
		n1->FB = 0;
	}
	if (n2->FB == -1) {
		n->FB = 1;
	}
	else {
		n->FB = 0;
	}
	n2->FB = 0;
	n = n2;
}

void ABB::RotacionDobleDerecha(NodoBinario* n, NodoBinario* n1) {
	NodoBinario *n2;
	n2 = n1->Hizq;
	n->Hder = n2->Hizq;
	n2->Hizq = n;
	n1->Hizq = n2->Hder;
	n2->Hder = n1;

	if (n2->FB == 1) {
		n->FB = -1;
	}else {
		n->FB = 0;
	}
	if (n2->FB == -1) {
		n1->FB = 1;
	}else {
		n1->FB = 0;
	}
	n2->FB = 0;
	n = n2;
}

void ABB::RotacionSimpleDerecha(NodoBinario* n, NodoBinario* n1) {
	n->Hder = n1->Hizq;
	n1->Hizq = n;

	if (n1->FB == 1) {
		n->FB = 0;
		n1->FB = 0;
	}
	else {
		n->FB = 1;
		n1->FB = -1;
	}
	n = n1;
}

void ABB::RotacionSimpleIzquierda(NodoBinario* n, NodoBinario* n1) {
	n->Hizq = n1->Hder;
	n1->Hder = n;

	if (n1->FB == -1) {
		n->FB = 0;
		n1->FB = 0;
	}
	else {
		n->FB = -1;
		n1->FB = -1;
	}
	n = n1;
}

int toInt(string valor) {
	stringstream x(valor);
	int resultado = 0;
	x >> resultado;
	return resultado;
}

ABB Clientes;
string delimiter = ";";
//Carga todos los usuarios y ingresa solo los que cumplan las validaciones.
void ABB::cargarClientes(string str) {
	size_t pos = 0;
	string cedula, nombre;
	while ((pos = str.find(delimiter)) != string::npos) {
		cedula = str.substr(0, str.find(delimiter));
		str.erase(0, str.find(delimiter) + 1);
		nombre = str.substr(0, str.find(delimiter));
		str.erase(0, str.find(delimiter) + 1);
		if (buscarCedula(toInt(cedula)) == false) {
			InsertaCliente(toInt(cedula), nombre);
		}
	}
}
class nodo {
public:
	nodo(int i, int cedula, string nombre) {
		indice = i;
		ced = cedula;
		nombre_usuario = nombre;
		siguiente = NULL;
	}
	nodo(int i, int cedula, string nombre, nodo * signodo) {
		indice = i;
		ced = cedula;
		nombre_usuario = nombre;
		siguiente = signodo;
	}
private:
	int indice, ced;
	string nombre_usuario;
	nodo *siguiente;


	friend class lista;
};

typedef nodo *pnodoL;


class lista {
public:
	lista() { primero = actual = NULL; }
	~lista();

	void InsertarCache(int i,int cedula,string nombre);
	void EliminarFinal();
	bool ListaVacia() { return primero == NULL; }
	void Mostrar();
	bool buscarCedula(int cedula);
	void mostrarCedula(int cedula);
	int largoLista();
	string lectura(string nombre);
	void Inicializar();
	void Cola();
	void cargarCiudad(string str);
private:
	pnodoL primero;
	pnodoL actual;
};
lista::~lista()
{
	pnodoL aux;
	while (primero) {
		aux = primero;
		primero = primero->siguiente;
		delete aux;
	}
	actual = NULL;
}
int lista::largoLista() {
	int cont = 0;

	pnodoL aux;
	aux = primero;
	if (ListaVacia()) {
		return cont;
	}
	else {
		while (aux != NULL) {
			aux = aux->siguiente;
			cont++;
		}
		return cont;
	}

}

void lista::InsertarCache(int i, int cedula, string nombre) {
	if (ListaVacia()) {
		primero = new nodo(i, cedula, nombre);
	}else{
		pnodoL aux = primero;
		while (aux->siguiente != NULL) {
			aux = aux->siguiente;
		}
		aux->siguiente = new nodo(i, cedula, nombre);
	}
}

bool lista::buscarCedula(int cedula) {
	bool result = false;
	if (primero == NULL) {
		return false;
	}
	else {
		pnodoL aux = primero;
		while (aux->siguiente != NULL) {
			if (aux->ced == cedula) {
				result = true;
			}
			aux = aux->siguiente;
		}
		return result;
	}
}
void lista::mostrarCedula(int cedula) {
	pnodoL aux = primero;
	while (aux->siguiente != NULL) {
		if (aux->ced == cedula) {
			cout << "Indice: " << aux->indice << " Cedula: " << aux->ced << " Nombre:" + aux->nombre_usuario << "\n";
			break;
		}
		aux = aux->siguiente;
	}
}
void lista::Mostrar() {
	nodo *aux;
	aux = primero;
	for (aux = primero; aux != NULL; aux = aux->siguiente) {
		cout <<"Indice: "<<aux->indice << " Cedula: "<< aux->ced <<" Nombre:" + aux->nombre_usuario << "\n";
	}
	cout << endl;
}
lista ListaCache;
void cache(string index, string arcClient) {
	int cont = 0;
	fstream datosI(index.c_str());
	string lineaI;
	if (!datosI.is_open()) {
		datosI.open(index.c_str(), ios::in);
	}
	string delimiter = ";";
	string cedula, cedulaC, nombre, indexado;
	while (getline(datosI, lineaI)) {
		if (cont <= 20) {
			indexado = lineaI.substr(0, lineaI.find(delimiter));
			lineaI.erase(0, lineaI.find(delimiter) + delimiter.length());
			cedula = lineaI.substr(0, lineaI.find(delimiter));
			lineaI.erase(0, lineaI.find(delimiter) + delimiter.length());

			fstream datosC(arcClient.c_str());
			string lineaC;
			if (!datosC.is_open()) {
				datosC.open(arcClient.c_str(), ios::in);
			}
			while (getline(datosC, lineaC)) {
				cedulaC = lineaC.substr(0, lineaC.find(delimiter));
				lineaC.erase(0, lineaC.find(delimiter) + delimiter.length());
				if (cedula == cedulaC) {
					nombre = lineaC.substr(0, lineaC.find(delimiter));
					datosC.close();
					break;
				}
			}
			ListaCache.InsertarCache(toInt(indexado), toInt(cedula), nombre);
		}
		else {
			break;
		}
	}
	datosI.close();
}

//Se encarga de leer todos los archivos .txt
void lectura() {
	fstream archivo;
	string frase;
	string clients = "Clientes.txt";
	archivo.open(clients.c_str(), ios::in);
	if (archivo.is_open()) {
			while (!archivo.eof()) {
				getline(archivo, frase);
				Clientes.cargarClientes(frase);
			}
	}else { cout << "Fichero inexistente o faltan permisos para abrirlo" << endl; }
	archivo.close();
}

void buscarCliente(int cedula) {
	if (ListaCache.buscarCedula(cedula)== true) {
		ListaCache.mostrarCedula(cedula);
	}
	else {
		cout<<"No esta en la cache"<<endl;
	}
}

void eliminarCliente(int cedula) {
	string linea, cedulaC, nombre;
	string delimiter = ";";
	ifstream fs("Clientes.txt"); //leer de este archivo
	ofstream fstemp("temp.txt"); //escribir en este archivo

	//modificar linea a linea
	while (getline(fs,linea)){
		cedulaC = linea.substr(0, linea.find(delimiter));
		linea.erase(0, linea.find(delimiter) + delimiter.length());
		nombre = linea.substr(0, linea.find(delimiter));
		linea.erase(0, linea.find(delimiter) + delimiter.length());
		if (toInt(cedulaC) == cedula) {  //se encontro
			linea = cedulaC + ";" + nombre + ";B"; //reemplazar
		}
		else {
			linea = cedulaC + ";" + nombre;
		}
		fstemp << linea << endl;
	}

	//reemplazar un archivo por otro
	fs.close();
	fstemp.close();
	remove("Clientes.txt");                    // borrar el original
	rename("temp.txt", "Clientes.txt");  // renombrar el temporal

	//siguiendo la logica que usaste en el resto
	cout << "El cliente se ha borrado correctamente" << endl;
}

void purgarCliente(int cedula) {
	string linea, cedulaC, nombre;
	string delimiter = ";";
	ifstream fs("Clientes.txt"); //leer de este archivo
	ofstream fstemp("temp.txt"); //escribir en este archivo

	//modificar linea a linea
	while (getline(fs, linea)) {
		cedulaC = linea.substr(0, linea.find(delimiter));
		linea.erase(0, linea.find(delimiter) + delimiter.length());
		nombre = linea.substr(0, linea.find(delimiter));
		linea.erase(0, linea.find(delimiter) + delimiter.length());
		if (toInt(cedulaC) != cedula) {  //se encontro
			linea = cedulaC + ";" + nombre;
			fstemp << linea << endl;
		}
	}

	//reemplazar un archivo por otro
	fs.close();
	fstemp.close();
	remove("Clientes.txt");                    // borrar el original
	rename("temp.txt", "Clientes.txt");  // renombrar el temporal

	//siguiendo la logica que usaste en el resto
	cout << "El cliente ha sido purgado correctamente" << endl;
}

void menu() {
	int opc,cedula;
	string nombre;
	do {
		cout << "--------------------------------------------" << endl;
		cout << "------------------[[[[Menu Tarea Corta#3]]]]--------------" << endl;
		cout << "[1]Buscar Cliente" << endl;
		cout << "[2]Eliminar Cliente" << endl;
		cout << "[3]Insertar Cliente" << endl;
		cout << "[4]Purgar Cliente" << endl;
		cout << "[5]Salir" << endl;
		cout << "--------------------------------------------" << endl;
		cout << "Ingrese una opcion: " << endl;
		cin >> opc;
		switch (opc) {
		case 1:
			cout << "Escriba la cedula que quiere buscar:" << endl;
			cin >> cedula;
			buscarCliente(cedula);
			break;
		case 2:
			cout << "Escriba la cedula del cliente que desea borrar" << endl;
			cin >> cedula;
			eliminarCliente(cedula);
			break;
		case 3:
			cout << "Escriba la cedula que quiere ingresar:" << endl;
			cin >> cedula;
			cout << "Escriba el nombre que quiere ingresar:" << endl;
			cin >> nombre;
			break;
		case 4:
			cout << "Escriba la cedula que quiere purgar:" << endl;
			cin >> cedula;
			purgarCliente(cedula);
			break;
		default:
			break;
		}
	} while (opc <= 4);

}

int main()
{
	lectura();
	menu();
	Clientes.PreordenI();
	cin.get();
	return 0;
}