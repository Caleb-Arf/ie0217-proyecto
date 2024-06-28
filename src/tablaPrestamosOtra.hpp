#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

// Función para ejecutar consultas SQL
int ejecutarSQLPrestamos(sqlite3* db, const std::string& consulta) {
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
              << std::setw(07) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(13) << (argv[3] ? argv[3] : "NULL") << " | "
              << std::setw(8) << (argv[4] ? argv[4] : "NULL") << " | "
              << std::setw(17) << (argv[5] ? argv[5] : "NULL") << " | "
              << std::setw(12) << (argv[6] ? argv[6] : "NULL") << " | "
              << std::setw(19) << (argv[7] ? argv[7] : "NULL") << " | "
              << std::setw(14) << (argv[8] ? argv[8] : "NULL") << " | "
              << std::setw(14) << (argv[9] ? argv[9] : "NULL") << " | "
              << std::setw(14) << (argv[10] ? argv[10] : "NULL") << " | "
              << std::setw(15) << (argv[11] ? argv[11] : "NULL") << " | "
              << std::setw(12) << (argv[12] ? argv[12] : "NULL") << " | " //diasvencidos
              << std::setw(15) << (argv[13] ? argv[13] : "NULL") << " | "
              << std::setw(15) << (argv[14] ? argv[14] : "NULL") << " | "
              << std::setw(12) << (argv[15] ? argv[15] : "NULL") << std::endl;
    return 0;
}

//Imprime encabezados
void printTableHeadersPrestamos() {
    std::cout << std::setw(130) << std::setfill(' ') << "tablaTransacciones" << std::endl << std::endl;
    std::cout << std::setw(10) << "IdPrestamo" << " | " //1
              << std::setw(10) << "IdCliente" << " | " //2
              << std::setw(9) << "Cedula" << " | " //3
              << std::setw(13) << "FechaCreacion" << " | " //4
              << std::setw(8) << "Divisa" << " | " //5
              << std::setw(17) << "FechaVencimiento" << " | " //5
              << std::setw(12) << "TipoPrestamo" << " | " //6
              << std::setw(19) << "MontoTotalPrestamo" << " | " //7
              << std::setw(14) << "TasaInteresP" << " | " //8
              << std::setw(14) << "CuotasTotales" << " | " //9
              << std::setw(14) << "CuotasPagadas" << " | " //10
              << std::setw(15) << "CuotasFaltantes" << " | " //11
              << std::setw(9) << "DiasVencidos" << " | " //12
              << std::setw(12) << "DiasVencimiento" << " | " //13
              << std::setw(15) << "SaldoPrestamo" << " | " //14
              << std::setw(12) << "MontoCuota" << std::endl; //15
    std::cout << std::string(10, '-') << " | " //1
              << std::string(10, '-') << " | " //2
              << std::string(9, '-') << " | " //3
              << std::string(13, '-') << " | " //4 
              << std::string(8, '-') << " | " //5
              << std::string(17, '-') << " | " //6
              << std::string(12, '-') << " | " //7
              << std::string(19, '-') << " | " //8
              << std::string(14, '-') << " | " //9
              << std::string(14, '-') << " | " //10
              << std::string(14, '-') << " | " //11
              << std::string(15, '-') << " | " //12
              << std::string(12, '-') << " | " //13
              << std::string(15, '-') << " | " //14
              << std::string(15, '-') << " | " //15
              << std::string(12, '-') << std::endl;
}

// Crea la tabla prestamos 
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

// Inserta datos en la tabla Prestamos
void insertarPrestamos(sqlite3 *db) {
    const char *sql_insert_data = R"(
        INSERT INTO tablaPrestamos (IdPrestamo, IdCliente, Cedula, FechaCreacion, Divisa, FechaVencimiento, TipoPrestamo, MontoTotalPrestamo, TasaInteresP, CuotasTotales, CuotasPagadas, CuotasFaltantes, DiasVencidos, DiasVencimiento, SaldoPrestamo, MontoCuota) VALUES
        (501, 2701006, '702890948', '2019-12-14', 'Dolares', '2024-12-02', 'H01', 1, 1, 1, 1, 1, 1, 1, 1, 1),
        (506, 1203004, '901460040', '2024-02-01', 'Colones', '2024-12-01', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0);
    )";
    
    char *err_msg = nullptr;
    int rc;

    // Eliminar datos existentes
    const char *sql_delete_data = "DELETE FROM tablaPrestamos";
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

// Selecciona y muestra datos de la tabla Prestamos
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

// Elimina la tabla Prestamos
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




