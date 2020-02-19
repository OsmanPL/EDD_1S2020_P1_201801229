#ifndef RUTA
#define RUTA
#include <string>
#include <iostream>

using namespace std;

class Ruta {
private:
	string ruta;
	Ruta* siguiente;

public:
	string getRuta() {
		return ruta;
	}
	void setRuta(string cadena) {
		ruta = cadena;
	}
	Ruta* getSiguiente() {
		return siguiente;
	}
	void setSiguiente(Ruta* siguiente1) {
		siguiente = siguiente1;
	}
};

#endif
