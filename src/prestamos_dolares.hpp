#include "prestamos_dolares.hpp"

static int callback3(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout.width(55);
        std::cout << azColName[i] << ": ";
        std::cout.width(10);
        std::cout << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

double parsePercentage(const std::string& percentStr) {
    std::string percent = percentStr.substr(0, percentStr.size() - 1); // Eliminar el símbolo %
    return std::stod(percent) / 100.0; // Convertir a decimal
}

int parseDollars(const std::string& dollarsStr) {
    std::string dollars = dollarsStr.substr(1); // Eliminar el símbolo $
    double dollarsDouble = std::stod(dollars); // Convertir a double
    return static_cast<int>(dollarsDouble); // Convertir a entero
}

void crearDolares(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Prestamos_Dolares (
            Credito TEXT,
            Tasa_Efectiva REAL,
            Plazo_Meses INTEGER,
            Cuota INTEGER
        );
    )";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void insertarDolares(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO Prestamos_Dolares (Credito, Tasa_Efectiva, Plazo_Meses, Cuota) VALUES
        ('Crédito Personal Hipotecario en Dolares (098)', 0.1879, 180, 9.84),
        ('Prendario Dolares(018)', 0.1291, 360, 6.65),
        ('Personal Back to Back Dolares Personas Físicas (093)', 0.0480, 180, 7.80),
        ('Vehículo Nuevo dolares (  098)', 0.1675, 96, 18.30),
        ('Vivienda Consumo Cuota unica Dolares (024)', 0.1418, 360, 7.17);
    )";
    
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void mostrarDolares(sqlite3 *db) {
    const char* selectDataSQL = "SELECT * FROM Prestamos_Dolares";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}
void eliminarDolares(sqlite3 *db) {
    const char *sql_delete_data = "DELETE FROM tasas";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }
}