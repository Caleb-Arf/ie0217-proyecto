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

// Función para crear la tabla de préstamos si no existe
void crearTablaPrestamos(sqlite3* db) {
    std::string consulta = "CREATE TABLE IF NOT EXISTS tablaPrestamos ("
                           "IdCliente INTEGER,"
                           "IdPrestamo INTEGER PRIMARY KEY,"
                           "FechaCreacion TEXT,"
                           "Divisa TEXT,"
                           "FechaVencimiento TEXT,"
                           "TipoPrestamo TEXT,"
                           "Cedula TEXT,"
                           "MontoTotalPrestamo REAL,"
                           "TasaInteresP REAL,"
                           "CuotasTotales INTEGER,"
                           "CuotasPagadas INTEGER,"
                           "CuotasFaltantes INTEGER,"
                           "DiasVencidos INTEGER,"
                           "DiasVencimiento INTEGER,"
                           "SaldoPrestamo REAL,"
                           "MontoCuota REAL"
                           ")";
    if (ejecutarSQL(db, consulta) != SQLITE_OK) {
        std::cerr << "Error creando la tabla de préstamos." << std::endl;
    } else {
        std::cout << "Tabla de préstamos creada exitosamente." << std::endl;
    }
}

int main() {
    sqlite3* db;
    int resultado = sqlite3_open("base_datos.db", &db); 

    if (resultado != SQLITE_OK) {
        std::cerr << "Error abriendo la base de datos." << std::endl;
        return resultado;
    }

    crearTablaPrestamos(db);

    sqlite3_close(db);
    return 0;
}
