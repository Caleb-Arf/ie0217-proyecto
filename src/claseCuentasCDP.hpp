// ClaseCuentasCDP.hpp

#ifndef CLASECUENTASCDP_HPP
#define CLASECUENTASCDP_HPP

#include <string>

// Clase que representa una Cuenta CDP (Certificado de Depósito a Plazo)
class CuentasCDP {
private:
    std::string numeroCuenta; // Número de la cuenta CDP
    double monto;             // Monto depositado en la cuenta CDP
    double tasaInteres;       // Tasa de interés de la cuenta CDP
    int plazo;                // Plazo de la cuenta CDP en meses

public:
    // Constructor
    CuentasCDP(const std::string& numeroCuenta, double monto, double tasaInteres, int plazo);
    //Placeholders
    std::string getNumeroCuenta() const;
    void setNumeroCuenta(const std::string& numeroCuenta);

    double getMonto() const;
    void setMonto(double monto);

    double getTasaInteres() const;
    void setTasaInteres(double tasaInteres);

    int getPlazo() const;
    void setPlazo(int plazo);

    void mostrarCuentaCDP() const;
};

#endif // CLASECUENTASCDP_HPP
