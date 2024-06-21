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
    Cliente(sqlite3* db, int idCliente);
    std::string getInfo(const std::string& tabla, const std::string& dato, int idCliente);
    void setInfo(const std::string& tabla, const std::string& dato, const std::string& datoActualizado, int idCliente);
    int getIdCliente() const;
};

#endif // CLIENTES_HPP
