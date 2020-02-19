#ifndef NODO
#define NODO
#include "Caracter.h"
#include <string.h>
#include <curses.h>

using namespace std;

class Nodo {
private:
	Caracter* caracter;
public:
	Caracter* primero;
	Caracter* ultimo;
	Caracter* auxInicio;
	Caracter* auxfinal;

	bool listaVacia() {
		if (primero == NULL || ultimo == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	void insertarInicio(char c) {
		Caracter* nuevoCaracter = new Caracter();
		nuevoCaracter->setCaracter(c);
		if (listaVacia()) {
			primero = nuevoCaracter;
			ultimo = nuevoCaracter;
		}
		else {
			primero->setAnterior(nuevoCaracter);
			nuevoCaracter->setSiguiente(primero);
			primero = nuevoCaracter;
		}
	}

	void mostrarPrincipio() {
		Caracter* aux = auxInicio;
		cout << "\n";
		while (aux != NULL) {
			cout << "->" << aux->getCaracter();
			aux = aux->getSiguiente();
		}
		cout << "\n";
	}

	void mostrarFinal(WINDOW* ventana) {
		Caracter* aux = ultimo;
		while (aux != NULL) {
			wprintw(ventana,"%c" ,aux->getCaracter());
			aux = aux->getAnterior();
		}
		wrefresh(ventana);
	}

	void eliminarUltimo() {
		primero = primero->getSiguiente();
		primero->setAnterior(NULL);
	}

	Caracter* buscarString(string cadena, int cantidad) {
		Caracter* aux = ultimo;
		Caracter* primercaracter;
		Caracter* ultimocaracter;
		int i = 0;
		while (aux != NULL) {
			if (i < cantidad) {
				if (cadena[i] == aux->getCaracter()) {
					if (i == 0) {
						primercaracter = aux;
					}
					if (i == cantidad - 1) {
						ultimocaracter = aux;
					}
					i++;
				}
				else {
					i = 0;
					primercaracter = NULL;
					ultimocaracter = NULL;
				}
			}
			aux = aux->getAnterior();
		}
		if (primercaracter != NULL && ultimocaracter != NULL) {
			return primercaracter;
		}
		else {
			return NULL;
		}
	}

	Caracter* devolverUltimo() {
		return ultimo;
	}

	void vaciarLista() {
		primero = NULL;
		ultimo = NULL;
	}

	void buscar(string reemplazo, string busqueda, WINDOW* ventanaOpciones) {
		string texto;
		Caracter* aux = ultimo;
		while (aux!=NULL)
		{
			texto += aux->getCaracter();
			aux = aux->getAnterior();
		}
		reemplazar(texto, busqueda, reemplazo, ventanaOpciones);
	}
	void reemplazar(string texto, string busqueda, string reemplazo, WINDOW* ventanaOpciones) {
		int pos = texto.find(busqueda);
		int c = 0;
		while (pos != -1) {
			texto.replace(pos, busqueda.size(), reemplazo);
			pos = texto.find(busqueda, pos + reemplazo.size());
			c++;
		}
		primero = NULL;
		ultimo = NULL;
		int cantidad = texto.length();
		for (int i = 0; i < cantidad; i++)
		{
			insertarInicio(texto[i]);
		}
		wclear(ventanaOpciones);
		wrefresh(ventanaOpciones);
		box(ventanaOpciones, 0, 0);
		wrefresh(ventanaOpciones);
		wprintw(ventanaOpciones, "(ctrl+w)Buscar y Reemplazar   (ctrl+s)Guardar   (ctrl+c)Reportes");
		wmove(ventanaOpciones, 1, 1);
		wprintw(ventanaOpciones, "%i Palabras Afectadas", c);
		wrefresh(ventanaOpciones);
	}

	
};
#endif