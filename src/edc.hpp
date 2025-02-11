/**
 * @file edc.hpp
 * @brief Archivo que contiene la función para recuperar datos de transacciones de una base de datos SQLite.
 */

#ifndef EDC_HPP
#define EDC_HPP

#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <iomanip>
#include <sstream>
#include <cmath>

/**
 * @brief Función para recibir datos de la transacción de un cliente específico en un rango de fechas.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param IdCliente ID del cliente cuya transacción se desea recuperar.
 * @param fechaInicio Fecha de inicio del rango en formato "YYYY-MM-DD".
 * @param fechaFin Fecha de fin del rango en formato "YYYY-MM-DD".
 */
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

    bool foundData = false;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        foundData = true;
        std::cout << std::setw(20) << sqlite3_column_text(stmt, 0) << " | "
                  << std::setw(30) << sqlite3_column_text(stmt, 1) << " | "
                  << std::setw(14) << sqlite3_column_double(stmt, 2) << " | "
                  << std::setw(14) << sqlite3_column_double(stmt, 3) << " | "
                  << std::setw(15) << sqlite3_column_double(stmt, 4) << std::endl;
    }

    if (!foundData) {
        std::cout << "No se encontraron datos para el IdCliente especificado." << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error ejecutando la declaración SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    // Finaliza la declaración
    sqlite3_finalize(stmt);
}
#endif // EDC_HPP