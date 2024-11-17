
#pragma once
#include "Monstruo.h"

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