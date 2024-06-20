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

    std::string Cliente::getInfo(const std::string& tabla, const std::string& dato);
        
    void Cliente::setInfo(const std::string& tabla, const std::string& dato, const std::string& datoActualizado);
};

#endif //CLIENTES_HPP
