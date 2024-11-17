
#pragma once
#include "Cuarto.h"
#include <iostream>

#define CUARTOS 20

template <typename T>
class Calabozo {

private:
    //puntero para el primer cuarto de la lista
    Cuarto<T>* head;

public:
    // constructor (lista vacía)
    Calabozo() : head(nullptr) {

    }
    //destructor para recorrer la lista y borrar memoria
    ~Calabozo() {
        Cuarto<T>* temp = head;

        while (temp != nullptr) {
            Cuarto<T>* next = temp->right;
            delete temp;
            temp = next;
        }
    }
    // crear un cuarto (objeto) con puntero de mosntruos
    bool makeCuarto(Monstruos<T>* monstruos) {
        Cuarto<T>* cuartoNuevo = new(std::nothrow) Cuarto<T>(monstruos);
        if (monstruos == nullptr) {
            // verificar que mostruos NO sea nullptr
            std::cout << "Error: Se intentó crear un cuarto con un puntero a Monstruos nulo." << std::endl;
            return false;
        }

        if (!cuartoNuevo) {
            // verificar que se asigne memoria a cuartoNuevo
            std::cout << "Error: No se pudo asignar memoria para un nuevo cuarto." << std::endl;
            return false;
        }

        if(head == nullptr) {
            head = cuartoNuevo;
            // lista vacía asiganndo head, cout usado para verificar el cuarto inicial
            //std::cout << "Cuarto inicial creado con monstruo: " << monstruos->getNombre() << std::endl;
        } else {
            // recorrer la lista hasta el último cuarto
            Cuarto<T>* temp = head;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            temp->right = cuartoNuevo;
            cuartoNuevo->left = temp;
            //std::cout << "Nuevo cuarto añadido con monstruo: " << monstruos->getNombre() << std::endl;
        }
        return true;
    }

    bool mostrarCuartos() {
        //recorrer la lista y mostrar el nombre de cada monstruo
        Cuarto<T>* temp = head;
        int count = 1;
        while (temp) {
            if (temp->getMonstruos() == nullptr) {
                std::cout << "Error: El puntero a Monstruos en el Cuarto #" << count << " es nullptr." << std::endl;
                return false;
            }

            if (temp->getMonstruos()->getNombre().empty()) {
                //comprobar que no esté vacío
                std::cout << "Error: El nombre del Monstruo en el Cuarto #" << count << " es nullptr." << std::endl;
                return false;
            }

            std::cout << "Cuarto #" << count << ", monstruo: " << temp->getMonstruos()->getNombre() << std::endl;
            temp = temp->right;
            count++;
        }
        return true;
    }
    // metodo para acceder a un cuarto
    Cuarto<T>* getCuarto(int num) {
        Cuarto<T>* temp = head;
        int cuenta = 1;
        while (temp) {
            if (cuenta == num) {
                return temp;
            }
            temp = temp->right;
            cuenta++;
        }
        return nullptr;
    }
};