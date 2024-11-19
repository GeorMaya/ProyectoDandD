#include <iostream>
#include <ctime>
#include "Jugador.h"
#include "Calabozo.h"
#include "Catalogo.h"
#define NUM_CUARTOS 20

using namespace std;


int main() {
    srand(time(0));
    using J = string;

    Catalogo<J> miCatalogo;  //al usar templates y typename, le indico que es string
    Calabozo<J> miCalabozo;
    Jugador<J> miJugador;

    if(!miCatalogo.cargarCSV()) {
        cout << "Catalogo no creado" << endl;
        return 0;  //mensaje de error por si no se crea el catalogo
    }

    cout << "Creando Calabozo" << endl;  //cout para saber que el calabozo se creó

    for(int i = 0; i < NUM_CUARTOS; i++) {
        Monstruos<J>* pMounstruo = miCatalogo.getRandomMonstruo();

        if(!pMounstruo) {
            cout << "No hay monstruos" << endl;
            return 0;         //control para revisar monstruos creados
        }

        if (!miCalabozo.makeCuarto(pMounstruo)) {
            cout << "No se creó el cuarto" << endl;
            return 0; //control para revisar cuartos creados
        }
    }

    miCalabozo.mostrarCuartos();
    return 0;
}
