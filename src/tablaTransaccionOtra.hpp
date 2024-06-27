#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

// Función para ejecutar consultas SQL
int ejecutarSQLTransacciones(sqlite3* db, const std::string& consulta) {
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
    std::cout << std::setw(14) << "IdTransaccion" << " | "
              << std::setw(10) << "IdCliente" << " | "
              << std::setw(7) << "Cedula" << " | "
              << std::setw(12) << "FechaTransaccion" << " | "
              << std::setw(5) << "Hora" << " | "
              << std::setw(13) << "SaldoBalance" << " | "
              << std::setw(6) << "Detalle" << " | "
              << std::setw(6) << "Credito" << " | "
              << std::setw(7) << "Debito" << " | "
              << std::setw(6) << "CuentaOrigen" << " | "
              << std::setw(6) << "CuentaDestino" << std::endl;
    std::cout << std::string(14, '-') << " | " //1
              << std::string(10, '-') << " | " //2
              << std::string(07, '-') << " | " //3
              << std::string(16, '-') << " | " //4
              << std::string(5, '-') << " | " //5
              << std::string(13, '-') << " | " //6
              << std::string(7, '-') << " | " //7
              << std::string(7, '-') << " | " //8
              << std::string(7, '-') << " | " //9
              << std::string(12, '-') << " | " //10
              << std::string(14, '-') << std::endl; //11
}

// Crea la tabla transacciones 
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

// Inserta datos en la tabla Tasas CDP
void insertarTransacciones(sqlite3 *db) {
    const char *sql_insert_data = 
        "INSERT INTO tablaTransacciones (IdTransaccion, IdCliente, Cedula, FechaTransaccion, Hora, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino) VALUES"
        "(1, 2, 3, 4, 5, 6, '7', 8, 9, 10, 11);";
    
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
    int rc = sqlite3_open("test.db", &db);

    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    } else {
        std::cout << "Base de datos abierta exitosamente" << std::endl;
    }

    crearTablaTransacciones(db);
    insertarTransacciones(db);
    printTableHeadersTransaccion();
    mostrarTablaTransacciones(db);

    sqlite3_close(db);
    return 0;
}
*/
