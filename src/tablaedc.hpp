#include <iostream>
#include <sqlite3.h>


static int callback(void *data, int argc, char **argv, char **azColName);
// Función para crear la tabla de EstadoDeCuenta
int crearTablaEDC(sqlite3 *db) {
    const char* createTableSQL = R"( 
        CREATE TABLE IF NOT EXISTS EstadoDeCuenta (
            IdCliente INTEGER PRIMARY KEY,
            Cedula TEXT,
            Nombre TEXT,
            Balance REAL,
            Fecha TEXT,
            Hora TEXT
        );
    )";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg); //ejecuta el comando SQL y maneja errores
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    }
    return SQLITE_OK;
}

// Función para insertar datos en la tabla de EstadoDeCuenta
int insertarDatosClientes(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO Clientes (IdCliente, Cedula, Nombre, Balance, Fecha, Hora) VALUES
        (701006, '702890948', 'YAKIR HERMAN BUSTOS', 4421987.12, ?, ?),
        (701027, '702890950', 'MARLENNY MAROTO GUADAMUZ', 2310985.98, ?, ?),
        (701019, '702890951', 'ANNIA CORTES SOLANO', 1298745.22, ?, ?),
        (701014, '702890952', 'LILLIAM VILLAVICENCIO HIDALGO', 450987.45, ?, ?),
        (504004, '504380806', 'ANA HERNANDEZ TORRES', 654987.33, ?, ?),
        (203004, '901460040', 'NESTOR AURELIO CHACON MONCADA', 87654.22, ?, ?);
    )";
        sqlite3_stmt *stmt;
    const char *pzTest;
    char *errMsg = nullptr;

    int rc = sqlite3_prepare_v2(db, insertDataSQL, strlen(insertDataSQL), &stmt, &pzTest); //prepara el comando SQL para su ejecución
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    rc = sqlite3_step(stmt); //Ejecuta el comando SQL perparado
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt); //Finaliza el comando SQL
    return rc;

}
// Función para seleccionar y mostrar datos de la tabla de clientes
int seleccionarYMostrarDatosEDC(sqlite3 *db) {
    const char* selectDataSQL = "SELECT * FROM EstadoDeCuenta"; //Comando para seleccionar todos los registros de 'EstadoDeCuenta'
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL, callback, nullptr, &errMsg); //Ejecuta el comando SQL y llama a la función callback para procesar los resultados
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    }
    return SQLITE_OK;
}

// Función para eliminar la base de datos
int eliminarBaseDatos(const char* dbFile) {
    if (remove(dbFile) != 0) {
        std::cerr << "Error al eliminar la base de datos '" << dbFile << "'" << std::endl;
        return 1;
    } else {
        std::cout << "Base de datos '" << dbFile << "' eliminada correctamente" << std::endl;
        return 0;
    }
}