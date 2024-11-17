
#pragma once
#include <string>

template <typename T>
class Monstruos {
public:
    Monstruos() : left(nullptr), right(nullptr), cr(0), ac(0), hp(0) {} //inicializar atributos (nums) y punteros

    // inicializo un objeto con valores específicos
    Monstruos(T nombre, double cr, T tamano, T tipo, double ac, double hp, T align)
        : nombre(nombre), cr(cr), tipo(tipo), tamano(tamano), ac(ac), hp(hp), align(align), left(nullptr), right(nullptr) {}

    //destructor
    ~Monstruos() {}

    //métodos para devolver cada atributo de Monstruos
    T getNombre() {
        return nombre;
    }
    T getTipo() {
        return tipo;
    }
    T getTamano() {
        return tamano;
    }
    T getAlign() {
        return align;
    }
    double getCr() {
        return cr;
    }
    double getAc() {
        return ac;
    }
    double getHp() {
        return hp;
    }

    //punteros
    Monstruos* left;
    Monstruos* right;

private:
    //atributos privados --encapsulamiento--
    T nombre, tipo, tamano, align;
    double cr, ac, hp;
};