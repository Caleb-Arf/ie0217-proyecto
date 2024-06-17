#include "cliente.hpp"

// Constructor
Cliente::Cliente(int IdCliente, const std::string& Nombre, int Cedula, int Telefono, const std::string& Direccion, const std::string& Correo, int Balance, const std::string& Prestamos, const std::string& TipoPrestamos)
    : IdCliente(IdCliente), Nombre(Nombre), Cedula(Cedula), Telefono(Telefono), Direccion(Direccion), Correo(Correo), Balance(Balance), Prestamos(Prestamos), TipoPrestamos(TipoPrestamos) {}

int Cliente::getIdCliente() const {
    return IdCliente;
}

std::string Cliente::getNombre() const {
    return Nombre;
}

int Cliente::getCedula() const {
    return Cedula;
}

int Cliente::getTelefono() const {
    return Telefono;
}

std::string Cliente::getDireccion() const {
    return Direccion;
}

std::string Cliente::getCorreo() const {
    return Correo;
}
int Cliente::getBalance() const {
    return Balance;
}

std::string Cliente::getPrestamos() const {
    return Prestamos;
}

std::string Cliente::getTipoPrestamos() const {
    return TipoPrestamos;
}



void Cliente::setNombre(const std::string& Nombre) {
    this->Nombre = Nombre;
}

void Cliente::setCedula(int Cedula) {
    this->Cedula = Cedula;
}
