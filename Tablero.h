#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include "Carta.h" // Para el enum Color

// Enum para el tipo de celda
enum TipoCelda { VACIA, CIUDAD, TRAYECTO };

// Estructura para cada celda del tablero
struct Celda {
    TipoCelda tipo;
    std::string nombreCiudad; // Solo si tipo == CIUDAD
    Color colorTrayecto;      // Para los segmentos de trayecto
    // Puedes agregar más atributos según necesites
};

// Estructura auxiliar para definir un segmento de trayecto con coordenadas y color
struct SegmentoTrayecto {
    int fila;
    int columna;
    Color color;
};

// Clase Tablero
class Tablero {
public:
    static const int FILAS = 14;
    static const int COLUMNAS = 19;
    std::vector<std::vector<Celda>> celdas;

    Tablero();
    void inicializarDisenoTablero();
    void colocarCiudad(int fila, int columna, const std::string& nombre);
    void colocarSegmentoTrayecto(int fila, int columna, Color color);
    void mostrarTablero(); // Para visualización
};

#endif