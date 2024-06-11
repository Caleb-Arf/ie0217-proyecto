#include "claseOperaciones.hpp"

// Constructor
Operacion::Operacion(const int& id, double m) : id_cuenta(id), monto(m) {}

// Métodos para Transferencia y Depósito
void Operacion::transferencia(const int& idCuentaDestino, double montoTransferencia) {
    std::cout << "Transferencia:\n";
    std::cout << "De la cuenta: " << id_cuenta << "\n";
    std::cout << "A la cuenta: " << idCuentaDestino << "\n";
    std::cout << "Monto: " << montoTransferencia<< "\n";
    // Lógica para realizar la transferencia
}

void Operacion::deposito(double montoDeposito) {
    std::cout << "Depósito:\n";
    std::cout << "En la cuenta: " << id_cuenta << "\n";
    std::cout << "Monto: " << montoDeposito << "\n";
    // Lógica para realizar el depósito
}

