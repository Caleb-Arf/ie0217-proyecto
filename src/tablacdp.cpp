#include <iostream>
#include <sqlite3.h>
#include <iomanip>

static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

void create_table(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tasas ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "plazo TEXT UNIQUE,"
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

void insert_data(sqlite3 *db) {
    const char *sql_insert_data = 
        "INSERT INTO tasas (plazo, fisico_negociable_en_bolsa, negociable_en_banco) VALUES"
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

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("tasas_cdp.db", &db);
    
    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    } else {
        std::cout << "Conectado a la base de datos exitosamente" << std::endl;
    }

    create_table(db);
    insert_data(db);

    // Selecciona datos de la tabla
    const char *sql = "SELECT * FROM tasas";
    char *err_msg = nullptr;
    rc = sqlite3_exec(db, sql, callback, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error ejecutando la consulta: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }

    // Cierra la base de datos
    sqlite3_close(db);
    return 0;
}
