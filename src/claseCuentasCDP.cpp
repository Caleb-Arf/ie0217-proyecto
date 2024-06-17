// ClaseCuentasCDP.cpp

#include "ClaseCuentasCDP.hpp"
#include <iostream>

// Constructor
CuentasCDP::CuentasCDP(const std::string& numeroCuenta, double monto, double tasaInteres, int plazo)
    : numeroCuenta(numeroCuenta), monto(monto), tasaInteres(tasaInteres), plazo(plazo) {}
// Placeholder

std::string CuentasCDP::getNumeroCuenta() const {
    return numeroCuenta;
}

void CuentasCDP::setNumeroCuenta(const std::string& numeroCuenta) {
    this->numeroCuenta = numeroCuenta;
}

double CuentasCDP::getMonto() const {
    return monto;
}

void CuentasCDP::setMonto(double monto) {
    this->monto = monto;
}

double CuentasCDP::getTasaInteres() const {
    return tasaInteres;
}

void CuentasCDP::setTasaInteres(double tasaInteres) {
    this->tasaInteres = tasaInteres;
}

int CuentasCDP::getPlazo() const {
    return plazo;
}

void CuentasCDP::setPlazo(int plazo) {
    this->plazo = plazo;
}

// Método para mostrar la información de la cuenta CDP
void CuentasCDP::mostrarCuentaCDP() const {
    std::cout << "\nNumero de Cuenta CDP: " << numeroCuenta << "\nMonto: " << monto << "\nTasa de Interes: " << tasaInteres << "\nPlazo: " << plazo << std::endl;
}
