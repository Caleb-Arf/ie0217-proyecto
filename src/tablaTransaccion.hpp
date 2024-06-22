#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>
#include <sqlite3.h>
#include <cstdlib> // Para generar numeros aleatorios
#include <cstring>

// Función para ejecutar consultas SQL
int ejecutarSQL(sqlite3* db, const std::string& consulta) {
    char* mensajeError = nullptr;
    int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &mensajeError);
    if (resultado != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }
    return resultado;
}

// Función para crear la tabla de transacciones si no existe
void crearTablaTransacciones(sqlite3* db) {
    std::string consulta = "CREATE TABLE IF NOT EXISTS tablaTransacciones ("
                           "IdCliente INTEGER,"
                           "Cedula TEXT,"
                           "FechaTransaccion TEXT,"
                           "Hora TEXT,"
                           "IdTransaccion INTEGER PRIMARY KEY,"
                           "SaldoBalance REAL,"
                           "Detalle TEXT,"
                           "Credito REAL,"
                           "Debito REAL,"
                           "CuentaOrigen TEXT,"
                           "CuentaDestino TEXT"
                           ")";
    if (ejecutarSQL(db, consulta) != SQLITE_OK) {
        std::cerr << "Error creando la tabla de transacciones." << std::endl;
    } else {
        std::cout << "Tabla de transacciones creada exitosamente." << std::endl;
    }
}

// Agrega datos en la tabla de transaccion
int insertarDatosTransaccion(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO tablaTransacciones (IdCliente, Cedula, FechaTransaccion, Hora, IdTransaccion, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino) VALUES
        ('?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?'),
    )";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    return rc;
}

// Verifica si la cedula existe en la base de datos
bool existeCedula(sqlite3 *db, const std::string &cedula) {
    std::string sql = "SELECT 1 FROM tablaTransacciones WHERE Cedula = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, cedula.c_str(), -1, SQLITE_STATIC);
    bool existe = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return existe;
}

// Imprime la informacion de transacción
void imprimirInfoTransaccion(sqlite3 *db, const std::string &cedula) {
    std::string sql = "SELECT IdCliente, Cedula, FechaTransaccion, Hora, IdTransaccion, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino FROM tablaTransacciones WHERE Cedula = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, cedula.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string idCliente = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string cedula = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string fechaTransaccion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string hora = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string idTransaccion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            double saldoBalance = sqlite3_column_double(stmt, 5);
            std::string detalle = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            std::string credito = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
            std::string debito = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
            std::string cuentaOrigen = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
            std::string cuentaDestino = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
            std::cout << "IdCliente: " << idCliente << "\nCedula: " << cedula << "\nFechaTransaccion: " << fechaTransaccion << "\nHora: " << hora << "\nIdTransaccion: " << idTransaccion << "\nSaldoBalance: " << saldoBalance << "\nDetalle: " << 
            detalle << "\nCredito:" << credito << "\nDebito:" << debito << "\nCuenta Origen:" << cuentaOrigen << "\nCuenta Destino:" << cuentaDestino << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }
}

int main() {
    sqlite3* db;
    int resultado = sqlite3_open("base_datos.db", &db); // Nombre de la base de datos

    if (resultado != SQLITE_OK) {
        std::cerr << "Error abriendo la base de datos." << std::endl;
        return resultado;
    }

    crearTablaTransacciones(db);

    sqlite3_close(db);
    return 0;
}
















