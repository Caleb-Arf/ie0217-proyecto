// ClaseCliente.cpp

#include "ClaseCliente.hpp"
#include <iostream>

// Constructor
Cliente::Cliente(const std::string& idCliente, const std::string& nombre, const std::string& direccion, const std::string& telefono, const std::string& correo, const std::string& cedula, double balance, const std::string& tipoPrestamos)
    : idCliente(idCliente), nombre(nombre), direccion(direccion), telefono(telefono), correo(correo), cedula(cedula), balance(balance), tipoPrestamos(tipoPrestamos) {}
// Métodos placeholder
// Métodos para obtener y establecer el ID del cliente
std::string Cliente::getIdCliente() const {
    return idCliente;
}

void Cliente::setIdCliente(const std::string& idCliente) {
    this->idCliente = idCliente;
}


std::string Cliente::getNombre() const {
    return nombre;
}

void Cliente::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}


std::string Cliente::getDireccion() const {
    return direccion;
}

void Cliente::setDireccion(const std::string& direccion) {
    this->direccion = direccion;
}


std::string Cliente::getTelefono() const {
    return telefono;
}

void Cliente::setTelefono(const std::string& telefono) {
    this->telefono = telefono;
}


std::string Cliente::getCorreo() const {
    return correo;
}

void Cliente::setCorreo(const std::string& correo) {
    this->correo = correo;
}


std::string Cliente::getCedula() const {
    return cedula;
}

void Cliente::setCedula(const std::string& cedula) {
    this->cedula = cedula;
}


double Cliente::getBalance() const {
    return balance;
}

void Cliente::setBalance(double balance) {
    this->balance = balance;
}


std::vector<Prestamos> Cliente::getPrestamos() const {
    return prestamos;
}

void Cliente::addPrestamo(const Prestamos& prestamo) {
    prestamos.push_back(prestamo);
}


std::string Cliente::getTipoPrestamos() const {
    return tipoPrestamos;
}

void Cliente::setTipoPrestamos(const std::string& tipoPrestamos) {
    this->tipoPrestamos = tipoPrestamos;
}

// Método para mostrar la información del cliente
void Cliente::mostrarCliente() const {
    std::cout << "ID Cliente: " << idCliente << "\nNombre: " << nombre << "\nDireccion: " << direccion << "\nTelefono: " << telefono << "\nCorreo: " << correo
              << "\nCedula: " << cedula << "\nBalance: " << balance << "\nTipo de Prestamos: " << tipoPrestamos << "\nPrestamos: ";
    for (const auto& prestamo : prestamos) {
        prestamo.mostrarPrestamo();
    }
}
