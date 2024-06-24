#include <iostream>
#include <string>
#include <sqlite3.h> 

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
