/**
 * @file tablaPrestamosOtra.hpp
 * @brief Archivo que contiene las funciones para gestionar la tabla de préstamos en una base de datos SQLite.
 */

#ifndef TABLAPRESTAMOSOTRA_HPP
#define TABLAPRESTAMOSOTRA_HPP

#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

/**
 * @brief Función para ejecutar consultas SQL en la base de datos de préstamos.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param consulta Consulta SQL a ejecutar.
 * @return int Código de resultado de la ejecución de la consulta SQL.
 */
int ejecutarSQLPrestamos(sqlite3* db, const std::string& consulta) {
    char* mensajeError = nullptr;
    int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &mensajeError);
    if (resultado != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }
    return resultado;
}

/**
 * @brief Callback para la impresión de la tabla de préstamos.
 * 
 * @param data Puntero a los datos pasados al callback (no se usa en esta función).
 * @param argc Número de columnas en la fila.
 * @param argv Matriz de cadenas que contiene los valores de cada columna.
 * @param azColName Matriz de cadenas que contiene los nombres de las columnas.
 * @return int Código de resultado de la ejecución del callback.
 */
static int callbackP(void *data, int argc, char **argv, char **azColName) {
    std::cout << std::setw(10) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(10) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(7) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(13) << (argv[3] ? argv[3] : "NULL") << " | "
              << std::setw(8) << (argv[4] ? argv[4] : "NULL") << " | "
              << std::setw(17) << (argv[5] ? argv[5] : "NULL") << " | "
              << std::setw(12) << (argv[6] ? argv[6] : "NULL") << " | "
              << std::setw(19) << (argv[7] ? argv[7] : "NULL") << " | "
              << std::setw(14) << (argv[8] ? argv[8] : "NULL") << " | "
              << std::setw(14) << (argv[9] ? argv[9] : "NULL") << " | "
              << std::setw(14) << (argv[10] ? argv[10] : "NULL") << " | "
              << std::setw(15) << (argv[11] ? argv[11] : "NULL") << " | "
              << std::setw(12) << (argv[12] ? argv[12] : "NULL") << " | " 
              << std::setw(15) << (argv[13] ? argv[13] : "NULL") << " | "
              << std::setw(15) << (argv[14] ? argv[14] : "NULL") << " | "
              << std::setw(12) << (argv[15] ? argv[15] : "NULL") << std::endl;
    return 0;
}

/**
 * @brief Imprime los encabezados de la tabla de préstamos.
 */
void printTableHeadersPrestamos() {
    std::cout << std::setw(130) << std::setfill(' ') << "tablaPrestamos" << std::endl << std::endl;
    std::cout << std::setw(10) << "IdPrestamo" << " | "         // 1
              << std::setw(10) << "IdCliente" << " | "          // 2
              << std::setw(9) << "Cedula" << " | "              // 3
              << std::setw(13) << "FechaCreacion" << " | "      // 4
              << std::setw(8) << "Divisa" << " | "              // 5
              << std::setw(17) << "FechaVencimiento" << " | "   // 6
              << std::setw(12) << "TipoPrestamo" << " | "       // 7
              << std::setw(19) << "MontoTotalPrestamo" << " | " // 8
              << std::setw(14) << "TasaInteresP" << " | "       // 9
              << std::setw(14) << "CuotasTotales" << " | "      // 10
              << std::setw(14) << "CuotasPagadas" << " | "      // 11
              << std::setw(15) << "CuotasFaltantes" << " | "    // 12
              << std::setw(12) << "DiasVencidos" << " | "       // 13
              << std::setw(15) << "DiasVencimiento" << " | "    // 14
              << std::setw(15) << "SaldoPrestamo" << " | "      // 15
              << std::setw(12) << "MontoCuota" << std::endl;    // 16
    std::cout << std::string(10, '-') << " | "      // 1
              << std::string(10, '-') << " | "      // 2
              << std::string(9, '-') << " | "       // 3
              << std::string(13, '-') << " | "      // 4 
              << std::string(8, '-') << " | "       // 5
              << std::string(17, '-') << " | "      // 6
              << std::string(12, '-') << " | "      // 7
              << std::string(19, '-') << " | "      // 8
              << std::string(14, '-') << " | "      // 9
              << std::string(14, '-') << " | "      // 10
              << std::string(14, '-') << " | "      // 11
              << std::string(15, '-') << " | "      // 12
              << std::string(12, '-') << " | "      // 13
              << std::string(15, '-') << " | "      // 14
              << std::string(15, '-') << " | "      // 15
              << std::string(12, '-') << std::endl; // 16
}

/**
 * @brief Crea la tabla de préstamos en la base de datos.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void crearTablaPrestamos(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tablaPrestamos ("
                           "IdPrestamo INTEGER PRIMARY KEY,"
                           "IdCliente INTEGER,"
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
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error creando la tabla: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

/**
 * @brief Inserta datos en la tabla de préstamos.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void insertarPrestamos(sqlite3 *db) {
    const char *sql_insert_data = R"(
        INSERT INTO tablaPrestamos (IdPrestamo, IdCliente, Cedula, FechaCreacion, Divisa, FechaVencimiento, TipoPrestamo, MontoTotalPrestamo, TasaInteresP, CuotasTotales, CuotasPagadas, CuotasFaltantes, DiasVencidos, DiasVencimiento, SaldoPrestamo, MontoCuota)
        VALUES (5019283, 2701006, '702890948', '2019-12-14', 'Dolares', '2027-12-02', '090', 40000, 12.91, 96, 50, 46, 0, 1807, 35814.67, 554.37)
    )";

    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_insert_data, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al insertar datos en tablaPrestamos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos insertados correctamente en tablaPrestamos" << std::endl;
    }
}

/**
 * @brief Selecciona y muestra datos de la tabla de préstamos.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void mostrarTablaPrestamos(sqlite3 *db) {
    const char *sql = "SELECT * FROM tablaPrestamos";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql, callbackP, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error ejecutando la consulta: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

/**
 * @brief Elimina los datos de la tabla de préstamos.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void eliminarDatosPrestamos(sqlite3 *db) {
    const char *sql_delete_data = "DELETE FROM tablaPrestamos";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }
}

#endif //TABLAPRESTAMOSOTRA_HPP