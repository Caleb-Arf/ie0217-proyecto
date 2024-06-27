#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "tablaTransaccionOtra.hpp"

struct Transaccion {
    std::string fecha;
    std::string detalle;
    double credito;
    double debito;
    double balance;
};

std::vector<Transaccion> fetchTransactions(sqlite3* db, int client_id) {
    std::vector<Transaccion> transactions;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT FechaTransaccion, Detalle, Credito, Debito, SaldoBalance FROM tablaTransacciones WHERE IdCliente = ?";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return transactions;
    }

    sqlite3_bind_int(stmt, 1, client_id);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Transaccion transaction;
        transaction.fecha = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        transaction.detalle = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        transaction.credito = sqlite3_column_double(stmt, 2);
        transaction.debito = sqlite3_column_double(stmt, 3);
        transaction.balance = sqlite3_column_double(stmt, 4);
        transactions.push_back(transaction);
    }

    sqlite3_finalize(stmt);
    return transactions;
}

void generarEstado(const std::vector<Transaccion>& transactions) {
    std::cout << std::setw(15) << "Fecha" << " | "
              << std::setw(20) << "Detalle" << " | "
              << std::setw(10) << "Credito" << " | "
              << std::setw(10) << "Debito" << " | "
              << std::setw(10) << "Balance" << std::endl;
    std::cout << std::string(15, '-') << " | "
              << std::string(20, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(10, '-') << std::endl;

    for (const auto& transaction : transactions) {
        std::cout << std::setw(15) << transaction.fecha << " | "
                  << std::setw(20) << transaction.detalle << " | "
                  << std::setw(10) << transaction.credito << " | "
                  << std::setw(10) << transaction.debito << " | "
                  << std::setw(10) << transaction.balance << std::endl;
    }
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    } else {
        std::cout << "Base de datos abierta exitosamente" << std::endl;
    }

    int client_id = 2; // Reemplazar con el IdCliente específico
    std::vector<Transaccion> transactions = fetchTransactions(db, client_id);

    generarEstado(transactions);

    sqlite3_close(db);
    return 0;
}
