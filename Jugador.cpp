#include "Jugador.h"
#include <algorithm>

Jugador::Jugador() : trenesDisponibles(72), puntos(0) {}

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

void Jugador::usarCartas(Color c, int cantidad) {
    int eliminados = 0;
    for (auto it = mano.begin(); it != mano.end() && eliminados < cantidad;) {
        if (it->color == c) {
            it = mano.erase(it);
            eliminados++;
        } else {
            ++it;
        }
    }
}
