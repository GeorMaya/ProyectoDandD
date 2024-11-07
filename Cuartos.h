#pragma once
#include "Monstruo.h"

template <typename T>
class Cuarto {
public:
    Cuarto(Monstruo<T>* monstruo) : monstruo(monstruo), right(nullptr), left(nullptr) {}

    ~Cuarto() {}

    Monstruo<T>* getMonstruo() {
        return monstruo;
    }

    Cuarto* right;
    Cuarto* left;

private:
    Monstruo<T>* monstruo;
};
