// ClasePrestamos.hpp

#ifndef CLASEPRESTAMOS_HPP
#define CLASEPRESTAMOS_HPP

#include <string>

// Clase que representa un Préstamo
class Prestamos {
private:
    std::string numeroPrestamo; // Número del préstamo
    double monto;               // Monto del préstamo
    double tasaInteres;         // Tasa de interés del préstamo
    int plazo;                  // Plazo del préstamo en meses
    std::string tipoPrestamo;   // Tipo de préstamo

public:
    // Constructor
    Prestamos(const std::string& numeroPrestamo, double monto, double tasaInteres, int plazo, const std::string& tipoPrestamo);
    // Métodos placeholder
    // Métodos para obtener y establecer el número del préstamo
    std::string getNumeroPrestamo() const;
    void setNumeroPrestamo(const std::string& numeroPrestamo);

    double getMonto() const;
    void setMonto(double monto);

    double getTasaInteres() const;
    void setTasaInteres(double tasaInteres);

    int getPlazo() const;
    void setPlazo(int plazo);

    std::string getTipoPrestamo() const;
    void setTipoPrestamo(const std::string& tipoPrestamo);


    void mostrarPrestamo() const;
};

#endif // CLASEPRESTAMOS_HPP
