#include <conio.h>
#include <iostream>

using namespace std;

class Editor {
private:
public:

    void editar() {
        char key;
        int ascii;
        cout << "presione una tecla \nPrecione ESC para salir \n" << endl;
        while (1) {
            key = getch();
            ascii = key;
            if (ascii == 27)break;
            cout << "Presiono: " << key << " codigo ascii: " << ascii << "\n" << endl;
        }
    }
    
};