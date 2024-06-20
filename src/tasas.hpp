#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>

// Callback para impresion de tabla de Tasas CDP
static int callback(void *data, int argc, char **argv, char **azColName) {
    // Imprime los datos de la tabla.
    std::cout << std::setw(10) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(15) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(12) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(12) << (argv[3] ? argv[3] : "NULL") << std::endl;
    return 0;
}
//Imprime encabezados
void printTableHeaders() {
    std::cout << std::setw(40) << std::setfill(' ') << "Tasas de CDPs" << std::endl << std::endl;
    std::cout << std::setw(10) << " " << " | "
              << std::setw(15) << "Plazo en meses" << " | "
              << std::setw(12) << "Tasa en bolsa" << " | "
              << std::setw(12) << "Tasa en banco" << std::endl;
    std::cout << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(12, '-') << std::endl;
}

// Crea la tabla Tasas CDP
void crearCdp(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS TasasCDP ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "plazo TEXT,"
        "fisico_negociable_en_bolsa REAL,"
        "negociable_en_banco REAL"
        ");";
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
void insertarCdp(sqlite3 *db) {
    const char *sql_insert_data = 
        "INSERT INTO TasasCDP (plazo, fisico_negociable_en_bolsa, negociable_en_banco) VALUES"
        "('1-6', NULL, 0.0018),"
        "('7-13', NULL, 0.0020),"
        "('14-20', NULL, 0.0062),"
        "('21-29', NULL, 0.0121),"
        "('30-59', 0.0301, 0.0311),"
        "('60-80', 0.0345, 0.0355),"
        "('90-119', 0.0388, 0.0398),"
        "('120-149', 0.0453, 0.0463),"
        "('150-179', 0.0501, 0.0511),"
        "('180*-209', 0.0519, 0.0529),"
        "('210-239', 0.0519, 0.0529),"
        "('240-269', 0.0544, 0.0554),"
        "('270-299', 0.0545, 0.0555),"
        "('300-329', 0.0549, 0.0559),"
        "('330-359', 0.0554, 0.0564),"
        "('360-539', 0.0559, 0.0569),"
        "('540-719', 0.0569, 0.0579),"
        "('720-1079', 0.0604, 0.0614),"
        "('1080-1439', 0.0624, 0.0634),"
        "('1440-1799', 0.0638, 0.0648),"
        "('De 1800', 0.0652, 0.0662);";
    
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_insert_data, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error insertando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla Tasas CDP
void mostrarTablaTasas(sqlite3 *db) {
    const char *sql = "SELECT * FROM TasasCDP";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql, callback, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error ejecutando la consulta: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

// Elimina la tabla Tasas  CDP
void eliminarDatosTabla(sqlite3 *db) {
    const char *sql_delete_data = "DELETE FROM TasasCDP";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }
}


// Callback para impresion de tabla de Tasas en colones
static int callback1(void *data, int argc, char **argv, char **azColName) {
 // Imprime los datos de la tabla.
    std::cout << std::setw(55) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(15) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(12) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(10) << (argv[3] ? argv[3] : "NULL") << std::endl;
    
    return 0;
}

//Imprime encabezados
void printHeader1() {
    static bool printTitle = true;
    if (printTitle) {
        std::cout << std::setw(80) << std::setfill(' ') << "Tasas de prestamos en colones" << std::endl << std::endl;
        printTitle = false;
    }

    std::cout << std::setw(55) << "Credito" << " | "
              << std::setw(15) << "Tasa Efectiva %" << " | "
              << std::setw(12) << "Plazo Meses" << " | "
              << std::setw(10) << "Cuota Colones" << std::endl;
    std::cout << std::string(55, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << std::endl;
}

// Crea la tabla Tasas en colones
void crearTabla1(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS TasasColones (
            Credito TEXT,
            Tasa_Efectiva REAL,
            Plazo_Meses INTEGER,
            Cuota_Millon INTEGER
        );
    )";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Inserta datos en la tabla Tasas en colones
void insertarData1(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO TasasColones (Credito, Tasa_Efectiva, Plazo_Meses, Cuota_Millon) VALUES
        ('Credito Personal Hipotecario colones (012)', 19.36, 240, '12281.84'),
        ('Prendario colones(014)', 10.50, 96, '7580'),
        ('Personal Back to Back Colones Personas Fisicas (093)', 11.51, 180, '11688.26'),
        ('Vehiculo Nuevo colones (  041)', 16.03, 96, '17910.7'),
        ('Vivienda Consumo Cuota unica colones (024)', 13.85, 360, '8827.17'),
        ('Fiduciaria a corto plazo (  070)', 18.85, 60, '25425.43'),
        ('Cancelacion de Pasivos - atraccion de clientes (059)', 17.85, 168, '16210.44');
    )";
    
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla Tasas en colones
void selectData1(sqlite3 *db) {
    const char* selectDataSQL = "SELECT * FROM TasasColones";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL, callback1, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

// Elimina la tabla Tasas en colones
void eliminarTabla1(sqlite3 *db) {
    const char* deleteTableSQL = "DROP TABLE IF EXISTS TasasColones";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, deleteTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Tabla eliminada exitosamente" << std::endl;
    }
}

// Callback para impresion de tabla de Tasas en dolares
static int callback3(void *data, int argc, char **argv, char **azColName) {  
    // Imprime los datos de la tabla.
    std::cout << std::setw(55) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(15) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(12) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(10) << (argv[3] ? argv[3] : "NULL") << std::endl;
    
    return 0;
}

//Imprime encabezados
void printHeader2() {
    static bool printTitle = true;
    if (printTitle) {
        std::cout << std::setw(80) << std::setfill(' ') << "Tasas de prestamos en dolares" << std::endl << std::endl;
        printTitle = false;
    }

    std::cout << std::setw(55) << "Credito" << " | "
              << std::setw(15) << "Tasa Efectiva %" << " | "
              << std::setw(12) << "Plazo Meses" << " | "
              << std::setw(10) << "Cuota $" << std::endl;
    std::cout << std::string(55, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << std::endl;
}

// Crea la tabla Tasas en dolares
void crearDolares(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS TasasDolares (
            Credito TEXT,
            Tasa_Efectiva REAL,
            Plazo_Meses INTEGER,
            Cuota_USD INTEGER
        );
    )";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Inserta datos en la tabla Tasas en dolares
void insertarDolares(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO TasasDolares (Credito, Tasa_Efectiva, Plazo_Meses, Cuota_USD) VALUES
        ('Credito Personal Hipotecario en Dolares (098)', 18.79, 180, 9.84),
        ('Prendario Dolares(018)', 12.91, 360, 6.65),
        ('Personal Back to Back Dolares Personas Fisicas (093)', 14.80, 180, 7.80),
        ('Vehiculo Nuevo dolares (090)', 16.75, 96, 18.30),
        ('Vivienda Consumo Cuota unica Dolares (024)', 14.18, 360, 7.17);
    )";
    
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla Tasas en dolares
void mostrarDolares(sqlite3 *db) {
    const char* selectDataSQL = "SELECT * FROM TasasDolares";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL, callback3, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

// Elimina la tabla Tasas en dolares
void eliminarDolares(sqlite3 *db) {
    const char *sql_delete_data = "DELETE FROM TasasDolares";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }
}

// Valida si existe la tabla
bool tablaExiste(sqlite3 *db, const std::string &nombreTabla) {
    std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + nombreTabla + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return rc == SQLITE_ROW;
    }
    return false;
}


//int main() {
//    sqlite3 *db;
//    int rc = sqlite3_open("datos_financieros.db", &db);
//    if (rc) {
//        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
//        return 1;
//    } else {
//        std::cout << "Base de datos abierta exitosamente" << std::endl;
//    }
//
//    if (!tablaExiste(db, "tasas")) {
//        // Crear tabla para tasas de CDPs
//        crearCdp(db);
//        insertarCdp(db);
//        mostrarTablaTasas(db);
//       // eliminarDatosTabla(db);
//    } else {
//        std::cout << "La tabla de tasas ya existe, no es necesario crearla" << std::endl;
//    }
//
//    if (!tablaExiste(db, "TasasColones")) {
//        // Crear tabla para préstamos en colones
//        crearTabla1(db);
//        insertarData1(db);
//        selectData1(db);
//       // eliminarTabla1(db);
//    } else {
//        std::cout << "La tabla de tasas ya existe, no es necesario crearla" << std::endl;
//    }
//    
//    if (!tablaExiste(db, "TasasDolares")) {
//        // Crear tabla para préstamos en dólares
//        crearDolares(db);
//        insertarDolares(db);
//        mostrarDolares(db);
//       // eliminarDolares(db);
//    } else {
//        std::cout << "La tabla de tasas ya existe, no es necesario crearla" << std::endl;
//    }
//
//    std::cout << "Base de datos cerrada exitosamente" << std::endl;
//    sqlite3_close(db);
//    return 0;
//}
//