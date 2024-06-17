#include <iostream>
#include <sqlite3.h>
#include <sstream>

static int callback1(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout.width(55);
        std::cout << azColName[i] << ": ";
        std::cout.width(10);
        std::cout << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

// Funcion para crear la tabla db
void crearTabla1(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS db (
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

// Funcion para insertar datos en la tabla db
void insertarData1(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO db (Credito, Tasa_Efectiva, Plazo_Meses, Cuota_Millon) VALUES
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

// Funcion para seleccionar y mostrar datos de la tabla db
void selectData1(sqlite3 *db) {
    const char* selectDataSQL = "SELECT * FROM db";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

// Funcion para eliminar la tabla db
void elimnarTabla1(sqlite3 *db) {
    const char* deleteTableSQL = "DROP TABLE IF EXISTS db";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, deleteTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Tabla eliminada exitosamente" << std::endl;
    }
}

