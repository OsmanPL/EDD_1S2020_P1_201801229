#ifndef VENTANA
#define VENTANA
#include <curses.h>
#include <fstream>
#include <string>
#include "Nodo.h"
#include "Caracter.h"
#include "Lectura.h"
#include "ListaCiruclar.h"
#include "LogCambios.h"
#include "Cambio.h"

using namespace std;

class Ventana {
private:
public:
	string ruta;
	Lectura* guardar = new Lectura();
	LogCambios* log = new LogCambios();
	WINDOW *nuevaVentana = newwin(30, 120, 0, 0);
	WINDOW *ventanaEditor = newwin(20, 116, 2, 2);
	WINDOW *ventanaOpciones = newwin(4, 116, 24, 2);

    void iniciarVentana(Nodo* nodo, int r, ListaCircular* rutas) {
        keypad(ventanaEditor, TRUE);
		noecho();
		refresh();
		box(nuevaVentana, 0, 0);
		wrefresh(nuevaVentana);
		box(ventanaOpciones, 0, 0);
		wrefresh(ventanaOpciones);
		wmove(nuevaVentana, 0,0);
		wprintw(ventanaOpciones, "(ctrl+w)Buscar y Reemplazar   (ctrl+s)Guardar   (ctrl+c)Reportes");
		wrefresh(ventanaOpciones);
		wprintw(nuevaVentana, "Editor de Texto");
		wrefresh(nuevaVentana);
		wmove(ventanaEditor, 0, 0);
		wrefresh(ventanaEditor);
        char key;
        int ascii;
		int salir = 0;
        while (salir == 0) {
			nodo->mostrarFinal(ventanaEditor);
			wrefresh(ventanaEditor);
			switch ((ascii=getch()))
			{

			case 3:
			{
				reportes(nodo);
			}break;
			case 8:
			{
				nodo->eliminarUltimo();
			}break;
			case 19:
			{
				if (r==0)
				{

					guardarArchivoNuevo(nodo, rutas);
				}
				else {
					guardarArchivoExistente(nodo, rutas);
				}
				salir = 1;
			}break;
			case 23:
			{
				pasarOpciones(nodo);
			}break;
			case 26:
			{
				Cambio* revertir = log->revertir();
				nodo->buscar(revertir->getBuscar(), revertir->getReemplazar(), ventanaOpciones);
			}break;
			case 25:
			{
				Cambio* revertir = log->cambiar();
				nodo->buscar(revertir->getReemplazar(), revertir->getBuscar(), ventanaOpciones);
			}break;
			default:
			{
				key = ascii;
				nodo->insertarInicio(key);
			}break;
			}
			wclear(ventanaEditor);
            wrefresh(ventanaEditor);
        }
	}
	void pasarOpciones(Nodo* nodo) {

		string buscar = "", reemplazar = "";

		wmove(ventanaOpciones, 1, 1);
		wprintw(ventanaOpciones, "Buscar y Reemplazar: ");
		wmove(ventanaOpciones, 1, 23);
		wrefresh(ventanaOpciones);
		char key;
		int ascii;
		while (1) {
			if ((ascii = getch()) == 59)
			{

				key = ascii;
				wprintw(ventanaOpciones, "%c", key, ascii);
				break;
			}
			else {
				key = ascii;
				buscar += key;
				wprintw(ventanaOpciones, "%c", key, ascii);
			}

			wrefresh(ventanaOpciones);
		}
		wrefresh(ventanaOpciones);
		while (1) {
			if ((ascii = getch()) == 10)
			{
				break;
			}
			else {
				key = ascii;
				reemplazar += key;
				wprintw(ventanaOpciones, "%c", key, ascii);
			}

			wrefresh(ventanaOpciones);
		}
		Cambio* nuevoCambio = new Cambio();
		nuevoCambio->setBuscar(buscar);
		nuevoCambio->setReemplazar(reemplazar);
		log->pushCambio(nuevoCambio);
		nodo->buscar(reemplazar, buscar, ventanaOpciones);
		wmove(nuevaVentana, 0, 0);
	}

	void lectura(string abrir, Nodo* nodo, ListaCircular* rutas) {
		ruta = abrir;
		iniciarVentana(nodo, 1, rutas);
	}

	void guardarArchivoNuevo(Nodo* nodo, ListaCircular* rutas) {

		string nombre;
		ruta = "";
		wmove(ventanaOpciones, 1, 1);
		wprintw(ventanaOpciones, "Nombre del Archivo: ");
		wmove(ventanaOpciones, 1, 20);
		wrefresh(ventanaOpciones);
		char key;
		int ascii;
		while (1) {
			if ((ascii = getch()) == 10)
			{

				break;
			}
			else {
				key = ascii;
				nombre += key;
				wprintw(ventanaOpciones, "%c", key, ascii);
			}
			wrefresh(ventanaOpciones);
		}

		wmove(ventanaOpciones, 1, 1);
		wprintw(ventanaOpciones, "Ruta donde Guardara el archivo: ");
		wmove(ventanaOpciones, 1, 33);
		wrefresh(ventanaOpciones);

		while (1) {
			if ((ascii = getch()) == 10)
			{

				break;
			}
			else {
				key = ascii;
				ruta += key;
				wprintw(ventanaOpciones, "%c", key, ascii);
			}

			wrefresh(ventanaOpciones);
		}
		ruta += nombre;
		ruta += ".txt";

		guardar->escribir(ruta, nodo, rutas);

		wclear(ventanaOpciones);
		wrefresh(ventanaOpciones);
		box(ventanaOpciones, 0, 0);
		wrefresh(ventanaOpciones);
		wmove(nuevaVentana, 0, 0);
		wprintw(ventanaOpciones, "(ctrl+w)Buscar y Reemplazar   (ctrl+s)Guardar   (ctrl+c)Reportes");
		wrefresh(ventanaOpciones);
	}

	void guardarArchivoExistente (Nodo* nodo, ListaCircular* rutas) {

		guardar->escribir(ruta, nodo, rutas);

		wclear(ventanaOpciones);
		wrefresh(ventanaOpciones);
		box(ventanaOpciones, 0, 0);
		wrefresh(ventanaOpciones);
		wmove(nuevaVentana, 0, 0);
		wprintw(ventanaOpciones, "(ctrl+w)Buscar y Reemplazar   (ctrl+s)Guardar   (ctrl+c)Reportes");
		wrefresh(ventanaOpciones);
	}

	void reportes(Nodo* nodo) {
		wmove(ventanaOpciones, 1, 1);
		wprintw(ventanaOpciones, "Reportes: 1)Lista     2)Palabras Buscadas     3)Palabras Ordenadas");
		wmove(ventanaOpciones, 1, 20);
		wrefresh(ventanaOpciones);
		int ascii;
		switch ((ascii = getch()))
		{

		case 49:
		{
			guardar->crearDot(nodo);
		}break;
		case 50:
		{
			guardar->crearDotBusqueda(log);
			guardar->crearDotRevertido(log);
		}break;
		}

		wclear(ventanaOpciones);
		wrefresh(ventanaOpciones);
		box(ventanaOpciones, 0, 0);
		wrefresh(ventanaOpciones);
		wmove(nuevaVentana, 0, 0);
		wprintw(ventanaOpciones, "(ctrl+w)Buscar y Reemplazar   (ctrl+s)Guardar   (ctrl+c)Reportes");
		wrefresh(ventanaOpciones);
	}

};

#endif

