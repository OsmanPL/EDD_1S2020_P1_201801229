#ifndef LECTURA
#define LECTURA
#include <curses.h>
#include <string>
#include <fstream>
#include "Nodo.h"
#include "Ventana.h"
#include "Caracter.h"
#include "ListaCiruclar.h"
#include "LogCambios.h"
#include "Cambio.h"
#include "Ruta.h"

using namespace std;
class Lectura {
private:
public:

	string ruta;
	string lectura(Nodo* nodo) {
		ifstream archivo;
		char ch;
		cout << "\nRuta del Archivo: ";
		cin >> ruta;
		archivo.open(ruta, ios::in);
		if (archivo.fail()) {
			cout << "Error: no se pudo abrir archivo";
		}
		else {
			while (!archivo.eof()) {
				archivo.get(ch);
				nodo->insertarInicio(ch);
			}
			archivo.close();

			return ruta;
		}

	}

	void escribir(string ruta, Nodo* nodo, ListaCircular* rutas) {
		ofstream archivo;
		archivo.open(ruta, ios::out);

		if (archivo.fail())
		{
			cout << "Error: no se pudo abrir el archivo";
			exit(1);
		}
		Caracter* recorrer = new Caracter();
		recorrer = nodo->devolverUltimo();
		while (recorrer != NULL)
		{
			archivo << recorrer->getCaracter();
			recorrer = recorrer->getAnterior();
		}
		nodo->vaciarLista();
		rutas->agregarLista(ruta);
		archivo.close();
	}

	void crearDot(Nodo* nodo) {
		Caracter* recorrer = new Caracter();
		recorrer = nodo->devolverUltimo();
		string grafica;
		int i1 = 1;
		int j1 = 2;

		grafica += "digraph lista{ \n";
		while (recorrer != NULL)
		{
			string i = to_string(i1);
			string j = to_string(j1);

			if (recorrer->getCaracter() == ' ')
			{
				grafica += "Espacio" + i;
			}
			else if (recorrer->getCaracter() == '\n')
			{
				grafica += "Salto" + i;
			}
			else {
				grafica += recorrer->getCaracter() + i;
			}
			grafica += " -> ";
			if (recorrer->getAnterior() != NULL)
			{
				if (recorrer->getAnterior()->getCaracter() == ' ')
				{
					grafica += "Espacio" + j;
				}
				else if (recorrer->getAnterior()->getCaracter() == '\n')
				{
					grafica += "Salto" + j;
				}
				else {
					grafica += recorrer->getAnterior()->getCaracter() + j;
				}
			}
			else {
				grafica += "fin";
			}
			grafica += " ;\n";

			recorrer = recorrer->getAnterior();
			if (recorrer != NULL)
			{
				if (recorrer->getCaracter() == ' ')
				{
					grafica += "Espacio" + j;
				}
				else if (recorrer->getCaracter() == '\n')
				{
					grafica += "Salto" + j;
				}
				else {
					grafica += recorrer->getCaracter() + j;
				}
				grafica += " -> ";
				if (recorrer->getSiguiente() != NULL)
				{
					if (recorrer->getSiguiente()->getCaracter() == ' ')
					{
						grafica += "Espacio" + i;
					}
					else if (recorrer->getSiguiente()->getCaracter() == '\n')
					{
						grafica += "Salto" + i;
					}
					else {
						grafica += recorrer->getSiguiente()->getCaracter() + i;
					}
				}
				else {
					grafica += "inicio";
				}
				grafica += " ;";
			}


			i1++;
			j1++;
			grafica += '\n';
		}
		grafica += "}";

		ofstream archivo;
		archivo.open("listacaracteres.txt", ios::out);

		if (archivo.fail())
		{
			cout << "Error: no se pudo abrir el archivo";
			exit(1);
		}
		archivo << grafica;

		archivo.close();

		system("dot -Tjpg listacaracteres.txt -o listacaracteres.jpg");
	}

