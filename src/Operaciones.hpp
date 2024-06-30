#ifndef OPERACIONES_HPP
#define OPERACIONES_HPP

#include "sqlite3.h"
#include "clientes2.hpp" 

class Operacion {
private:
    sqlite3* db;
    Cliente* cliente;  

public:
    Operacion(sqlite3* db, Cliente* cliente);
    void transferencia(double montoTransferencia, int idDestino);
    void deposito(double montoDeposito);
    int crearPrestamo(int idCliente, sqlite3* db);
    void abonoPrestamo();
    void abonoPrestamoExtraordinario();
    void crearCDP();
    void consultarCDP();
};

std::string obtenerFechaActual();


#endif // OPERACIONES_HPP
