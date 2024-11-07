#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Monstruo.h"


#define CSV "monsters.csv"
#define CSV "/Users/jorge/CLionProjects/Arboles/Nose/monsters.csv"

template <typename T>
class Catalogo {
public:
    Catalogo() : root(nullptr) {}

    ~Catalogo() {
        destruirArbol(root);
    }

    bool agregarMonstruo(Monstruo<T>& nuevoMonstruo) {
        Monstruo<T>* nuevoPtr = new(std::nothrow) Monstruo<T>(nuevoMonstruo);
        if (nuevoPtr == nullptr) return false;

        if (root == nullptr) {
            root = nuevoPtr;
            return true;
        }

        Monstruo<T>* current = root;
        Monstruo<T>* padre = nullptr;

        while (current != nullptr) {
            padre = current;
            if(nuevoPtr->getCr() < current->getCr()) current = current->left;
            else current = current->right;
        }

        if(nuevoPtr->getCr() < padre->getCr()) padre->left = nuevoPtr;
        else padre->right = nuevoPtr;

        return true;
    }

    bool loadCSV() {
    std::ifstream file(CSV);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo CSV: " << CSV << std::endl;
        return false;
    }

    std::string line;
    getline(file, line); // Salta la primera línea (cabecera)

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name, type, size, align;
        double cr, ac, hp;  // Ahora estos son siempre `double`

        // Lee cada campo separado por comas
        getline(ss, name, ',');     // Nombre del monstruo
        getline(ss, cr, ',');      // CR (Challenge Rating)
        getline(ss, type, ',');     // Tipo
        getline(ss, size, ',');     // Tamaño
        getline(ss, ac, ',');      // AC (Armor Class)
        getline(ss, hp, ',');      // HP (Hit Points)
        getline(ss, align);    // Alineación

        // Crea el objeto Monstruo con los valores leídos
        Monstruo<T> monstruo(name, cr, type, size, ac, hp, align);

        // Agrega el monstruo al árbol
        agregarMonstruo(monstruo);
    }

    file.close();
    return true;
}



    Monstruo<T>* getRandomMonstruo() {
        int numeroRandom = rand() % 762 + 1;
        return buscarMonstruo(numeroRandom);
    }

    Monstruo<T>* buscarMonstruo(int numero) {
        int indice = 0;
        return buscarIndex(root, indice, numero);
    }

private:
    Monstruo<T>* root;

    bool destruirArbol(Monstruo<T>* nodo) {
        if(nodo != nullptr) {
            destruirArbol(nodo->left);
            destruirArbol(nodo->right);
            delete nodo;
        }
        return true;
    }

    Monstruo<T>* buscarIndex(Monstruo<T>* nodo, int& indice, int numero) {
        if(nodo == nullptr) return nullptr;

        Monstruo<T>* found = buscarIndex(nodo->left, indice, numero);
        if(found != nullptr) return found;

        indice++;
        if(indice == numero) return nodo;

        return buscarIndex(nodo->right, indice, numero);
    }
};
