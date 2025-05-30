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

   
    Jugador(int trenesIniciales);

    void agregarCarta(Carta c);
  
    bool puedeTomarTrayecto(const Trayecto& t);
    std::vector<Carta> usarCartas(Color c, int cantidad); 
};

#endif