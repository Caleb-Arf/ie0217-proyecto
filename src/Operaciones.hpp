#ifndef OPERACIONES_HPP
#define OPERACIONES_HPP

#include <sqlite3.h>
#include "funciones.hpp"
class Operacion {
private:
    sqlite3* db;
    int idCliente;

public:
    Operacion(sqlite3* db, int idCliente);

    void transferencia(double montoTransferencia, int idDestino);
    
    void deposito(double montoDeposito);
};

#endif // OPERACIONES_HPP
