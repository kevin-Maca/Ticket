#include "Carta.h"

std::string colorToString(Color c) {
    switch (c) {
        case ROJO: return "Rojo";
        case AZUL: return "Azul";
        case VERDE: return "Verde";
        case AMARILLO: return "Amarillo";
        case NARANJA: return "Naranja";
        case PURPURA: return "Purpura";
        default: return "Nulo";
    }
}
