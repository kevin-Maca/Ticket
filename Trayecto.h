#ifndef TRAYECTO_H
#define TRAYECTO_H

#include <string>
#include "Carta.h"

struct Trayecto {
    std::string ciudadA;
    std::string ciudadB;
    int longitud;
    Color color;
    int x, y; // Coordenadas para visualización

    Trayecto(std::string a, std::string b, int l, Color c, int x, int y)
        : ciudadA(a), ciudadB(b), longitud(l), color(c), x(x), y(y) {}
};

int puntosPorLongitud(int longitud);

#endif
