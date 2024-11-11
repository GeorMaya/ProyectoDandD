#pragma once

#include <string>

template <typename T>
class Monstruo {
public:
    Monstruo() : left(nullptr), right(nullptr), cr(0), ac(0), hp(0) {}

    Monstruo(T name, double cr, T type, T size, double ac, double hp, T align)
        : name(name), cr(cr), type(type), size(size), ac(ac), hp(hp), align(align), left(nullptr), right(nullptr) {}

    ~Monstruo() {}

    // Métodos getter para los atributos
    T getNombre() { return name; }
    double getCr() { return cr; }
    T getType() { return type; }
    T getSize() { return size; }
    double getAc() { return ac; }
    double getHp() { return hp; }
    T getAlign() { return align; }

    Monstruo* left;
    Monstruo* right;

private:
    T name, type, size, align;  // Atributos de tipo genérico
    double cr, ac, hp;          // Atributos específicos de tipo numérico
};
