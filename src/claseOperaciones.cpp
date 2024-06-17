#include "Operaciones.hpp"
#include <iostream> // Asegúrate de incluir <iostream> para usar std::cout

Operacion::Operacion(sqlite3* db, int idCliente) : db(db), idCliente(idCliente) {}

void Operacion::transferencia(double montoTransferencia, int idDestino) {
    double balanceOrigen = obtenerBalance(db, idCliente);
    double balanceDestino = obtenerBalance(db, idDestino);
    
    if (balanceOrigen < montoTransferencia) {
        std::cout << "Saldo insuficiente para realizar la transaccion." << std::endl;
        return;
    }
    
    double nuevoBalanceOrigen = balanceOrigen - montoTransferencia;
    double nuevoBalanceDestino = balanceDestino + montoTransferencia;

    actualizarBalance(db, idCliente, nuevoBalanceOrigen);
    actualizarBalance(db, idDestino, nuevoBalanceDestino);
}

void Operacion::deposito(double montoDeposito) {
    double balance = obtenerBalance(db, idCliente);
    double nuevoBalance = balance + montoDeposito;
    actualizarBalance(db, idCliente, nuevoBalance);
}

