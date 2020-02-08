#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void Menu(){
	cout << "\n------Menu-----";
	cout << "\n1. Crear Archivo";
	cout << "\n2. Abrir Archivo";
	cout << "\n3. Salir";
	cout << "\nSu opcion es: ";
}

int main(){
	int opcion;
	
	do{
		Menu();
		cin >> opcion;
	}while(opcion != 3);
	
	return 0;
}
