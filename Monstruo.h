#pragma once

template <typename T>
class Monstruo {
public:
    Monstruo() : left(nullptr), right(nullptr), cr(T()), ac(T()), hp(T()) {}

    Monstruo(T name, T cr, T type, T size, T ac, T hp, T align)
        : name(name), cr(cr), type(type), size(size), ac(ac), hp(hp), align(align), left(nullptr), right(nullptr) {}

    ~Monstruo() {
    }

    T getCr() {
        return cr;
    }

    T getNombre() {
        return name;
    }

    T getType() {
        return type;
    }

    T getHp() {
        return hp;
    }

    Monstruo* left;
    Monstruo* right;

private:
    T name, type, size, align, cr, ac, hp;
};
