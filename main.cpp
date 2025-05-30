#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm> // Para std::random_shuffle
#include <limits>    // Para std::numeric_limits

#include "Carta.h"
#include "Trayecto.h"
#include "Jugador.h"
#include "Tablero.h" // Incluir el Tablero

// Variables globales para el juego (como antes)
std::vector<Carta> baraja;
std::vector<Carta> descarte;
std::vector<Carta> zonaVisible;

Tablero juegoTablero; // Instancia global del tablero

// Funciones globales del juego (como antes)
void inicializarBaraja() {
    for (int i = 0; i < 12; ++i) {
        baraja.push_back(Carta(ROJO));
        baraja.push_back(Carta(AZUL));
        baraja.push_back(Carta(VERDE));
        baraja.push_back(Carta(AMARILLO));
        baraja.push_back(Carta(NARANJA));
        baraja.push_back(Carta(PURPURA)); 
    }
    std::random_shuffle(baraja.begin(), baraja.end());
}

void reponerZonaVisible() {
    while (zonaVisible.size() < 5 && !baraja.empty()) {
        zonaVisible.push_back(baraja.back());
        baraja.pop_back();
    }
}

Carta robarCarta() {
    if (baraja.empty()) {
        if (descarte.empty()) {
            return Carta(COLOR_NULO); // No hay más cartas en la baraja ni en el descarte
        }
        std::cout << "La baraja se ha agotado. Barajando cartas del descarte...\n";
        baraja = descarte;
        descarte.clear();
        std::random_shuffle(baraja.begin(), baraja.end());
    }

    if (!baraja.empty()) {
        Carta c = baraja.back();
        baraja.pop_back();
        return c;
    }
    return Carta(COLOR_NULO); // En caso de que ambas barajas estén vacías
}

void mostrarZonaVisible() {
    std::cout << "Cartas disponibles en la zona visible: ";
    for (int i = 1; i < zonaVisible.size(); ++i) {
        std::cout << i << ":" << colorToString(zonaVisible[i].color) << "  ";
    }
    std::cout << "\n";
}

