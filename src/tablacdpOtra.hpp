/**
 * @file tablacdpOtra.hpp
 * @brief Header file que interactúa con una base de datos SQLite para gestionar la tabla CDP.
 */

#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath> 
#include <vector>

/**
 * @brief Función para ejecutar consultas SQL.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param consulta Consulta SQL a ejecutar.
 * @return int Código de resultado de la ejecución de la consulta SQL.
 */
int ejecutarSQLCDP(sqlite3* db, const std::string& consulta) {
    char* mensajeError = nullptr;
    int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &mensajeError);
    if (resultado != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }
    return resultado;
}

/**
 * @brief Callback para la impresión de la tabla CDP.
 * 
 * @param data Puntero a los datos pasados al callback (no se usa en esta función).
 * @param argc Número de columnas en la fila.
 * @param argv Matriz de cadenas que contiene los valores de cada columna.
 * @param azColName Matriz de cadenas que contiene los nombres de las columnas.
 * @return int Código de resultado de la ejecución del callback.
 */
static int callbackC(void *data, int argc, char **argv, char **azColName) {
    std::cout << std::setw(7) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(10) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(10) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(16) << (argv[3] ? argv[3] : "NULL") << " | "
              << std::setw(10) << (argv[4] ? argv[4] : "NULL") << " | "
              << std::setw(19) << (argv[5] ? argv[5] : "NULL") << " | "
              << std::setw(10) << (argv[6] ? argv[6] : "NULL") << " | "
              << std::setw(16) << (argv[7] ? argv[7] : "NULL") << " | "
              << std::setw(14) << (argv[8] ? argv[8] : "NULL") << " | "
              << std::setw(17) << (argv[9] ? argv[9] : "NULL") << " | "
              << std::setw(8) << (argv[10] ? argv[10] : "NULL") << " | " << std::endl;
    return 0;
}

/**
 * @brief Imprime los encabezados de la tabla CDP.
 */
void printTableHeadersCDP() {
    std::cout << std::setw(85) << std::setfill(' ') << "tablaCDP" << std::endl << std::endl;
    std::cout << std::setw(7) << "IdCDP" << " | "                //1
              << std::setw(10) << "Cedula" << " | "              //2
              << std::setw(10) << "IdCliente" << " | "           //3
              << std::setw(14) << "FechaCreacionCDP" << " | "    //4
              << std::setw(10) << "DivisaCDP" << " | "           //5
              << std::setw(17) << "FechaVencimientoCDP" << " | " //6
              << std::setw(10) << "MontoCDP" << " | "            //7
              << std::setw(16) << "InteresesGanados" << " | "    //8
              << std::setw(14) << "TasaInteresCDP" << " | "      //9
              << std::setw(17) << "MesesFaltantesCDP" << " | "   //10
              << std::setw(8) << "Plazo" << " | " << std::endl;  //11
    std::cout << std::string(7, '-') << " | "               //1
              << std::string(10, '-') << " | "              //2
              << std::string(10, '-') << " | "              //3
              << std::string(16, '-') << " | "              //4
              << std::string(10, '-') << " | "              //5
              << std::string(19, '-') << " | "              //6
              << std::string(10, '-') << " | "              //7
              << std::string(16, '-') << " | "              //8
              << std::string(14, '-') << " | "              //9
              << std::string(17, '-') << " | "              //10
              << std::string(8, '-') << " | " << std::endl; //11
}

/**
 * @brief Crea la tabla CDP en la base de datos.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void crearTablaCDP(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tablaCDP ("
                           "IdCDP INTEGER PRIMARY KEY UNIQUE,"
                           "Cedula TEXT,"
                           "IdCliente INTEGER,"
                           "FechaCreacionCDP TEXT,"
                           "DivisaCDP TEXT,"
                           "FechaVencimientoCDP TEXT,"
                           "MontoCDP REAL,"
                           "InteresesGanados REAL,"
                           "TasaInteresCDP REAL,"
                           "MesesFaltantesCDP INTEGER,"
                           "Plazo TEXT"
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
 * @brief Inserta datos en la tabla CDP.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void insertarCDP(sqlite3 *db) {
    const char *sql_insert_data = R"(
        INSERT INTO tablaCDP (IdCDP, Cedula, IdCliente, FechaCreacionCDP, DivisaCDP, FechaVencimientoCDP, MontoCDP, InteresesGanados, TasaInteresCDP, MesesFaltantesCDP, Plazo) VALUES
        (7000001, '702890948', 2701006, '2023-11-30', 'Dolares', '2024-05-30', 15000.0, 1500.0, 0.1, 0, '1-6'),
        (7000002, '702890950', 2701027, '2023-08-02', 'Dolares', '2024-09-02', 10000.0, 1800.0, 0.18, 0, '7-13'),
        (7000003, '702890951', 2701019, '2023-11-08', 'Dolares', '2025-07-08', 13000.0, 7800.0, 0.6, 0, '14-20'),
        (7000004, '702890952', 1701014, '2022-10-20', 'Colones', '2025-03-20', 350000.0, 423500.0, 1.21, 0, '21-29'),
        (7000005, '504380806', 1504004, '2021-01-26', 'Colones', '2025-12-26', 300000.0, 933000.0, 3.11, 0, '30-59'),
        (7000006, '901460040', 1203004, '2020-02-01', 'Colones', '2026-10-01', 320000.0, 1136000.0, 3.55, 0, '60-80');
    )";
    
    char *err_msg = nullptr;
    int rc;

    // Eliminar datos existentes
    const char *sql_delete_data = "DELETE FROM tablaCDP";
    rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }

    // Insertar nuevos datos
    rc = sqlite3_exec(db, sql_insert_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error insertando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

/**
 * @brief Selecciona y muestra datos de la tabla CDP.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void mostrarTablaCDP(sqlite3 *db) {
    const char *sql = "SELECT * FROM tablaCDP";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql, callbackC, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error ejecutando la consulta: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

/**
 * @brief Elimina los datos de la tabla CDP.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void eliminarDatosCDP(sqlite3 *db) {
    const char *sql_delete_data = "DELETE FROM tablaCDP";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }
}
