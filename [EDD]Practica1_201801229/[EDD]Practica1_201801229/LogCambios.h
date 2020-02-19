
#ifndef LOGCAMBIOS
#define LOGCAMBIOS
#include <iostream>
#include <string>
#include "Cambio.h"

using namespace std;

class LogCambios {
private:
public:
	Cambio* pilaCambio;
	Cambio* pilaRevertido;

	void pushCambio(Cambio* nuevoCambio) {
		nuevoCambio->setEstado(false);
		if (pilaCambio!=NULL)
		{
			nuevoCambio->serSiguiente(pilaCambio);
			pilaCambio = nuevoCambio;
		}
		else {
			pilaCambio = nuevoCambio;
		}
	}
	Cambio* popCambio() {
		if (pilaCambio!=NULL)
		{
			Cambio* aux = pilaCambio;
			pilaCambio = pilaCambio->getSiguiente();
			return aux;
		}
	}

	void pushRevertido(Cambio* nuevoCambio) {
		nuevoCambio->setEstado(true);
		if (pilaRevertido != NULL)
		{
			nuevoCambio->serSiguiente(pilaRevertido);
			pilaRevertido = nuevoCambio;
		}
		else {
			pilaRevertido = nuevoCambio;
		}
	}
	Cambio* popRevertido() {
		if (pilaRevertido!=NULL)
		{
			Cambio* aux = pilaRevertido;
			pilaRevertido = pilaRevertido->getSiguiente();
			return aux;
		}
	}

	Cambio* cambiar() {
		if (pilaRevertido!=NULL) {
			Cambio* aux = popRevertido();
			pushCambio(aux);
			return aux;
		}
	}
	Cambio* revertir() {
		if (pilaCambio != NULL) {
			Cambio* aux = popCambio();
			pushRevertido(aux);
			return aux;
		}
	}

	Cambio* getPilaRevertido() {
		return pilaRevertido;
	}
	Cambio* getPilaCambio() {
		return pilaCambio;
	}

};

#endif
