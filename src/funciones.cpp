#include "funciones.hpp"

// Función para obtener el salario de un cliente por su ID
double obtenerBalance(sqlite3* db, int idCliente) {
    std::string sql = "SELECT Balance FROM Clientes WHERE IdCliente = " + std::to_string(idCliente) + ";";
    sqlite3_stmt *stmt;
    double balance = -1;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            balance = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error en la preparación de la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    return balance;
}

// Función para actualizar el salario de un cliente por su ID
bool actualizarBalance(sqlite3* db, int idCliente, double nuevoBalance) {
    std::string sql = "UPDATE Clientes SET Balance = " + std::to_string(nuevoBalance) + " WHERE IdCliente = " + std::to_string(idCliente) + ";";
    char *errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al actualizar el salario: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}
