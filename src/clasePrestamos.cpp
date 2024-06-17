// ClasePrestamos.cpp

#include "ClasePrestamos.hpp"
#include <iostream>

// Constructor
Prestamos::Prestamos(const std::string& numeroPrestamo, double monto, double tasaInteres, int plazo, const std::string& tipoPrestamo)
    : numeroPrestamo(numeroPrestamo), monto(monto), tasaInteres(tasaInteres), plazo(plazo), tipoPrestamo(tipoPrestamo) {}
// Métodos placeholder
std::string Prestamos::getNumeroPrestamo() const {
    return numeroPrestamo;
}

void Prestamos::setNumeroPrestamo(const std::string& numeroPrestamo) {
    this->numeroPrestamo = numeroPrestamo;
}

double Prestamos::getMonto() const {
    return monto;
}

void Prestamos::setMonto(double monto) {
    this->monto = monto;
}

double Prestamos::getTasaInteres() const {
    return tasaInteres;
}

void Prestamos::setTasaInteres(double tasaInteres) {
    this->tasaInteres = tasaInteres;
}

int Prestamos::getPlazo() const {
    return plazo;
}

void Prestamos::setPlazo(int plazo) {
    this->plazo = plazo;
}

std::string Prestamos::getTipoPrestamo() const {
    return tipoPrestamo;
}

void Prestamos::setTipoPrestamo(const std::string& tipoPrestamo) {
    this->tipoPrestamo = tipoPrestamo;
}

// Método para mostrar la información del préstamo
void Prestamos::mostrarPrestamo() const {
    std::cout << "\nNumero de Prestamo: " << numeroPrestamo << "\nMonto: " << monto << "\nTasa de Interes: " << tasaInteres << "\nPlazo: " << plazo << "\nTipo de Prestamo: " << tipoPrestamo << std::endl;
}
