#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>

class Cliente {
private:
    int IdCliente;
    std::string Nombre;
    int Cedula;
    int Telefono;
    const std::string& Direccion;
    const std::string& Correo;
    int Balance; 
    const std::string& Prestamos; 
    const std::string& TipoPrestamos;


public:
    // Constructor
    Cliente(int IdCliente, const std::string& Nombre, int Cedula, int Telefono, const std::string& Direccion, const std::string& Correo, int Balance, const std::string& Prestamos, const std::string& TipoPrestamos);

    
    int getIdCliente() const;
    std::string getNombre() const;
    int getCedula() const;
    int getTelefono() const;
    std::string& getDireccion() const;
    std::string& getCorreo() const;
    int getBalance() const; 
    std::string& getPrestamos() const; 
    std::string& getTipoPrestamos() const;

    void setIdCliente(int IdCliente);
    void setNombre(const std::string& Nombre);
    void setCedula(int Cedula);
    void setTelefono(int Telefono);
    void setDireccion(const std::string& Direccion);
    void setCorreo(const std::string& Correo);
    void setBalance(int Balance);
    void setPrestamos(const std::string& Prestamos);
    void setTipoPrestamos(const std::string& TipoPrestamos);
};

#endif // CLIENTE_HPP
