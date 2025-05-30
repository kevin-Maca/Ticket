#ifndef CARTA_H
#define CARTA_H

#include <string>

enum Color { ROJO, AZUL, VERDE, AMARILLO, NARANJA, PURPURA, COLOR_NULO };

struct Carta {
    Color color;
    Carta(Color c) : color(c) {}
};

std::string colorToString(Color c);

#endif
