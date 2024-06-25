#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

// Función para ejecutar consultas SQL
int ejecutarSqlPrestamos(sqlite3* db, const std::string& consulta) {
    char* mensajeError = nullptr;
    int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &mensajeError);
    if (resultado != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }
    return resultado;
}


// Callback para impresion de tabla de préstamos
static int callbackP(void *data, int argc, char **argv, char **azColName) {
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
              << std::setw(12) << (argv[10] ? argv[10] : "NULL") << " | "
              << std::setw(12) << (argv[11] ? argv[11] : "NULL") << " | "
              << std::setw(12) << (argv[12] ? argv[12] : "NULL") << " | "
              << std::setw(12) << (argv[13] ? argv[13] : "NULL") << " | "
              << std::setw(12) << (argv[14] ? argv[14] : "NULL") << " | "
              << std::setw(12) << (argv[15] ? argv[15] : "NULL") << std::endl;
    return 0;
}

//Imprime encabezados
void printTableHeadersPrestamos() {
    std::cout << std::setw(40) << std::setfill(' ') << "tablaTransacciones" << std::endl << std::endl;
    std::cout << std::setw(10) << "IdCliente" << " | "
              << std::setw(15) << "IdPrestamo" << " | "
              << std::setw(12) << "Cedula" << " | "
              << std::setw(12) << "FechaCreacion" << " | "
              << std::setw(12) << "Divisa" << " | "
              << std::setw(15) << "FechaVencimiento" << " | "
              << std::setw(40) << "TipoPrestamo" << " | "
              << std::setw(15) << "MontoTotalPrestamo" << " | "
              << std::setw(15) << "TasaInteresP" << " | "
              << std::setw(15) << "CuotasTotales" << " | "
              << std::setw(15) << "CuotasPagadas" << " | "
              << std::setw(15) << "CuotasFaltantes" << " | "
              << std::setw(15) << "DiasVencidos" << " | "
              << std::setw(15) << "DiasVencimiento" << " | "
              << std::setw(15) << "SaldoPrestamo" << " | "
              << std::setw(15) << "MontoCuota" << std::endl;
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
              << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << std::endl;
}

// Crea la tabla prestamos 
void crearTablaPrestamos(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tablaPrestamos ("
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
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error creando la tabla: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Inserta datos en la tabla prestamos
void insertarPrestamos(sqlite3 *db) {
    const char *sql_insert_data = 
        "INSERT INTO tablaTransacciones (IdCliente, IdPrestamo, Cedula, FechaCreacion, Divisa, FechaVencimiento, TipoPrestamo, MontoTotalPrestamo, TasaInteresP, CuotasTotales, CuotasPagadas, CuotasFaltantes, DiasVencidos, DiasVencimiento, SaldoPrestamo, MontoCuota) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_insert_data, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error insertando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla prestamos
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

// Elimina la tabla prestamos
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
/*
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
*/
