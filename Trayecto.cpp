#include "Trayecto.h"

int puntosPorLongitud(int longitud) {
    switch (longitud) {
        case 2: return 1;
        case 3: return 2;
        case 4: return 4;
        case 5: return 6;
        case 6: return 9;
        default: return 0;
    }
}
