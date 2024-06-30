#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "tablaTransaccionOtra.hpp"

// Función para recibir datos de la transacción
void regresarDatosTransaccion(sqlite3* db, int IdCliente, const std::string& fechaInicio, const std::string& fechaFin) {
    const char* sql = "SELECT FechaTransaccion, Detalle, Credito, Debito, SaldoBalance FROM tablaTransacciones WHERE IdCliente = ? AND FechaTransaccion BETWEEN ? AND ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparando declaración SQL: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Conecta IdCliente y fechas a parámetros
    sqlite3_bind_int(stmt, 1, IdCliente);
    sqlite3_bind_text(stmt, 2, fechaInicio.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, fechaFin.c_str(), -1, SQLITE_STATIC);

    // Imprime la información en tabla
    std::cout << std::setw(20) << std::setfill(' ') << "Fecha Transaccion" << " | "
              << std::setw(30) << "Detalle" << " | "
              << std::setw(14) << "Credito" << " | "
              << std::setw(14) << "Debito" << " | "
              << std::setw(15) << "Saldo Balance" << std::endl;
    std::cout << std::string(20, '-') << " | "
              << std::string(30, '-') << " | "
              << std::string(14, '-') << " | "
              << std::string(14, '-') << " | "
              << std::string(15, '-') << std::endl;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::cout << std::setw(20) << sqlite3_column_text(stmt, 0) << " | "
                  << std::setw(30) << sqlite3_column_text(stmt, 1) << " | "
                  << std::setw(14) << sqlite3_column_double(stmt, 2) << " | "
                  << std::setw(14) << sqlite3_column_double(stmt, 3) << " | "
                  << std::setw(15) << sqlite3_column_double(stmt, 4) << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error ejecutando la declaración SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    // Finaliza la declaración
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("base_de_datos.db", &db);

    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    } else {
        std::cout << "Base de datos abierta exitosamente" << std::endl;
    }

    // Ingresa el IdCliente para encontrar la info
    int IdCliente;
    std::cout << "Ingrese IdCliente: ";
    std::cin >> IdCliente;

    // Ingresa el rango de fechas
    std::string fechaInicio, fechaFin;
    std::cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
    std::cin >> fechaInicio;
    std::cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
    std::cin >> fechaFin;

    regresarDatosTransaccion(db, IdCliente, fechaInicio, fechaFin);

    sqlite3_close(db);
    return 0;
}
