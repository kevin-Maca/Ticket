#include "Tablero.h"
#include <iostream>
#include <map>
#include <string>
#include <windows.h>

// Definiciones de códigos de escape ANSI para colores de texto
// Ten en cuenta que la compatibilidad con ANSI varía según la terminal
#define BG_RED     "\x1B[41m" // Rojo
#define BG_BLUE    "\x1b[44m" // Azul
#define BG_GREEN   "\x1B[42m" // Verde
#define BG_YELLOW  "\x1b[43m" // Amarillo
#define BG_ORANGE  "\x1B[48;2;255;128;0m" // Naranja (color 208 en la paleta de 256 colores ANSI)
#define BG_PURPLE  "\x1b[45m" // Magenta/Púrpura
#define RESET   "\x1b[0m"  // Resetear color

// Mapeo de enum Color a códigos ANSI
std::map<Color, std::string> color_ansi_map = {
    {ROJO, BG_RED},
    {AZUL, BG_BLUE},
    {VERDE, BG_GREEN},
    {AMARILLO, BG_YELLOW},
    {NARANJA, BG_ORANGE},
    {PURPURA, BG_PURPLE},
};

// Función auxiliar para obtener el código ANSI de un color
std::string getAnsiColorCode(Color c) {
    auto it = color_ansi_map.find(c);
    if (it != color_ansi_map.end()) {
        return it->second;
    }
    return RESET; // Por defecto, sin color
}


Tablero::Tablero() {
    celdas = std::vector<std::vector<Celda>>(FILAS, std::vector<Celda>(COLUMNAS, {VACIA, "", COLOR_NULO}));
    inicializarDisenoTablero();
}

void Tablero::colocarCiudad(int fila, int columna, const std::string& nombre) {
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        celdas[fila][columna].tipo = CIUDAD;
        celdas[fila][columna].nombreCiudad = nombre;
        celdas[fila][columna].colorTrayecto = COLOR_NULO; // Las ciudades no tienen color de trayecto
    }
}

void Tablero::colocarSegmentoTrayecto(int fila, int columna, Color color) {
    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        celdas[fila][columna].tipo = TRAYECTO;
        celdas[fila][columna].colorTrayecto = color;
    }
}

