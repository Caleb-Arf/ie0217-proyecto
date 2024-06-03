//Tabla de tasas de interes para CDPs
#include <iostream>
#include <sqlite3.h>

static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

void create_table(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS tasas ("
        "plazo TEXT PRIMARY KEY,"
        "fisico_negociable_en_bolsa TEXT,"
        "negociable_en_banco TEXT"
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
        "('1-6', 'N/A', '0.18%'),"
        "('7-13', 'N/A', '0.20%'),"
        "('14-20', 'N/A', '0.62%'),"
        "('21-29', 'N/A', '1.21%'),"
        "('30-59', '3.01%', '3.11%'),"
        "('60-80', '3.45%', '3.55%'),"
        "('90-119', '3.88%', '3.98%'),"
        "('120-149', '4.53%', '4.63%'),"
        "('150-179', '5.01%', '5.11%'),"
        "('180*-209', '5.19%', '5.29%'),"
        "('210-239', '5.19%', '5.29%'),"
        "('240-269', '5.44%', '5.54%'),"
        "('270-299', '5.45%', '5.55%'),"
        "('300-329', '5.49%', '5.59%'),"
        "('330-359', '5.54%', '5.64%'),"
        "('360-539', '5.59%', '5.69%'),"
        "('540-719', '5.69%', '5.79%'),"
        "('720-1079', '6.04%', '6.14%'),"
        "('1080-1439', '6.24%', '6.34%'),"
        "('1440-1799', '6.38%', '6.48%'),"
        "('De 1800', '6.52%', '6.62%');";
    
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
