#include <iostream>
#include <vector>
#include <sqlite3.h>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "tablaTransaccionOtra.hpp"

// Función para recibir datos de la transacción
void regresarDatosTransaccion(sqlite3* db, int idTransaccion) {
  const char* sql = "SELECT FechaTransaccion, Detalle, Credito, Debito, SaldoBalance FROM tablaTransacciones WHERE IdTransaccion = ?";
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Error preparando declaración SQL: " << sqlite3_errmsg(db) << std::endl;
    return;
  }

  // Conecta IdTransaccion a parámetro
  sqlite3_bind_int(stmt, 1, idTransaccion);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW) {
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

    std::cout << std::setw(20) << sqlite3_column_text(stmt, 0) << " | "
              << std::setw(30) << sqlite3_column_text(stmt, 1) << " | "
              << std::setw(14) << sqlite3_column_double(stmt, 2) << " | "
              << std::setw(14) << sqlite3_column_double(stmt, 3) << " | "
              << std::setw(15) << sqlite3_column_double(stmt, 4) << std::endl;
  } else {
    std::cout << "No se encontró la transacción con IdTransaccion: " << idTransaccion << std::endl;
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

  // Ingresa el IdTransacción para encontrar la info
  int idTransaccion;
  std::cout << "Ingrese IdTransaccion: ";
  std::cin >> idTransaccion;

  regresarDatosTransaccion(db, idTransaccion);

  sqlite3_close(db);
  return 0;
}
