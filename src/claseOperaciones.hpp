#ifndef OPERACION_HPP
#define OPERACION_HPP

#include <iostream>
#include <string>

class Operacion {
private:
    int id_cuenta;
    double monto;

public:
    // Constructor
    Operacion(const int& id, double m);

    // Métodos para Transferencia y Depósito
    void transferencia(const int& id_cuenta_destino, double monto_transferir);
    void deposito(double monto_depositar);

};

#endif // OPERACION_HPP
