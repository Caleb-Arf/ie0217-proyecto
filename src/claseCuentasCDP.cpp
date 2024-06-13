#include "claseCuentasCDP.hpp"
#include <iomanip>
#include <fstream>

Cuenta::Cuenta(std::string moneda, double saldo)
    : moneda(moneda), saldo(saldo) {}

void Cuenta::mostrarInfo() const {
    std::cout << "Cuenta en " << moneda << ": " << saldo << "\n";
}

CDP::CDP(double monto, double tasaInteres, int plazo)
    : monto(monto), tasaInteres(tasaInteres), plazo(plazo) {}

void CDP::mostrarInfo() const {
    std::cout << "CDP - Monto: " << monto << ", Tasa de Interés: " << tasaInteres << "%, Plazo: " << plazo << " meses\n";
}

double CDP::calcularInteres() const {
    return monto * (tasaInteres / 100) * (plazo / 12.0);
}
