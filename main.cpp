#include <iostream>
#include <vector>
#include <ctime>     
#include <cstdlib>    
#include <algorithm>  
#include <random>    
#include <chrono>    
#include <limits>     


#ifdef _WIN32
#include <windows.h>
#include <io.h>    
#include <fcntl.h>  
#endif

#include "Carta.h"    
#include "Trayecto.h" 
#include "Jugador.h"  
#include "Tablero.h"  


std::vector<Carta> baraja;
std::vector<Carta> descarte;
std::vector<Carta> zonaVisible;

Tablero juegoTablero; 


std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());


void inicializarBaraja() {
    for (int i = 0; i < 12; ++i) {
        baraja.push_back(Carta(ROJO)); 
        baraja.push_back(Carta(AZUL));
        baraja.push_back(Carta(VERDE));
        baraja.push_back(Carta(AMARILLO));
        baraja.push_back(Carta(NARANJA));
        baraja.push_back(Carta(PURPURA));
    }
    std::shuffle(baraja.begin(), baraja.end(), rng); 
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
            return Carta(COLOR_NULO); 
        }
        std::cout << "La baraja se ha agotado. Barajando cartas del descarte...\n";
        baraja = descarte;
        descarte.clear();
        std::shuffle(baraja.begin(), baraja.end(), rng);
    }

    if (!baraja.empty()) {
        Carta c = baraja.back();
        baraja.pop_back();
        return c;
    }
    return Carta(COLOR_NULO); // 
}

void mostrarZonaVisible() {
    std::cout << "Cartas disponibles en la zona visible: ";
    for (int i = 0; i < zonaVisible.size(); ++i) {
        
        std::cout << (i + 1) << ":" << colorToString(zonaVisible[i].color) << "  ";
    }
    std::cout << "\n";
}


void jugar() {
    int numJugadores;
    do {
        std::cout << "Ingrese la cantidad de jugadores (2-4): ";
        std::cin >> numJugadores;
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (numJugadores < 2 || numJugadores > 4); 

    int trenesPorJugador; 

   
    if (numJugadores == 2) {
        trenesPorJugador = 36;
    } else if (numJugadores == 3) {
        trenesPorJugador = 24;
    } else { //== 4
        trenesPorJugador = 18;
    }


    std::vector<Jugador> jugadores;
    for (int i = 0; i < numJugadores; ++i) {
        jugadores.push_back(Jugador(trenesPorJugador));
    }

    std::cout << "Se han creado " << numJugadores << " jugadores. Cada uno con " << trenesPorJugador << " trenes.\n";

   
    std::vector<Trayecto> trayectos = {
        {"A", "B", 4, ROJO, 0,0}, 
        {"H", "L", 6, ROJO, 0,0},
        {"J", "N", 2, ROJO, 0,0},
        {"A", "F", 4, AZUL, 0,0},
        {"H", "K", 2, AZUL, 0,0},
        {"I", "O", 6, AZUL, 0,0},
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

    // Repartir cartas iniciales a los jugadores (Ticket to Ride reparte 4 cartas)
    for (int i = 0; i < numJugadores; ++i) {
        for (int k = 0; k < 4; ++k) { // Repartir 4 cartas a cada jugador
            jugadores[i].agregarCarta(robarCarta());
        }
    }


    while (juegoEnCurso) {
        Jugador& jugadorActual = jugadores[turnoActual]; // Referencia al jugador del turno

        std::cout << "\n--- Estado del Tablero ---\n";
        juegoTablero.mostrarTablero(); // Aquí llamamos a la función de Tablero
        std::cout << "--------------------------\n";

        std::cout << "\n--- Turno del Jugador " << (turnoActual + 1) << " ---\n";
        std::cout << "Trenes disponibles: " << jugadorActual.trenesDisponibles << "\n";
        std::cout << "Puntos: " << jugadorActual.puntos << "\n";
        std::cout << "Cartas en mano: ";
        // Para mostrar las cartas de manera más legible, podrías agruparlas por color
        // y mostrar el conteo (ej. "Rojo x3, Azul x2")
        for(const auto& carta : jugadorActual.mano) {
            std::cout << colorToString(carta.color) << " ";
        }
        std::cout << "\n";

        mostrarZonaVisible(); // Muestra la zona visible

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
                // Indice para la baraja "ciega" será el siguiente número después de las cartas visibles
                int opcionBarajaCiega = zonaVisible.size() + 1;
                std::cout << "Seleccione carta " << (cartasRobadas + 1) << " (1-" << zonaVisible.size() << " para visible, " << opcionBarajaCiega << " para baraja): ";
                int idx;
                std::cin >> idx;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (idx > 0 && idx <= zonaVisible.size()) { // Robar de zona visible
                    // Ajustar el índice para que sea 0-basado para el vector
                    Carta cartaRobada = zonaVisible[idx - 1];
                    jugadorActual.agregarCarta(cartaRobada);
                    zonaVisible.erase(zonaVisible.begin() + (idx - 1)); // Eliminar la carta del vector
                    descarte.push_back(cartaRobada); // Moverla al descarte (asumiendo que visible pasa a descarte)
                    reponerZonaVisible();
                    cartasRobadas++;
                } else if (idx == opcionBarajaCiega) { // Robar de la baraja (ciego)
                    Carta robada = robarCarta();
                    if (robada.color != COLOR_NULO) { // Si usas enum class, sería Color::COLOR_NULO
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
                          << " (Longitud: " << trayectos[i].longitud << ", Color: " << colorToString(trayectos[i].color) << ")\n";
            }
            std::cout << "Elige uno: ";
            int idx;
            std::cin >> idx;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (idx >= 0 && idx < trayectos.size()) {
                if (jugadorActual.puedeTomarTrayecto(trayectos[idx])) {
                    
                    std::vector<Carta> cartasDescartadas = jugadorActual.usarCartas(trayectos[idx].color, trayectos[idx].longitud);
                    for(const auto& carta : cartasDescartadas) {
                        descarte.push_back(carta);
                    }

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
   
    #ifdef _WIN32
       
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);

       
        SetConsoleOutputCP(CP_UTF8);
     
        _setmode(_fileno(stdout), _O_U16TEXT);
    #endif
    // -----------------------------------------------------------------------------------------

  
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    inicializarBaraja();
    reponerZonaVisible(); 

    jugar();
    	std::cout << "\nPresiona Enter para salir...";
    	std::cin.ignore();
    	std::cin.get();

    return 0;
}