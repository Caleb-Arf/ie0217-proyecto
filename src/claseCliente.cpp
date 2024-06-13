#include "claseCliente.hpp"
#include "clasePrestamos.hpp"
#include <iomanip>
#include <fstream>

Cliente::Cliente(int idCliente, std::string nombre)
    : idCliente(idCliente), cedula(cedula), nombre(nombre), telefono(telefono), direccion(direccion), correo(correo), balance(0), prestamos(prestamos), tipoPrestamos(tipoPrestamos){}

Cliente::Cliente()
    : idCliente(0), cedula(0), nombre(""), telefono(0), direccion(""), correo(""), balance(0), idPrestamo(""), tipoPrestamos(""){}

void Cliente::mostrarInfo() {
    std::cout << "ID: " << idCliente << "\nCédula: " << cedula << "\nNombre: " << nombre << "\nTeléfono " << telefono << "\nDirección: " << direccion << "\n Correo: " << correo << "\n Balance: "
<< balance << "\nPréstamo: " << idPrestamo << "\nTipo de préstamo: " << tipoPrestamos << "\n";
}

void Cliente::agregarPrestamo(Prestamo prestamo) {
    prestamos.push_back(prestamo);
}
