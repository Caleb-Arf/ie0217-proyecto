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

// Función para crear la tabla de CDP si no existe
void crearTablaCDP(sqlite3* db) {
    std::string consulta = "CREATE TABLE IF NOT EXISTS tablaCDP ("
                           "IdCliente INTEGER,"
                           "Cedula TEXT,"
                           "IdCDP INTEGER PRIMARY KEY,"
                           "FechaCreacion2 TEXT,"
                           "Divisa2 TEXT,"
                           "FechaVencimiento2 TEXT,"
                           "MontoCDP REAL,"
                           "InteresesGanados REAL,"
                           "TasaInteresCDP REAL,"
                           "DiasFaltantesCDP INTEGER"
                           ")";
    if (ejecutarSQL(db, consulta) != SQLITE_OK) {
        std::cerr << "Error creando la tabla de CDP." << std::endl;
    } else {
        std::cout << "Tabla de CDP creada exitosamente." << std::endl;
    }
}


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


// Agrega datos en la tabla de cdp
int insertarDatosPrestamos(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO tablaCDP (IdCliente, Cedula, IdCDP, FechaCreacion2, Divisa2, FechaVencimiento2, MontoCDP, InteresesGanados, TasaInteresCDP, DiasFaltantesCDP) VALUES
        ('?', '?', '?', '?', '?', '?', '?', '?', '?', '?'),
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
    std::string sql = "SELECT 1 FROM tablaCDP WHERE Cedula = ?;";
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
void imprimirInfoCDP(sqlite3 *db, const std::string &cedula) {
    std::string sql = "SELECT IdCliente, Cedula, IdCDP, FechaCreacion2, Divisa2, FechaVencimiento2, MontoCDP, InteresesGanados, TasaInteresCDP, DiasFaltantesCDP WHERE Cedula = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, cedula.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string idCliente = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string Cedula = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string IdCDP = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string FechaCreacion2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string Divisa2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            std::string FechaVencimiento2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            double MontoCDP = sqlite3_column_double(stmt, 6);
            double InteresesGanados = sqlite3_column_double(stmt, 7);
            double TasaInteresCDP = sqlite3_column_double(stmt, 8);
            std::string DiasFaltantesCDP = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
            std::cout << "idCliente: " << idCliente << "\nCedula: " << Cedula << "\nIdCDP: " << IdCDP << "\nFechaCreacion2: " << FechaCreacion2 << "\nDivisa2: " << Divisa2 << "\nFechaVencimiento2: " << 
            FechaVencimiento2 << "\nMontoCDP:" << MontoCDP << "\nInteresesGanados:" << InteresesGanados << "\nTasaInteresCDP:" << TasaInteresCDP << "\nDiasFaltantesCDP:" << DiasFaltantesCDP << std::endl;
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

    crearTablaCDP(db);

    sqlite3_close(db);
    return 0;
}