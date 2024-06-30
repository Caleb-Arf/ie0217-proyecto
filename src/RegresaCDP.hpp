/**
 * @file RegresaCDP.hpp
 * @brief Archivo que contiene la función para recuperar datos de CDP de una base de datos SQLite.
 */

#ifndef REGRESACDP_HPP
#define REGRESACDP_HPP

#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <iomanip>
#include <sstream>
#include <cmath>

/**
 * @brief Función para recibir datos del CDP de un cliente específico basado en la cédula.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param cedula Cédula del cliente cuya información de CDP se desea recuperar.
 */
void regresarDatosCDP(sqlite3* db, int cedula) {
    const char* sql = "SELECT IdCDP, IdCliente, FechaCreacionCDP, DivisaCDP, FechaVencimientoCDP, MontoCDP FROM tablaCDP WHERE Cedula = ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparando declaración SQL: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Conecta cédula a parámetros
    sqlite3_bind_int(stmt, 1, cedula);

    // Imprime la información en tabla
    std::cout << std::setw(10) << std::setfill(' ') << "IdCDP" << " | "
              << std::setw(10) << "IdCliente" << " | "
              << std::setw(16) << "FechaCreacionCDP" << " | "
              << std::setw(10) << "DivisaCDP" << " | "
              << std::setw(18) << "FechaVencimientoCDP" << " | "
              << std::setw(10) << "MontoCDP" << " | " << std::endl;
    std::cout << std::string(10, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(16, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(19, '-') << " | "
              << std::string(10, '-') << " | " << std::endl;

    bool foundData = false;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        foundData = true;
        std::cout << std::setw(10) << sqlite3_column_text(stmt, 0) << " | "
                  << std::setw(10) << sqlite3_column_text(stmt, 1) << " | "
                  << std::setw(16) << sqlite3_column_text(stmt, 2) << " | "
                  << std::setw(10) << sqlite3_column_text(stmt, 3) << " | "
                  << std::setw(19) << sqlite3_column_text(stmt, 4) << " | "
                  << std::setw(10) << sqlite3_column_double(stmt, 5) << " | " << std::endl;
    }

    if (!foundData) {
        std::cout << "No se encontraron datos para la cédula especificada." << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error ejecutando la declaración SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    // Finaliza la declaración
    sqlite3_finalize(stmt);
}
#endif // REGRESACDP_HPP