	void crearDotBusqueda(LogCambios* log) {
		Cambio* cambios = log->getPilaCambio();
		string grafica = "";
		int i = 0;
		string j = to_string(i);
		grafica += "digraph busqueda { \n";
		grafica += "node [shape = record, height=.1,fillcolor=\u0022chartreuse\u0022]";

		while (cambios != NULL)
		{
			grafica += "node" + j + " [label= \u0022Buscada: " + cambios->getBuscar() + " \u005C" + "n ";
			grafica += " Reemplazo: " + cambios->getReemplazar() + " \u005C" + "n ";
			grafica += " Estado: No Revertido \u005Cn ";
			grafica += " Palabra: NULL \u005Cn Posicion: NULL \u0022]; \n ";
			cambios = cambios->getSiguiente();
			i++;
		}

		int r = 1;
		i = 0;
		j = to_string(i);
		string l = to_string(r);
		cambios = log->getPilaCambio();
		while (cambios != NULL)
		{
			grafica += "node" + j + " -> node" + l + " ; \n";
			cambios = cambios->getSiguiente();
			i++;
		}
		grafica += "}";

		ofstream archivo;
		archivo.open("listabuscarcambios.txt", ios::out);

		if (archivo.fail())
		{
			cout << "Error: no se pudo abrir el archivo";
			exit(1);
		}
		archivo << grafica;

		archivo.close();

		system("dot -Tjpg listabuscarcambios.txt -o listabuscarcambios.jpg");
	}

	void crearDotRevertido(LogCambios* log) {
		Cambio* cambios = log->getPilaRevertido();
		string grafica = "";
		int i = 0;
		string j = to_string(i);
		grafica += "digraph revertido { \n";
		grafica += "node [shape = record, height=.1, fillcolor=\u0022crimson\u0022]";

		while (cambios != NULL)
		{
			j = to_string(i);
			grafica += "node" + j + " [label= \u0022Buscada: " + cambios->getBuscar() + " \u005C" + "n ";
			grafica += " Reemplazo: " + cambios->getReemplazar() + " \u005C" + "n ";
			grafica += " Estado: Revertido \u005Cn ";
			grafica += " Palabra: NULL \u005Cn Posicion: NULL \u0022]; \n ";
			cambios = cambios->getSiguiente();
			i++;
		}

		int r = 1;
		i = 0;
		j = to_string(i);
		string l = to_string(r);
		cambios = log->getPilaRevertido();
		while (cambios != NULL)
		{
			j = to_string(i);
			l = to_string(r);
			grafica += "node" + j + " -> node" + l + " ; \n";
			cambios = cambios->getSiguiente();
			i++;
			r++;
		}
		grafica += "}";

		ofstream archivo;
		archivo.open("listarevertidos.txt", ios::out);

		if (archivo.fail())
		{
			cout << "Error: no se pudo abrir el archivo";
			exit(1);
		}
		archivo << grafica;

		archivo.close();

		system("dot -Tjpg listarevertidos.txt -o listarevertidos.jpg");
	}
	void crearDotListaCircular(ListaCircular* lc) {
		Ruta* recorrer = lc->retornarInicio();
		Ruta* fin = lc->retornarInicio();
		string grafica;
		int i = 0;
		string j = to_string(i);
		int ultimo;
		grafica += "digraph listaCircular{ \n";
		grafica += "node [shape = record, height=.1, fillcolor=\u0022aquamarine\u0022];\n";

		do {
			j = to_string(i);
			grafica += "node" + j + " [label= \u0022Ruta: "+ recorrer->getRuta() + "\u0022];\n";
			recorrer = recorrer->getSiguiente();
			i++;
		} while (recorrer!=fin);
		ultimo = i - 1;
		recorrer = lc->retornarInicio();
		i = 0;
		j = to_string(i);
		int r = 1;
		string l;
		do {
			l = to_string(r);
			j = to_string(i);
			if (i == ultimo) {

				grafica += "node" + j + " -> node0 ;\n";
			}
			else {
				grafica += "node" + j + " -> node" + l + " ;\n";
			}
			recorrer = recorrer->getSiguiente();
			i++;
			r++;
		} while (recorrer != fin);
		grafica += "}";

		ofstream archivo;
		archivo.open("listacircular.txt", ios::out);

		if (archivo.fail())
		{
			cout << "Error: no se pudo abrir el archivo";
			exit(1);
		}
		archivo << grafica;

		archivo.close();

		system("dot -Tjpg listacircular.txt -o listacircular.jpg");
	}

};
#endif
