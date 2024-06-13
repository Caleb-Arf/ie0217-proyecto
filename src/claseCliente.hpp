// Clase de info de cliente
#ifndef CLASECLIENTE_HPP
#define CLASECLIENTE_HPP

#include "prestamos.hpp"
#include <string>
#include <vector>
#include <iostream>

class Cliente {
public:
    int idCliente;
    int cedula;
    std::string nombre;
    int telefono;
    std::string direccion;
    std::string correo;
    double balance;
    std::string idPrestamo;
    std::string tipoPrestamos;


    std::vector<std::string> historialTransacciones;
    std::vector<Prestamo> prestamos;
    
    Cliente(int idCliente, std::string nombre);
    Cliente();
    void mostrarInfo();
    void agregarPrestamo(Prestamo prestamo);
};

#endif // CLASECLIENTE_HPP
