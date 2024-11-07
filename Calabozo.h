#pragma once
#include "Cuartos.h"
#include <iostream>

#define CUARTOS 20

template <typename T>
class Calabozo {
public:
    Calabozo() : head(nullptr) {}

    ~Calabozo() {
        Cuarto<T>* current = head;
        while (current != nullptr) {
            Cuarto<T>* next = current->right;
            delete current;
            current = next;
        }
    }

    bool crearCuarto(Monstruo<T>* monstruo) {
        Cuarto<T>* nuevoCuarto = new(std::nothrow) Cuarto<T>(monstruo);
        if (!nuevoCuarto) return false;

        if (head == nullptr) {
            head = nuevoCuarto;
        } else {
            Cuarto<T>* current = head;
            while (current->right != nullptr) {
                current = current->right;
            }
            current->right = nuevoCuarto;
            nuevoCuarto->left = current;
        }
        return true;
    }

    bool imprimeCuartos() {
        Cuarto<T>* current = head;
        int contador = 1;
        while (current) {
            std::cout << "Cuarto numero " << contador << ", monstruo: " << current->getMonstruo()->getNombre() <<" lol "<< current->getMonstruo()->getCr() << std::endl;
            current = current->right;
            contador++;
        }
        return true;
    }

    Cuarto<T>* getCuarto(int numero) {
        Cuarto<T>* current = head;
        int contador = 1;
        while (current) {
            if (contador == numero) {
                return current;
            }
            current = current->right;
            contador++;
        }
        return nullptr;
    }

private:
    Cuarto<T>* head;
};
