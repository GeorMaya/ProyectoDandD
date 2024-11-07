#include <iostream>
#include <ctime>
#include "Calabozo.h"
#include "Catalogo.h"
#include "Jugador.h"

#define NUM_CUARTOS 20

using namespace std;

int main() {
    srand(time(0));
    using U = string;

    Catalogo<U> miCatalogo;
    Calabozo<U> miCalabozo;
    Jugador<U> miJugador;

    if(!miCatalogo.loadCSV()) {
        cout << "No se pudo crear el catalogo" << endl;
        return 0;
    }

    cout << "Creando Dungeon" << endl;

    for(int c = 0; c < NUM_CUARTOS; c ++) {
        Monstruo<U>* pMonster = miCatalogo.getRandomMonstruo();

        if(!pMonster) {
            cout << "No se obtuvo un monstruo" << endl;
            return 0;
        }

        if (!miCalabozo.crearCuarto(pMonster)) {
            cout << "No se inserto el cuarto" << endl;
            return 0;
        }
    }

    miCalabozo.imprimeCuartos();

    return 0;
}
