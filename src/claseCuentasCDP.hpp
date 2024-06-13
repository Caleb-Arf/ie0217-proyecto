#ifndef CLASECUENTASCDP_HPP
#define CLASECUENTASCDP_HPP

#include <string>
#include <vector>
#include <iostream>

class Cuenta {
public:
    std::string idCuenta;
    std::string moneda;
    double saldo;

    Cuenta(std::string moneda, double saldo);
    void mostrarInfo() const;
};

class CDP {
public:
    double monto;
    double tasaInteres;
    int plazo; // en meses

    CDP(double monto, double tasaInteres, int plazo);
    void mostrarInfo() const;
    double calcularInteres() const;
};

#endif // CLASECUENTASCDP_HPP
