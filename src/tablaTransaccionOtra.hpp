#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

// Función para ejecutar consultas SQL
int ejecutarSqlTransaccion(sqlite3* db, const std::string& consulta) {
    char* mensajeError = nullptr;
    int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &mensajeError);
    if (resultado != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }
    return resultado;
}


// Callback para impresion de tabla de transacciones
static int callbackT(void *data, int argc, char **argv, char **azColName) {
    // Imprime los datos de la tabla.
    std::cout << std::setw(10) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(10) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(15) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(12) << (argv[3] ? argv[3] : "NULL") << " | "
              << std::setw(10) << (argv[4] ? argv[4] : "NULL") << " | "
              << std::setw(10) << (argv[5] ? argv[5] : "NULL") << " | "
              << std::setw(15) << (argv[6] ? argv[6] : "NULL") << " | "
              << std::setw(12) << (argv[7] ? argv[7] : "NULL") << " | "
              << std::setw(15) << (argv[8] ? argv[8] : "NULL") << " | "
              << std::setw(12) << (argv[9] ? argv[9] : "NULL") << " | "
              << std::setw(12) << (argv[10] ? argv[10] : "NULL") << std::endl;
    return 0;
}

//Imprime encabezados
void printTableHeadersTransaccion() {
    std::cout << std::setw(40) << std::setfill(' ') << "tablaTransacciones" << std::endl << std::endl;
    std::cout << std::setw(10) << "IdCliente" << " | "
              << std::setw(15) << "Cedula" << " | "
              << std::setw(12) << "FechaTransaccion" << " | "
              << std::setw(12) << "Hora" << " | "
              << std::setw(12) << "IdTransaccion" << " | "
              << std::setw(15) << "SaldoBalance" << " | "
              << std::setw(40) << "Detalle" << " | "
              << std::setw(15) << "Credito" << " | "
              << std::setw(15) << "Debito" << " | "
              << std::setw(15) << "CuentaOrigen" << " | "
              << std::setw(15) << "CuentaDestino" << std::endl;
    std::cout << std::string(10, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(12, '-') << std::endl;
}

// Crea la tabla transacciones 
void crearTablaTransacciones(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tablaTransacciones ("
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
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error creando la tabla: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Inserta datos en la tabla Tasas CDP
void insertarTransacciones(sqlite3 *db) {
    const char *sql_insert_data = 
        "INSERT INTO tablaTransacciones (IdCliente, Cedula, FechaTransaccion, Hora, IdTransaccion, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino) VALUES"
        "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?),";
    
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_insert_data, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error insertando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla transacciones
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

// Elimina la tabla Tasas  CDP
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

/*
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
*/