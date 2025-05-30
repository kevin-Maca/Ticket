#ifndef JUGADOR_H
#define JUGADOR_H

#include <vector>
#include "Carta.h"
#include "Trayecto.h"

class Jugador {
public:
    std::vector<Carta> mano;
    int trenesDisponibles;
    int puntos;

    Jugador();

    void agregarCarta(Carta c);
    bool puedeTomarTrayecto(const Trayecto& t);
    void usarCartas(Color c, int cantidad);
};

#endif