void Tablero::inicializarDisenoTablero() {
    // Definir ciudades (coordenadas 0-indexadas)
    colocarCiudad(7, 0, "A");  // Fila 8, Columna 1
    colocarCiudad(4, 2, "B");  // Fila 5, Columna 3
    colocarCiudad(13, 2, "C"); // Fila 13, Columna 3
    colocarCiudad(0, 3, "D");  // Fila 4, Columna 5
    colocarCiudad(3, 5, "E");  // Fila 5, Columna 6
    colocarCiudad(7, 5, "F");  // Fila 8, Columna 7
    colocarCiudad(11, 5, "G"); // Fila 12, Columna 7
    colocarCiudad(7, 8, "H");  // Fila 8, Columna 9
    colocarCiudad(4, 9, "I"); // Fila 6, Columna 11
    colocarCiudad(1, 10, "J"); // Fila 2, Columna 11
    colocarCiudad(7, 11, "K"); // Fila 8, Columna 13
    colocarCiudad(11, 11, "L"); // Fila 12, Columna 12
    colocarCiudad(13, 12, "M"); // Fila 14, Columna 14
    colocarCiudad(1, 13, "N"); // Fila 2, Columna 15
    colocarCiudad(3, 15, "O"); // Fila 4, Columna 16
    colocarCiudad(7, 15, "P"); // Fila 8, Columna 16
    colocarCiudad(11, 15, "Q"); // Fila 12, Columna 16
    colocarCiudad(5, 18, "R"); // Fila 6, Columna 18
    colocarCiudad(9, 18, "S"); // Fila 11, Columna 19

	//Trayecto A-B (ROJO)
    colocarSegmentoTrayecto(6, 0, ROJO);
    colocarSegmentoTrayecto(5, 0, ROJO);
    colocarSegmentoTrayecto(4, 0, ROJO);
    colocarSegmentoTrayecto(4, 1, ROJO);

    // Trayecto H-L (ROJO)
    colocarSegmentoTrayecto(8, 8, ROJO);
    colocarSegmentoTrayecto(9, 8, ROJO);
    colocarSegmentoTrayecto(10, 8, ROJO);
    colocarSegmentoTrayecto(11, 8, ROJO);
    colocarSegmentoTrayecto(11, 9, ROJO);
    colocarSegmentoTrayecto(11, 10, ROJO);
    
    //Trayecto J-N (ROJO)
    colocarSegmentoTrayecto(1, 11, ROJO);
    colocarSegmentoTrayecto(1, 12, ROJO);
    
    // Trayecto A-F (AZUL)
    colocarSegmentoTrayecto(7, 1, AZUL);
    colocarSegmentoTrayecto(7, 2, AZUL);
    colocarSegmentoTrayecto(7, 3, AZUL);
    colocarSegmentoTrayecto(7, 4, AZUL);
    
    // Trayecto H-K (AZUL)
    colocarSegmentoTrayecto(7, 9, AZUL);
    colocarSegmentoTrayecto(7, 10, AZUL);
    
    // Trayecto I-O (AZUL)
    colocarSegmentoTrayecto(3, 9, AZUL);
    colocarSegmentoTrayecto(3, 10, AZUL);
    colocarSegmentoTrayecto(3, 11, AZUL);
    colocarSegmentoTrayecto(3, 12, AZUL);
    colocarSegmentoTrayecto(3, 13, AZUL);
    colocarSegmentoTrayecto(3, 14, AZUL);
    
    // Trayecto E-F (VERDE)
    colocarSegmentoTrayecto(4, 5, VERDE);
    colocarSegmentoTrayecto(5, 5, VERDE);
    colocarSegmentoTrayecto(6, 5, VERDE);
    
    // Trayecto N-O (VERDE)
    colocarSegmentoTrayecto(1, 14, VERDE);
    colocarSegmentoTrayecto(1, 15, VERDE);
    colocarSegmentoTrayecto(2, 15, VERDE);
    
    // Trayecto K-P (VERDE)
    colocarSegmentoTrayecto(7, 12, VERDE);
    colocarSegmentoTrayecto(7, 13, VERDE);
    colocarSegmentoTrayecto(7, 14, VERDE);
    
    // Trayecto P-Q (VERDE)
    colocarSegmentoTrayecto(8, 15, VERDE);
    colocarSegmentoTrayecto(9, 15, VERDE);
    colocarSegmentoTrayecto(10, 15, VERDE);
    
    //Trayecto F-G (NARANJA)
    colocarSegmentoTrayecto(8, 5, NARANJA);
    colocarSegmentoTrayecto(9, 5, NARANJA);
    colocarSegmentoTrayecto(10, 5, NARANJA);
    
    // Trayecto F-H (NARANJA)
    colocarSegmentoTrayecto(7, 6, NARANJA);
    colocarSegmentoTrayecto(7, 7, NARANJA);
    
    // Trayecto K-L (NARANJA)
    colocarSegmentoTrayecto(8, 11, NARANJA);
    colocarSegmentoTrayecto(9, 11, NARANJA);
    colocarSegmentoTrayecto(10, 11, NARANJA);
    
    // Trayecto O-P (NARANJA)
    colocarSegmentoTrayecto(4, 15, NARANJA);
    colocarSegmentoTrayecto(5, 15, NARANJA);
    colocarSegmentoTrayecto(6, 15, NARANJA);
    
    // Trayecto I-K (PURPURA)
    colocarSegmentoTrayecto(5, 9, PURPURA);
    colocarSegmentoTrayecto(5,10, PURPURA);
    colocarSegmentoTrayecto(5, 11, PURPURA); 
    colocarSegmentoTrayecto(6, 11, PURPURA);
    
    // Trayecto O-R (PURPURA)
    colocarSegmentoTrayecto(3, 16, PURPURA);
    colocarSegmentoTrayecto(3, 17, PURPURA);
    colocarSegmentoTrayecto(3, 18, PURPURA);
    colocarSegmentoTrayecto(4, 18, PURPURA);
    
    // Trayecto M-Q (PURPURA)
    colocarSegmentoTrayecto(13, 13, PURPURA);
    colocarSegmentoTrayecto(13, 14, PURPURA);
    colocarSegmentoTrayecto(13, 15, PURPURA);
    colocarSegmentoTrayecto(12, 15, PURPURA);
    
    // Trayecto C-G (AMARILLO)
    colocarSegmentoTrayecto(12, 2, AMARILLO);
    colocarSegmentoTrayecto(11, 2, AMARILLO);
    colocarSegmentoTrayecto(11, 3, AMARILLO);
    colocarSegmentoTrayecto(11, 4, AMARILLO);
    
    // Trayecto D-E (AMARILLO)
    colocarSegmentoTrayecto(0, 4, AMARILLO);
    colocarSegmentoTrayecto(0, 5, AMARILLO);
    colocarSegmentoTrayecto(1, 5, AMARILLO);
    colocarSegmentoTrayecto(2, 5, AMARILLO);
    
    // Trayecto Q-S (MARRON - Usaré NEGRO)
    colocarSegmentoTrayecto(11, 16, AMARILLO);
    colocarSegmentoTrayecto(11, 17, AMARILLO);
    colocarSegmentoTrayecto(11, 18, AMARILLO);
    colocarSegmentoTrayecto(10, 18, AMARILLO);
}


void Tablero::mostrarTablero() {
   #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // Activar el modo VT
    SetConsoleMode(hOut, dwMode);
	#endif
    // Imprimir encabezado de columnas (1, 2, ..., 19)
    std::cout << "   "; // Espacio para el número de fila
    for (int j = 0; j < COLUMNAS; ++j) {
        std::cout << (j + 1 < 10 ? " " : "") << j + 1 << " "; // Alineación para 1 o 2 dígitos
    }
    std::cout << " " << std::endl;

    for (int i = 0; i < FILAS; ++i) {
        // Imprimir número de fila
        std::cout << (i + 1 < 10 ? " " : "") << i + 1 << " "; // Alineación para 1 o 2 dígitos
        for (int j = 0; j < COLUMNAS; ++j) {
            switch (celdas[i][j].tipo) {
                case CIUDAD:
                    if (!celdas[i][j].nombreCiudad.empty()) {
                        std::cout << celdas[i][j].nombreCiudad[0] << "  "; // Primera letra de la ciudad
                    } else {
                        std::cout << "C  "; // Si por alguna razón no tiene nombre
                    }
                    break;
                case TRAYECTO:
                    // Usa el color ANSI si es un trayecto
                    std::cout << getAnsiColorCode(celdas[i][j].colorTrayecto) << "█" << RESET; // Bloque coloreado
                    break;
                case VACIA:
                default:
                    std::cout << ".  "; // Celda vacía
                    break;
            }
        }
        std::cout << std::endl;
    }
}