#include "clasePrestamos.hpp"
#include <iomanip>
#include <fstream>

InformacionPrestamo::InformacionPrestamo(std::string tipo, double tasaInteres)
    : tipo(tipo), tasaInteres(tasaInteres) {}

void InformacionPrestamo::mostrarInfo() {
    std::cout << "Tipo de Préstamo: " << tipo << "\nTasa de Interés: " << tasaInteres << "%\n";
}
