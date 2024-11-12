#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Monstruo.h"

#define CSV "/Users/jorge/CLionProjects/Arboles/Nose/monsters.csv"
#define TABLE_SIZE 100  // Tamaño de la tabla hash

template <typename T>
class Catalogo {
public:
    Catalogo() {
        // Inicializa la tabla con punteros nulos
        for (int i = 0; i < TABLE_SIZE; i++) {
            hashTable[i] = nullptr;
        }
    }

    ~Catalogo() {
        // Elimina todos los elementos en la tabla hash
        for (int i = 0; i < TABLE_SIZE; i++) {
            Nodo* current = hashTable[i];
            while (current != nullptr) {
                Nodo* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    bool agregarMonstruo(Monstruo<T>& nuevoMonstruo) {
        int index = hashFunction(nuevoMonstruo.getCr());

        // Verificación de índice válido
        if (index < 0 || index >= TABLE_SIZE) {
            std::cerr << "Índice fuera de rango: " << index << std::endl;
            return false;
        } else {
            std::cout << "Índice calculado para " << nuevoMonstruo.getNombre() << " es " << index << std::endl;
        }

        // Crea un nuevo nodo para almacenar el monstruo
        Nodo* newNode = new Nodo;
        newNode->monstruo = nuevoMonstruo;
        newNode->next = nullptr;

        // Inserta en la tabla hash
        if (hashTable[index] == nullptr) {
            hashTable[index] = newNode;
        } else {
            Nodo* current = hashTable[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
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
            double cr, ac, hp;

            // Lee cada campo separado por comas
            getline(ss, name, ',');
            ss >> cr; ss.ignore();
            getline(ss, type, ',');
            getline(ss, size, ',');
            ss >> ac; ss.ignore();
            ss >> hp; ss.ignore();
            getline(ss, align, ',');

            // Crea el objeto Monstruo con los valores leídos
            Monstruo<T> monstruo(name, cr, type, size, ac, hp, align);

            // Agrega el monstruo a la tabla hash
            agregarMonstruo(monstruo);
        }

        file.close();
        return true;
    }

    Monstruo<T>* getRandomMonstruo() {
        int randomIndex = rand() % TABLE_SIZE;
        Nodo* current = hashTable[randomIndex];

        if (current == nullptr) return nullptr;

        // Navegar hasta un elemento aleatorio en la lista enlazada
        int count = 0;
        while (current != nullptr) {
            if (rand() % (++count) == 0) break;
            current = current->next;
        }
        return current ? &current->monstruo : nullptr;
    }

    Monstruo<T>* buscarMonstruo(int cr) {
        int index = hashFunction(cr);
        Nodo* current = hashTable[index];

        // Buscar en la lista enlazada en el índice correspondiente
        while (current != nullptr) {
            if (current->monstruo.getCr() == cr) {
                return &current->monstruo;
            }
            current = current->next;
        }
        return nullptr;
    }

private:
    struct Nodo {
        Monstruo<T> monstruo;
        Nodo* next;
    };

    Nodo* hashTable[TABLE_SIZE];  // Tabla hash con manejo de colisiones por encadenamiento

    int hashFunction(int cr) {
        return cr % TABLE_SIZE;  // Función hash simple
    }
};
