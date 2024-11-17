
#pragma once
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include "Monstruo.h"

#define CSV "monster.csv"
#define CSV "/Users/jorge/CLionProjects/Arboles/Nose/monsters.csv" //ruta personal en mi compu

template <typename T>
class Catalogo {
private:
    Monstruos<T>* root;
    //recorrer arbol y liberar memoria
    bool destruirArbol(Monstruos<T>* nodo) {
        if(nodo != nullptr) {
            destruirArbol(nodo->left);
            destruirArbol(nodo->right);
            delete nodo;
        }
        return true;
    }
    // metodo para buscar un nodo específico en el árbol
    Monstruos<T>* buscarIndex(Monstruos<T>* nodo, int& indice, int numero) {
        if(nodo == nullptr) return nullptr;
        //buscar la rama izquierda
        Monstruos<T>* found = buscarIndex(nodo->left, indice, numero);
        if(found != nullptr) return found;

        indice++; // regresa el nodo cuando coincide con el nodo que se busca
        if(indice == numero) return nodo;
        //recorrer rama derecha
        return buscarIndex(nodo->right, indice, numero);
    }
public:
    Catalogo() : root(nullptr) {}

    ~Catalogo() {
        destruirArbol(root);
    }

    bool addMontruos(Monstruos<T>& nuevoMonstruo) {
        //puntero a nuevo objeto mosntruo
        Monstruos<T>* otroPtr = new(std::nothrow) Monstruos<T>(nuevoMonstruo);
        if(otroPtr == nullptr)
            return false;
        // true cuando se añade un monstruo
        if (root == nullptr) {
            root = otroPtr;
            return true;
        }
        // recorrer el arbol
        Monstruos<T>* temp = root;
        Monstruos<T>* padre = nullptr;
        // encuentra la posición para inertar puntero otroPtr
        while (temp != nullptr) {
            padre = temp;
            //asigna otroPtr al hijo izq o der
            if(otroPtr->getCr() < temp->getCr()) temp = temp->left;
            else {
                temp = temp->right;
            }
        }

        if(otroPtr->getCr() < padre->getCr()) padre->left = otroPtr;
        else {
            padre->right = otroPtr;
        }
        return true;
    }

    bool cargarCSV() {
        std::ifstream file(CSV);
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo CSV: " << CSV << std::endl;
            return false;
        }

        std::string line;
        getline(file, line);
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string name, type, size, align;
            double cr, ac, hp;

            // Lee cada campo separado por comas
            getline(ss, name, ',');     // Nombre del monstruo
            ss >> cr; ss.ignore();      // CR (Challenge Rating)
            getline(ss, type, ',');     // Tipo
            getline(ss, size, ',');     // Tamaño
            ss >> ac; ss.ignore();      // AC (Armor Class)
            ss >> hp; ss.ignore();      // HP (Hit Points)
            getline(ss, align, ',');    // Alineación

            // Crea el objeto Monstruo con los valores leídos
            Monstruos<T> monstruos(name, cr, type, size, ac, hp, align);

            // Agrega el monstruo al árbol
            addMontruos(monstruos);
        }
        file.close();
        return true;
    }

    Monstruos<T>* getRandomMonstruo() {
        int randNum = rand() % 762 + 1;
        return searchMonstruo(randNum);
    }

    Monstruos<T>* searchMonstruo(int num) {
        int indice = 0;
        return buscarIndex(root, indice, num);
    }


};