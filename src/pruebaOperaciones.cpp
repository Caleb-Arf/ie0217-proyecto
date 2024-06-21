#include <iostream>
#include "clientes2.hpp"
#include "Operaciones.hpp"

int main() {
    sqlite3* db;
    int rc = sqlite3_open("clientes.db", &db);

    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    Cliente cliente(db, 101006);

    Operacion operacion(db, &cliente);

    std::cout << "Realizando un depósito de 200000.0 a Cliente 1." << std::endl;
    operacion.deposito(200000.0);

    
    std::cout << "Realizando una transferencia de 300000.0 de Cliente 1 a Cliente 2." << std::endl;
    operacion.transferencia(100000.0, 103026);

    
    std::cout << "Balance de Cliente 1: " << cliente.getInfo("Clientes", "Balance", cliente.getIdCliente()) << std::endl;
    std::cout << "Balance de Cliente 2: " << cliente.getInfo("Clientes", "Balance", 103026) << std::endl;

    sqlite3_close(db);

    return 0;
}