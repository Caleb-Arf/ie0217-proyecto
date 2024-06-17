// ClaseCliente.hpp

#ifndef CLASECLIENTE_HPP
#define CLASECLIENTE_HPP

#include <string>
#include <vector>
#include "ClasePrestamos.hpp"

// Clase que representa a un Cliente
class Cliente {
private:
    std::string idCliente;            // ID del cliente
    std::string nombre;               // Nombre del cliente
    std::string direccion;            // Dirección del cliente
    std::string telefono;             // Teléfono del cliente
    std::string correo;               // Correo del cliente
    std::string cedula;               // Cédula del cliente
    double balance;                   // Balance del cliente
    std::vector<Prestamos> prestamos; // Lista de préstamos del cliente
    std::string tipoPrestamos;        // Tipo de préstamos del cliente

public:
    // Constructor
    Cliente(const std::string& idCliente, const std::string& nombre, const std::string& direccion, const std::string& telefono, const std::string& correo, const std::string& cedula, double balance, const std::string& tipoPrestamos);
    // Placeholders de los métodos.
    // Métodos para obtener y establecer el ID del cliente
    std::string getIdCliente() const;
    void setIdCliente(const std::string& idCliente);

 
    std::string getNombre() const;
    void setNombre(const std::string& nombre);

    std::string getDireccion() const;
    void setDireccion(const std::string& direccion);

    std::string getTelefono() const;
    void setTelefono(const std::string& telefono);

    std::string getCorreo() const;
    void setCorreo(const std::string& correo);

    std::string getCedula() const;
    void setCedula(const std::string& cedula);

    double getBalance() const;
    void setBalance(double balance);

    std::vector<Prestamos> getPrestamos() const;
    void addPrestamo(const Prestamos& prestamo);

    std::string getTipoPrestamos() const;
    void setTipoPrestamos(const std::string& tipoPrestamos);

    void mostrarCliente() const;
};

#endif // CLASECLIENTE_HPP
