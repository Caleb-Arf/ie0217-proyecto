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


// Callback para impresion de tabla de cdp
static int callbackC(void *data, int argc, char **argv, char **azColName) {
    // Imprime los datos de la tabla.
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

//Imprime encabezados
void printTableHeadersCDP() {
    std::cout << std::setw(70) << std::setfill(' ') << "tablaCDP" << std::endl << std::endl;
    std::cout << std::setw(7) << "IdCDP" << " | "
              << std::setw(10) << "Cedula" << " | "
              << std::setw(10) << "IdCliente" << " | "
              << std::setw(10) << "FechaCreacion2" << " | "
              << std::setw(10) << "Divisa2" << " | "
              << std::setw(11) << "FechaVencimiento2" << " | "
              << std::setw(10) << "MontoCDP" << " | "
              << std::setw(10) << "InteresesGanados" << " | "
              << std::setw(8) << "TasaInteresCDP" << " | "
              << std::setw(10) << "DiasFaltantesCDP" << std::endl;
    std::cout << std::string(7, '-') << " | " //1
              << std::string(10, '-') << " | " //2
              << std::string(10, '-') << " | " //3
              << std::string(14, '-') << " | " //4
              << std::string(10, '-') << " | " //5
              << std::string(17, '-') << " | " //6
              << std::string(10, '-') << " | " //7
              << std::string(16, '-') << " | " //8
              << std::string(14, '-') << " | " //9
              << std::string(16, '-') << std::endl; //10
}

// Crea la tabla cdp 
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

// Inserta datos en la tabla cdp
void insertarCDP(sqlite3 *db) {
    const char *sql_insert_data = R"(
        INSERT INTO tablaCDP (IdCDP, Cedula, IdCliente, FechaCreacion2, Divisa2, FechaVencimiento2, MontoCDP, InteresesGanados, TasaInteresCDP, DiasFaltantesCDP) VALUES
        (1, '12345678', 7, '2019-12-14', 'USD', '2024-12-01', 1234.0, 50.0, 5.0, 160),
        (2, '12345679', 8, '2020-08-02', 'Colones', '2024-12-01', 567.0, 50.0, 5.0, 80),
        (3, '12345677', 9, '2021-11-08', 'Colones', '2024-12-01', 8920.0, 50.0, 5.0, 100),
        (4, '12345676', 10, '2022-10-20', 'USD', '2024-12-01', 100.0, 50.0, 5.0, 01),
        (5, '12345675', 11, '2023-01-26', 'Colones', '2024-12-01', 1000.0, 50.0, 5.0, 120),
        (6, '12345674', 12, '2024-02-01', 'USD', '2024-12-01', 5355.0, 50.0, 5.0, 10);
    )";
    
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
    int rc = sqlite3_open("test.db", &db);

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
*/