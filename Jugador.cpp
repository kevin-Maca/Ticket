#include "Jugador.h"
#include <algorithm> 


Jugador::Jugador(int trenesIniciales) : trenesDisponibles(trenesIniciales), puntos(0) {}

void Jugador::agregarCarta(Carta c) {
    mano.push_back(c);
}

bool Jugador::puedeTomarTrayecto(const Trayecto& t) {
    int conteo = 0;

    for (const auto& carta : mano) {
        if (carta.color == t.color)
            conteo++;
    }
    return conteo >= t.longitud && trenesDisponibles >= t.longitud;
}


std::vector<Carta> Jugador::usarCartas(Color c, int cantidad) {
    std::vector<Carta> descartadas;
    int eliminados = 0;
    for (auto it = mano.begin(); it != mano.end() && eliminados < cantidad;) {
        if (it->color == c) {
            descartadas.push_back(*it);
            it = mano.erase(it);
            eliminados++;
        } else {
            ++it;
        }
    }
    return descartadas;
}