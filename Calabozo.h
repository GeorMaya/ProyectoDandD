
#pragma once
#include "Monstruo.h"
#include <iostream>

#define CUARTOS 20

template <typename T>

class Cuarto {
private:
    //puntero a objeto monstruos
    Monstruos<T>* monstruos;

public:
    //constructor que recibe punteros como arg
    Cuarto(Monstruos<T>* monstruos) : monstruos(monstruos), right(nullptr), left(nullptr) {}

    ~Cuarto() {}

    //devuelve el puntero de mosntruos
    Monstruos<T>* getMonstruos() {
        return monstruos;
    }

    //punteros para cuarto siguiente y anterior
    Cuarto* right;
    Cuarto* left;
};

// Nodo de la lista doblemente enlazada
template <typename T>
class Nodo {
public:
    Cuarto<T>* cuarto;       // Cuarto contenido en este nodo
    Nodo* siguiente;         // Puntero al siguiente nodo
    Nodo* anterior;          // Puntero al nodo anterior

    Nodo(Cuarto<T>* cuarto) : cuarto(cuarto), siguiente(nullptr), anterior(nullptr) {}
};

// Clase que implementa una lista doblemente enlazada
template <typename T>
class ListaLigada {
private:
    Nodo<T>* head;  // Puntero al primer nodo de la lista
    Nodo<T>* tail;  // Puntero al último nodo de la lista

public:
    ListaLigada() : head(nullptr), tail(nullptr) {}

    ~ListaLigada() {
        Nodo<T>* actual = head;
        while (actual) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp->cuarto;  // Liberar memoria del cuarto
            delete temp;          // Liberar memoria del nodo
        }
    }

    // Agregar un nuevo cuarto al final de la lista
    void agregarCuarto(Cuarto<T>* cuarto) {
        Nodo<T>* nuevoNodo = new Nodo<T>(cuarto);
        if (!head) {
            head = tail = nuevoNodo;  // La lista estaba vacía
        } else {
            tail->siguiente = nuevoNodo;
            nuevoNodo->anterior = tail;
            tail = nuevoNodo;
        }
    }

    // Mostrar la lista de cuartos
    void mostrarCuartos() {
        Nodo<T>* actual = head;
        int count = 1;
        while (actual) {
            Cuarto<T>* cuarto = actual->cuarto;
            if (cuarto && cuarto->getMonstruos() && !cuarto->getMonstruos()->getNombre().empty()) {
                std::cout << "Cuarto #" << count << ", monstruo: " << cuarto->getMonstruos()->getNombre() << std::endl;
            } else {
                std::cout << "Error en el Cuarto #" << count << ": información incompleta." << std::endl;
            }
            actual = actual->siguiente;
            count++;
        }
    }

    // Obtener un cuarto por índice
    Cuarto<T>* obtenerCuarto(int num) {
        Nodo<T>* actual = head;
        int cuenta = 1;
        while (actual) {
            if (cuenta == num) {
                return actual->cuarto;
            }
            actual = actual->siguiente;
            cuenta++;
        }
        return nullptr;  // Índice fuera de rango
    }
};

// Clase Calabozo que contiene una lista ligada
template <typename T>
class Calabozo {
private:
    ListaLigada<T> listaCuartos;  // Lista de cuartos

public:
    Calabozo() = default;

    ~Calabozo() = default;

    // Crear un cuarto y agregarlo a la lista
    bool makeCuarto(Monstruos<T>* monstruos) {
        if (!monstruos) {
            std::cerr << "Error: Monstruos no puede ser nullptr." << std::endl;
            return false;
        }

        Cuarto<T>* nuevoCuarto = new Cuarto<T>(monstruos);
        listaCuartos.agregarCuarto(nuevoCuarto);
        return true;
    }

    // Mostrar todos los cuartos
    void mostrarCuartos() {
        listaCuartos.mostrarCuartos();
    }

    // Obtener un cuarto por índice
    Cuarto<T>* getCuarto(int num) {
        return listaCuartos.obtenerCuarto(num);
    }
};
