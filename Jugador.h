#pragma once
#include "Calabozo.h"

template <typename T>
class Jugador {
public:
    Jugador(T raza = T(), T name = T(), T hp = T(), T mp = T())
        : raza(raza), name(name), hp(hp), mp(mp), head(nullptr), tail(nullptr) {}

    ~Jugador() {
        Cuarto<T>* current = head;
        while (current != nullptr) {
            Cuarto<T>* next = current->right;
            if (current->getMonstruo()) delete current->getMonstruo();
            delete current;
            current = next;
        }
    }

    bool agregarCuarto(Cuarto<T>* cuarto) {
        if (!cuarto) return false;

        if (head == nullptr) {
            head = cuarto;
            tail = cuarto;
        } else {
            tail->right = cuarto;
            cuarto->left = tail;
            tail = cuarto;
        }
        return true;
    }

private:
    T raza, name, hp, mp;

    Cuarto<T>* head;
    Cuarto<T>* tail;
};
