#ifndef LISTACIRCULAR
#define LISTACIRCULAR
#include "Ruta.h"
#include <string.h>
#include <curses.h>

class ListaCircular {
private:
public:
	Ruta* inicioLista;
	Ruta* finalLista;
	bool listaVacia() {
		if (inicioLista == NULL || finalLista == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	Ruta* retornarInicio() {
		return inicioLista;
	}

	void agregarLista(string nuevaruta) {
		Ruta* nueva = new Ruta();
		nueva->setRuta(nuevaruta);
		if (listaVacia())
		{
			nueva->setSiguiente(nueva);
			inicioLista = nueva;
			finalLista = nueva;
		}
		else {
			nueva->setSiguiente(inicioLista);
			finalLista->setSiguiente(nueva);
			inicioLista = nueva;
		}
	}

	void mostrar() {
		Ruta* aux = inicioLista;
		int i = 1;
		if (aux!=NULL)
		{

			do
			{
				cout << "\n" << i << ". " << aux->getRuta();
				aux = aux->getSiguiente();
			} while (aux != inicioLista);
		}
	}
};

#endif