// Función que contiene la lógica principal del juego
void jugar() {
    int numJugadores;
    do {
        std::cout << "Ingrese la cantidad de jugadores (2-4): ";
        std::cin >> numJugadores;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (numJugadores < 2 || numJugadores > 4);

    std::vector<Jugador> jugadores(numJugadores);
    std::cout << "Se han creado " << numJugadores << " jugadores.\n";
    
    std::vector<Trayecto> trayectos = {
        {"A", "B", 4, ROJO, 0,0}, 
        {"H", "L", 6, ROJO, 0,0},
        {"J", "N", 2, ROJO, 0,0},
        {"A", "F", 4, AZUL, 0,0}, 
        {"H", "K", 2, AZUL, 0,0},
        {"I", "0", 6, AZUL, 0,0},
        {"E", "F", 3, VERDE, 0,0},
        {"N", "O", 3, VERDE, 0,0},
        {"K", "P", 3, VERDE, 0,0},
        {"P", "Q", 3, VERDE, 0,0},
        {"F", "G", 3, NARANJA, 0,0},
        {"F", "H", 2, NARANJA, 0,0},
        {"K", "L", 3, NARANJA, 0,0},
        {"O", "P", 3, NARANJA, 0,0},
        {"I", "K", 4, PURPURA, 0,0},
        {"O", "R", 4, PURPURA, 0,0},
        {"M", "Q", 4, PURPURA, 0,0},
        {"C", "G", 4, AMARILLO, 0,0},
        {"D", "E", 4, AMARILLO, 0,0},
        {"Q", "S", 4, AMARILLO, 0,0}
    };

    int turnoActual = 0; // Índice del jugador actual
    bool juegoEnCurso = true;

    while (juegoEnCurso) {
        Jugador& jugadorActual = jugadores[turnoActual]; // Referencia al jugador del turno

        std::cout << "\n--- Estado del Tablero ---\n";
        juegoTablero.mostrarTablero(); // Aquí se llama a la función de Tablero
        std::cout << "--------------------------\n";

        std::cout << "\n--- Turno del Jugador " << (turnoActual + 1) << " ---\n";
        std::cout << "Trenes disponibles: " << jugadorActual.trenesDisponibles << "\n";
        std::cout << "Puntos: " << jugadorActual.puntos << "\n";
        std::cout << "Cartas en mano: ";
        for(const auto& carta : jugadorActual.mano) {
            std::cout << colorToString(carta.color) << " ";
        }
        std::cout << "\n";
        mostrarZonaVisible();
        std::cout << "1. Robar 2 cartas de la zona visible o baraja\n";
        std::cout << "2. Realizar un trayecto\n";
        std::cout << "Seleccione una opcion: ";
        int opcion;
        std::cin >> opcion;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 1) {
            int cartasRobadas = 0;
            while (cartasRobadas < 2) {
                mostrarZonaVisible();
                std::cout << "Seleccione carta " << (cartasRobadas + 1) << " (1-4 para visible, 5 para baraja): ";
                int idx;
                std::cin >> idx;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (idx > 0 && idx < 5) {
                    if (idx < zonaVisible.size()) {
                        Carta cartaRobada = zonaVisible[idx];
                        jugadorActual.agregarCarta(cartaRobada);
                        zonaVisible.erase(zonaVisible.begin() + idx);
                        descarte.push_back(cartaRobada);
                        reponerZonaVisible();
                        cartasRobadas++;
                    } else {
                        std::cout << "Índice de zona visible inválido o ranura vacía. Intenta de nuevo.\n";
                    }
                } else if (idx == 5) { // De la baraja (ciego)
                    Carta robada = robarCarta();
                    if (robada.color != COLOR_NULO) {
                        jugadorActual.agregarCarta(robada);
                        std::cout << "Robaste una carta de la baraja: " << colorToString(robada.color) << "\n";
                        cartasRobadas++;
                    } else {
                        std::cout << "La baraja está vacía. No se pueden robar más cartas.\n";
                        if (baraja.empty() && descarte.empty()) {
                            juegoEnCurso = false;
                            break;
                        }
                    }
                } else {
                    std::cout << "Opción inválida para robar carta. Intenta de nuevo.\n";
                }
            }
        } else if (opcion == 2) {
            std::cout << "Trayectos disponibles:\n";
            for (int i = 0; i < trayectos.size(); ++i) {
                std::cout << i << ". " << trayectos[i].ciudadA << "-" << trayectos[i].ciudadB
                          << " (Longitud: " << trayectos[i].longitud - 1  << ", Color: " << colorToString(trayectos[i].color) << ")\n";
            }
            std::cout << "Elige uno: ";
            int idx;
            std::cin >> idx;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (idx >= 0 && idx < trayectos.size()) {
                if (jugadorActual.puedeTomarTrayecto(trayectos[idx])) {
                    jugadorActual.usarCartas(trayectos[idx].color, trayectos[idx].longitud);
                    jugadorActual.trenesDisponibles -= trayectos[idx].longitud;
                    jugadorActual.puntos += puntosPorLongitud(trayectos[idx].longitud);
                    std::cout << "¡Trayecto " << trayectos[idx].ciudadA << "-" << trayectos[idx].ciudadB << " completado! Puntos: " << jugadorActual.puntos << "\n";
                    trayectos.erase(trayectos.begin() + idx);
                    std::cout << "El trayecto ha sido removido de la lista de disponibles.\n";

                    if (jugadorActual.trenesDisponibles <= 2) {
                        std::cout << "\n¡El Jugador " << (turnoActual + 1) << " tiene 2 o menos trenes! Ultima ronda para todos.\n";
                        juegoEnCurso = false;
                    }

                } else {
                    std::cout << "No tienes suficientes cartas o trenes disponibles para este trayecto.\n";
                }
            } else {
                std::cout << "Selección de trayecto inválida.\n";
            }
        } else {
            std::cout << "Opción inválida. Intenta de nuevo.\n";
        }

        if (juegoEnCurso) {
            turnoActual = (turnoActual + 1) % numJugadores;
        }
    }

    std::cout << "\n--- Juego Terminado ---\n";
    std::cout << "\n--- Tablero Final ---\n";
    juegoTablero.mostrarTablero();
    std::cout << "---------------------\n";

    std::cout << "\nResultados finales:\n";
    for (int i = 0; i < numJugadores; ++i) {
        std::cout << "Jugador " << (i + 1) << ": " << jugadores[i].puntos << " puntos. Trenes restantes: " << jugadores[i].trenesDisponibles << "\n";
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    inicializarBaraja();
    reponerZonaVisible();

    jugar();
    return 0;
}