#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

// Función para ejecutar consultas SQL
int ejecutarSQLCDP(sqlite3* db, const std::string& consulta) {
    char* mensajeError = nullptr;
    int resultado = sqlite3_exec(db, consulta.c_str(), nullptr, nullptr, &mensajeError);
    if (resultado != SQLITE_OK) {
        std::cerr << "Error ejecutando SQL: " << mensajeError << std::endl;
        sqlite3_free(mensajeError);
    }
    return resultado;
}

// Callback para impresión de tabla de CDP
static int callbackC(void *data, int argc, char **argv, char **azColName) {
    std::cout << std::setw(7) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(10) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(10) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(14) << (argv[3] ? argv[3] : "NULL") << " | "
              << std::setw(10) << (argv[4] ? argv[4] : "NULL") << " | "
              << std::setw(17) << (argv[5] ? argv[5] : "NULL") << " | "
              << std::setw(10) << (argv[6] ? argv[6] : "NULL") << " | "
              << std::setw(16) << (argv[7] ? argv[7] : "NULL") << " | "
              << std::setw(14) << (argv[8] ? argv[8] : "NULL") << " | "
              << std::setw(16) << (argv[9] ? argv[9] : "NULL") << std::endl;
    return 0;
}

// Imprime encabezados
void printTableHeadersCDP() {
    std::cout << std::setw(70) << std::setfill(' ') << "tablaCDP" << std::endl << std::endl;
    std::cout << std::setw(7) << "IdCDP" << " | "
              << std::setw(10) << "Cedula" << " | "
              << std::setw(10) << "IdCliente" << " | "
              << std::setw(14) << "FechaCreacion2" << " | "
              << std::setw(10) << "Divisa2" << " | "
              << std::setw(17) << "FechaVencimiento2" << " | "
              << std::setw(10) << "MontoCDP" << " | "
              << std::setw(16) << "InteresesGanados" << " | "
              << std::setw(14) << "TasaInteresCDP" << " | "
              << std::setw(16) << "DiasFaltantesCDP" << std::endl;
    std::cout << std::string(7, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(14, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(17, '-') << " | "
              << std::string(10, '-') << " | "
              << std::string(16, '-') << " | "
              << std::string(14, '-') << " | "
              << std::string(16, '-') << std::endl;
}

// Crea la tabla CDP 
void crearTablaCDP(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tablaCDP ("
                           "IdCDP INTEGER PRIMARY KEY UNIQUE,"
                           "Cedula TEXT,"
                           "IdCliente INTEGER,"
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

// Inserta datos en la tabla CDP
void insertarCDP(sqlite3 *db) {
    const char *sql_insert_data = R"(
        INSERT INTO tablaCDP (IdCDP, Cedula, IdCliente, FechaCreacion2, Divisa2, FechaVencimiento2, MontoCDP, InteresesGanados, TasaInteresCDP, DiasFaltantesCDP) VALUES
        (401, '702890948', 2701006, '2019-12-14', 'Dolares', '2024-12-01', 1234.0, 50.0, 5.0, 160),
        (402, '702890950', 2701027, '2020-08-02', 'Dolares', '2024-12-01', 567.0, 50.0, 5.0, 80),
        (403, '702890951', 2701019, '2021-11-08', 'Dolares', '2024-12-01', 8920.0, 50.0, 5.0, 100),
        (404, '702890952', 1701014, '2022-10-20', 'Colones', '2024-12-01', 100.0, 50.0, 5.0, 1),
        (405, '504380806', 1504004, '2023-01-26', 'Colones', '2024-12-01', 1000.0, 50.0, 5.0, 120),
        (406, '901460040', 1203004, '2024-02-01', 'Colones', '2024-12-01', 5355.0, 50.0, 5.0, 10);
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

int main() {
    sqlite3* db;
    int rc = sqlite3_open("base_datos.db", &db);

    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    } else {
        std::cout << "Base de datos abierta exitosamente" << std::endl;
    }

    crearTablaCDP(db);
    insertarCDP(db);
    printTableHeadersCDP();
    mostrarTablaCDP(db);

    sqlite3_close(db);
    return 0;
}
