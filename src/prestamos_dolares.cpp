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
    std::string percent = percentStr.substr(0, percentStr.size() - 1); // Eliminar el símbolo %
    return std::stod(percent) / 100.0; // Convertir a decimal
}

// Funcion para convertir dolares a enteros
int parseDollars(const std::string& dollarsStr) {
    std::string dollars = dollarsStr.substr(1); // Eliminar el símbolo $
    double dollarsDouble = std::stod(dollars); // Convertir a double
    return static_cast<int>(dollarsDouble); // Convertir a entero
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

    // Crear tabla Prestamos_Dolares
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Prestamos_Dolares (
            Credito TEXT,
            Tasa_Efectiva REAL,
            Plazo_Meses INTEGER,
            Cuota INTEGER
        );
    )";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Insertar datos en la tabla
    const char* insertDataSQL = R"(
        INSERT INTO Prestamos_Dolares (Credito, Tasa_Efectiva, Plazo_Meses, Cuota) VALUES
        ('Crédito Personal Hipotecario en Dolares (098)', 0.1879, 180, 9.84),
        ('Prendario Dolares(018)', 0.1291, 360, 6.65),
        ('Personal Back to Back Dolares Personas Físicas (093)', 0.0480, 180, 7.80),
        ('Vehículo Nuevo dolares (  098)', 0.1675, 96, 18.30),
        ('Vivienda Consumo Cuota unica Dolares (024)', 0.1418, 360, 7.17);
    )";
    
    rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Seleccionar datos de la tabla y mostrarlos
    const char* selectDataSQL = "SELECT * FROM Prestamos_Dolares";
    rc = sqlite3_exec(db, selectDataSQL, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Cerrar la conexion a la base de datos
    sqlite3_close(db);

    return 0;
}
