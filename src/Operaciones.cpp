#include "Operaciones.hpp"
#include <iostream>

Operacion::Operacion(sqlite3* db, Cliente* cliente) : db(db), cliente(cliente) {}

void Operacion::transferencia(double montoTransferencia, int idDestino) {
    std::string tabla = "Clientes";
    std::string dato = "Balance";

    std::string balanceO = cliente->getInfo(tabla, dato, cliente->getIdCliente());
    double balanceOrigen = std::stod(balanceO);

    std::string balandeD = cliente->getInfo(tabla, dato, idDestino);
    double balanceDestino = std::stod(balandeD);

    if (balanceOrigen < montoTransferencia) {
        std::cout << "Saldo insuficiente para realizar la transaccion." << std::endl;
        return;
    }

    double nuevoBalanceOrigen = balanceOrigen - montoTransferencia;
    double nuevoBalanceDestino = balanceDestino + montoTransferencia;

    cliente->setInfo("Clientes", "Balance", std::to_string(nuevoBalanceOrigen), cliente->getIdCliente());
    cliente->setInfo("Clientes", "Balance", std::to_string(nuevoBalanceDestino), idDestino);
}

void Operacion::deposito(double montoDeposito) {
    std::string tabla = "Clientes";
    std::string dato = "Balance";

    double balance = std::stod(cliente->getInfo(tabla, dato, cliente->getIdCliente()));

    double nuevoBalance = balance + montoDeposito;

    cliente->setInfo("Clientes", "Balance", std::to_string(nuevoBalance), cliente->getIdCliente());
}

