#include <iostream>
#include <sqlite3.h>
#include <sstream>

static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout.width(55);
        std::cout << azColName[i] << ": ";
        std::cout.width(10);
        std::cout << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

// Funcion para convertir porcentaje de texto a decimal
double parsePercentage(const std::string& percentStr) {
    std::string percent = percentStr.substr(0, percentStr.size() - 1); // Eliminar el simbolo %
    return std::stod(percent) / 100.0; // Convertir a decimal
}

// Funcion para convertir cuota de texto a entero
int parseCuota(const std::string& cuotaStr) {
    std::string cuota = cuotaStr; // No es necesario eliminar simbolos
    std::istringstream iss(cuota);
    double cuotaDouble;
    iss >> cuotaDouble; // Convertir a double
    return static_cast<int>(cuotaDouble); // Convertir a entero
}

int main() {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Abrir una conexion a la base de datos en memoria
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    // Crear tabla Prestamos_Colones
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Prestamos_Colones (
            Credito TEXT,
            Tasa_Efectiva REAL,
            Plazo_Meses INTEGER,
            Cuota_Millon INTEGER
        );
    )";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Insertar datos en la tabla
    const char* insertDataSQL = R"(
        INSERT INTO Prestamos_Colones (Credito, Tasa_Efectiva, Plazo_Meses, Cuota_Millon) VALUES
        ('Credito Personal Hipotecario colones (012)', 19.36, 240, '12281.84'),
        ('Prendario colones(014)', 10.50, 96, '7580'),
        ('Personal Back to Back Colones Personas Fisicas (093)', 11.51, 180, '11688.26'),
        ('Vehiculo Nuevo colones (  041)', 16.03, 96, '17910.7'),
        ('Vivienda Consumo Cuota unica colones (024)', 13.85, 360, '8827.17'),
        ('Fiduciaria a corto plazo (  070)', 18.85, 60, '25425.43'),
        ('Cancelacion de Pasivos - atraccion de clientes (059)', 17.85, 168, '16210.44');
    )";
    
    rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Seleccionar datos de la tabla y mostrarlos
    const char* selectDataSQL = "SELECT * FROM Prestamos_Colones";
    rc = sqlite3_exec(db, selectDataSQL, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Cerrar la conexion a la base de datos
    sqlite3_close(db);

    return 0;
}
