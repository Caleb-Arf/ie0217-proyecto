/**
 * @file tablaTransaccionOtra.hpp
 * @brief Archivo que contiene las funciones para gestionar la tabla de transacciones en una base de datos SQLite.
 */

#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

/**
 * @brief Función para ejecutar consultas SQL en la base de datos de transacciones.
 * 
 * @param db Puntero a la base de datos SQLite.
 * @param consulta Consulta SQL a ejecutar.
 * @return int Código de resultado de la ejecución de la consulta SQL.
 */
int ejecutarSQLTransacciones(sqlite3* db, const std::string& consulta) {
    char* mensajeError = nullptr;
    int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &mensajeError);
    if (resultado != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }
    return resultado;
}

/**
 * @brief Callback para la impresión de la tabla de transacciones.
 * 
 * @param data Puntero a los datos pasados al callback (no se usa en esta función).
 * @param argc Número de columnas en la fila.
 * @param argv Matriz de cadenas que contiene los valores de cada columna.
 * @param azColName Matriz de cadenas que contiene los nombres de las columnas.
 * @return int Código de resultado de la ejecución del callback.
 */
static int callbackT(void *data, int argc, char **argv, char **azColName) {
    std::cout << std::setw(14) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(10) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(11) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(16) << (argv[3] ? argv[3] : "NULL") << " | "
              << std::setw(12) << (argv[4] ? argv[4] : "NULL") << " | "
              << std::setw(17) << (argv[5] ? argv[5] : "NULL") << " | "
              << std::setw(25) << (argv[6] ? argv[6] : "NULL") << " | "
              << std::setw(19) << (argv[7] ? argv[7] : "NULL") << " | "
              << std::setw(12) << (argv[8] ? argv[8] : "NULL") << " | "
              << std::setw(12) << (argv[9] ? argv[9] : "NULL") << " | "
              << std::setw(14) << (argv[10] ? argv[10] : "NULL") << " | " << std::endl;
    return 0;
}

/**
 * @brief Imprime los encabezados de la tabla de transacciones.
 */
void printTableHeadersTransacciones() {
    std::cout << std::setw(105) << std::setfill(' ') << "tablaTransacciones" << std::endl << std::endl;
    std::cout << std::setw(14) << "IdTransaccion" << " | "               // 1
              << std::setw(10) << "IdCliente" << " | "                   // 2
              << std::setw(11) << "Cedula" << " | "                      // 3
              << std::setw(16) << "FechaTransaccion" << " | "            // 4 
              << std::setw(12) << "Hora" << " | "                        // 5
              << std::setw(17) << "SaldoBalance" << " | "                // 6
              << std::setw(25) << "Detalle" << " | "                     // 7
              << std::setw(19) << "Credito" << " | "                     // 8
              << std::setw(12) << "Debito" << " | "                      // 9
              << std::setw(12) << "CuentaOrigen" << " | "                // 10
              << std::setw(14) << "CuentaDestino" << " | " << std::endl; // 11
    std::cout << std::string(14, '-') << " | "               // 1
              << std::string(10, '-') << " | "               // 2
              << std::string(11, '-') << " | "               // 3
              << std::string(16, '-') << " | "               // 4
              << std::string(12, '-') << " | "               // 5
              << std::string(17, '-') << " | "               // 6
              << std::string(25, '-') << " | "               // 7
              << std::string(19, '-') << " | "               // 8
              << std::string(12, '-') << " | "               // 9
              << std::string(12, '-') << " | "               // 10
              << std::string(14, '-') << " | " << std::endl; // 11
}

/**
 * @brief Crea la tabla de transacciones en la base de datos.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void crearTablaTransacciones(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tablaTransacciones ("
                           "IdTransaccion INTEGER PRIMARY KEY,"
                           "IdCliente INTEGER,"
                           "Cedula TEXT,"
                           "FechaTransaccion TEXT,"
                           "Hora TEXT,"
                           "SaldoBalance REAL,"
                           "Detalle TEXT,"
                           "Credito REAL,"
                           "Debito REAL,"
                           "CuentaOrigen TEXT,"
                           "CuentaDestino TEXT"
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
 * @brief Inserta datos en la tabla de transacciones.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void insertarTransacciones(sqlite3 *db) {
    const char *sql_insert_data = R"(
        INSERT INTO tablaTransacciones (IdTransaccion, IdCliente, Cedula, FechaTransaccion, Hora, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino) VALUES
        (3000041, 2701006, '702890948', '2017-01-11', '21:31:19', 87354.22, 'Transferencia realizada', 0, 300, 'Dolares', 'Dolares'),
        (3000042, 2701027, '702890950', '2017-02-12', '21:31:19', 21285.98, 'Transferencia recibida', 300, 0, 'Dolares', 'Dolares'),
        (3006334, 1203004, '901460040', '2018-03-13', '23:42:08', 4371687.12, 'Transferencia realizada', 0, 50300, 'Colones', 'Dolares'),
        (3006335, 2701006, '702890948', '2018-04-14', '23:42:08', 87449.12566037737, 'Transferencia recibida', 94.90566037735849, 0, 'Colones', 'Dolares'),
        (3018467, 1701014, '702890952', '2019-05-15', '23:41:05', 1410987.45, 'Transferencia realizada', 0, 40000, 'Colones', 'Colones'),
        (3018468, 1504004, '504380806', '2019-06-16', '23:41:05', 694987.33, 'Transferencia recibida', 40000, 0, 'Colones', 'Colones'),
        (3026500, 2701027, '702890950', '2020-07-17', '23:42:29', 20885.98, 'Transferencia realizada', 0, 400, 'Dolares', 'Colones'),
        (3026501, 1504004, '504380806', '2020-18-18', '23:42:29', 906987.33, 'Transferencia recibida', 212000, 0, 'Dolares', 'Colones');
    )";
   
    char *err_msg = nullptr;
    int rc;

    // Eliminar datos existentes
    const char *sql_delete_data = "DELETE FROM tablaTransacciones";
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
 * @brief Selecciona y muestra datos de la tabla de transacciones.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void mostrarTablaTransacciones(sqlite3 *db) {
    const char *sql = "SELECT * FROM tablaTransacciones";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql, callbackT, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error ejecutando la consulta: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

/**
 * @brief Elimina los datos de la tabla de transacciones.
 * 
 * @param db Puntero a la base de datos SQLite.
 */
void eliminarDatosTransacciones(sqlite3 *db) {
    const char *sql_delete_data = "DELETE FROM tablaTransacciones";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }
}
