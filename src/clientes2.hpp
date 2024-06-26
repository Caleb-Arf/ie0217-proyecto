#ifndef CLIENTES_HPP
#define CLIENTES_HPP

#include <iostream>
#include <sqlite3.h>
#include <string>

class Cliente {
private:
    sqlite3* db;
    int idCliente;

public:
    int getIdCliente() const;
    Cliente(sqlite3* db, int idCliente);
    std::string getInfoClientes(const std::string& tabla, const std::string& dato, int idCliente);
    void setInfoClientes(const std::string& tabla, const std::string& dato, const std::string& datoActualizado, int idCliente);
    std::string getInfoInteres(const std::string& tabla, const std::string& dato, int id);
    std::string getInfoPrestamos(const std::string& dato, int idPrestamos);
    void setInfoPrestamos(const std::string& dato, const std::string& datoActualizado, int idPrestamo);
};

#endif // CLIENTES_HPP
