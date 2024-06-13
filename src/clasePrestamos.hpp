// Clase de info de prestamos
#ifndef CLASEPRESTAMOS_HPP
#define CLASEPRESTAMOS_HPP

#include <string>
#include <vector>
#include <iostream>

class InformacionPrestamo {
public:
    std::string tipo;
    double tasaInteres;
    
    InformacionPrestamo(std::string tipo, double tasaInteres);
    void mostrarInfo();
};

#endif // CLASEPRESTAMOS_HPP
