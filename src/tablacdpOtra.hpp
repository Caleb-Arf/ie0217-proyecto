#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

// Función para ejecutar consultas SQL
int ejecutarSqlCdp(sqlite3* db, const std::string& consulta) {
    char* mensajeError = nullptr;
    int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &mensajeError);
    if (resultado != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }
    return resultado;
}


// Callback para impresion de tabla de cdp
static int callbackC(void *data, int argc, char **argv, char **azColName) {
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
              << std::setw(12) << (argv[9] ? argv[9] : "NULL") << std::endl;
    return 0;
}

//Imprime encabezados
void printTableHeadersCDP() {
    std::cout << std::setw(40) << std::setfill(' ') << "tablaCDP" << std::endl << std::endl;
    std::cout << std::setw(10) << "IdCliente" << " | "
              << std::setw(15) << "Cedula" << " | "
              << std::setw(12) << "IdCDP" << " | "
              << std::setw(12) << "FechaCreacion2" << " | "
              << std::setw(12) << "Divisa2" << " | "
              << std::setw(15) << "FechaVencimiento2" << " | "
              << std::setw(40) << "MontoCDP" << " | "
              << std::setw(40) << "InteresesGanados" << " | "
              << std::setw(40) << "TasaInteresCDP" << " | "
              << std::setw(15) << "DiasFaltantesCDP" << std::endl;
    std::cout << std::string(10, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << std::endl;
}

// Crea la tabla cdp 
void crearTablaCDP(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tablaCDP ("
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
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error creando la tabla: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Inserta datos en la tabla cdp
void insertarCDP(sqlite3 *db) {
    const char *sql_insert_data = 
        "INSERT INTO tablaCDP (IdCliente, Cedula, IdCDP, FechaCreacion2, Divisa2, FechaVencimiento2, MontoCDP, InteresesGanados, TasaInteresCDP, DiasFaltantesCDP) VALUES"
        "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?),";
    
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_insert_data, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error insertando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla CDP
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

// Elimina la tabla CDP
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
/*
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
*/
