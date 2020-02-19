#include "pch.h"
#include <iostream>
#include <curses.h>
#include <thread>
#include <chrono>
#include <mutex>
#include "Nodo.h"
#include "Ventana.h"
#include "Lectura.h"
#include "ListaCiruclar.h"

using namespace std;


Nodo* nodo = new Nodo();
ListaCircular* rutas = new ListaCircular();

void Menu() {
	cout << "\nUNIVERSIDAD DE SAN CARLOS DE GUATEMALA";
	cout << "\nFACULTAD DE INGENIERIA";
	cout << "\nESTRUCTURAS DE DATOS";
	cout << "\nPRACTICA 1";
	cout << "\nOSMAN ALEJANDRO PEREZ LOPEZ";
	cout << "\n201801229";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n--------------------MENU EDITOR------------------";
	cout << "\n1. Crear Archivo";
	cout << "\n2. Abrir Archivo";
	cout << "\n3. Archivos Recientes";
	cout << "\n4. Salir";
	cout << "\nSu Opcion: ";
}

void mostrarArchivosRecientes() {
	int opcion;
	cout << "\n---------------------Archivos Recientes ----------------------------------------";
	rutas->mostrar();
	cout << "\nPresione Ctrl+X para generar el reporte \nCualquier otra tecla para regresar al menu";
	char key;
	int ascii;
	while (1) {
		key = getch();
		ascii = key;
		if (ascii == 24) {
			Lectura* lec = new Lectura();
			lec->crearDotListaCircular(rutas);
			cout << "\nReporte generado\n";
			system("pause");
			break;
		}
	}
}

int main() {
	int op;
	do
	{
		Menu();
		cin >> op;
		switch (op)
		{
		case 1:
		{
			initscr();
			Ventana* nuevo = new Ventana();
			nuevo->iniciarVentana(nodo, 0, rutas);
			endwin();
		}break;
		case 2:
		{
			string ruta;
			Lectura* nuevo = new Lectura();
			ruta = nuevo->lectura(nodo);
			initscr();
			Ventana* mostrar = new Ventana();
			mostrar->lectura(ruta, nodo, rutas);
			endwin();
		}break;
		case 3:
		{
			mostrarArchivosRecientes();
		}break;
		case 5:
		{
			nodo->mostrarPrincipio();
		}break;
		}
	} while (op!=4);

	cout << "\nSGracias por usar el editor de texto :p";

	return 0;
}