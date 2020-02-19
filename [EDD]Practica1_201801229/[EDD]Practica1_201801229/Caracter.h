#ifndef CARACTER
#define CARACTER
#include <curses.h>

using namespace std;

class Caracter {
private:
	char caracter;
	Caracter* siguiente;
	Caracter* anterior;

public:
	char getCaracter() {
		return caracter;
	}
	void setCaracter(char c) {
		caracter = c;
	}
	Caracter* getSiguiente() {
		return siguiente;
	}
	void setSiguiente(Caracter* siguiente1) {
		siguiente = siguiente1;
	}
	Caracter* getAnterior() {
		return anterior;
	}
	void setAnterior(Caracter* anterior1) {
		anterior = anterior1;
	}
};
#endif
