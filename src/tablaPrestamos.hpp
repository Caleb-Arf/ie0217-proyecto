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

// Función para crear la tabla de préstamos si no existe
void crearTablaPrestamos(sqlite3* db) {
    std::string consulta = "CREATE TABLE IF NOT EXISTS tablaPrestamos ("
                           "IdCliente INTEGER,"
                           "IdPrestamo INTEGER PRIMARY KEY,"
                           "Cedula TEXT,"
                           "FechaCreacion TEXT,"
                           "Divisa TEXT,"
                           "FechaVencimiento TEXT,"
                           "TipoPrestamo TEXT,"
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

// Agrega datos en la tabla de prestamos
int insertarDatosPrestamos(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO tablaPrestamos (IdCliente, IdPrestamo, Cedula, FechaCreacion, Divisa, FechaVencimiento, TipoPrestamo, MontoTotalPrestamo, TasaInteresP, CuotasTotales, CuotasPagadas, CuotasFaltantes, DiasVencidos, DiasVencimiento, SaldoPrestamo, MontoCuota) VALUES
        ('?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?'),
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
    std::string sql = "SELECT 2 FROM tablaPrestamos WHERE Cedula = ?;";
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
    std::string sql = "SELECT IdCliente, IdPrestamo, Cedula, FechaCreacion, Divisa, FechaVencimiento, TipoPrestamo, MontoTotalPrestamo, TasaInteresP, CuotasTotales, CuotasPagadas, CuotasFaltantes, DiasVencidos, DiasVencimiento, SaldoPrestamo, MontoCuota FROM tablaPrestamos WHERE Cedula = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, cedula.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string idCliente = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string IdPrestamo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string Cedula = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string FechaCreacion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string Divisa = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            std::string FechaVencimiento = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            std::string TipoPrestamo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            double MontoTotalPrestamo = sqlite3_column_double(stmt, 7);
            double TasaInteresP = sqlite3_column_double(stmt, 8);
            std::string CuotasTotales = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
            std::string CuotasPagadas = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
            std::string CuotasFaltantes = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));
            std::string DiasVencidos = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12));
            std::string DiasVencimiento = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 13));
            double SaldoPrestamo = sqlite3_column_double(stmt, 14);
            double MontoCuota = sqlite3_column_double(stmt, 15);
            std::cout << "idCliente: " << idCliente << "\nIdPrestamo: " << IdPrestamo << "\nCedula: " << Cedula << "\nFechaCreacion: " << FechaCreacion << "\nDivisa: " << Divisa << "\nFechaVencimiento: " << 
            FechaVencimiento << "\nTipoPrestamo:" << TipoPrestamo << "\nMontoTotalPrestamo:" << MontoTotalPrestamo << "\nTasaInteresP:" << TasaInteresP << "\nCuotasTotales:" << CuotasTotales <<
            "\nCuotasPagadas:" << CuotasPagadas << "\nCuotasFaltantes: " << CuotasFaltantes << "\nDiasVencidos: " << DiasVencidos << "\nDiasVencimiento: " << DiasVencimiento << 
            "\nSaldoPrestamo: " << SaldoPrestamo << "\nMontoCuota: " << MontoCuota << std::endl;
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

    crearTablaPrestamos(db);

    sqlite3_close(db);
    return 0;
}




