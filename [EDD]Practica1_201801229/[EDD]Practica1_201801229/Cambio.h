#ifndef CAMBIO
#define CAMBIO
#include <iostream>
#include <string>

using namespace std;

class Cambio {
private:
	string buscar;
	string reemplazar;
	bool estado;
	string palabra;
	int posicion;
	Cambio* siguiente;
public:

	void setBuscar(string buscar1) {
		buscar = buscar1;
	}

	void setReemplazar(string reemplazar1) {
		reemplazar = reemplazar1;
	}

	void setEstado(bool estado1) {
		estado = estado1;
	}

	void setPalabra(string palabra1) {
		palabra = palabra1;
	}

	void setPosicion(int posicion1) {
		posicion = posicion1;
	}

	void serSiguiente(Cambio* siguiente1) {
		siguiente = siguiente1;
	}

	string getBuscar() {
		return buscar;
	}

	string getReemplazar() {
		return reemplazar;
	}

	bool getEstado() {
		return estado;
	}

	string getPalabra() {
		return palabra;
	}

	int getPosicion() {
		return posicion;
	}

	Cambio* getSiguiente() {
		return siguiente;
	}

};

#endif

