#include <iostream>
#include <sqlite3.h>


static int callback(void *data, int argc, char **argv, char **azColName);
// Función para crear la tabla de clientes
int crearTablaClientes(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Clientes (
            IdCliente INTEGER PRIMARY KEY,
            Cedula TEXT,
            Nombre TEXT,
            Telefono TEXT,
            Direccion TEXT,
            Correo TEXT,
            Balance REAL,
            Prestamos TEXT,
            TipoPrestamo TEXT
        );
    )";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    }
    return SQLITE_OK;
}

// Función para crear la tabla de clientes
int crearTablaClientes(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Clientes (
            IdCliente INTEGER PRIMARY KEY,
            Cedula TEXT,
            Nombre TEXT,
            Telefono TEXT,
            Direccion TEXT,
            Correo TEXT,
            Balance REAL,
            Prestamos TEXT,
            TipoPrestamo TEXT,
            Cuenta TEXT
        );
    )";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    }
    return SQLITE_OK;
}

// Función para generar un valor aleatorio de "Colones" o "Dolares"
const char* generarCuenta() {
    return (rand() % 2 == 0) ? "Colones" : "Dolares";
}

// Función para insertar datos en la tabla de clientes
int insertarDatosClientes(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO Clientes (IdCliente, Cedula, Nombre, Telefono, Direccion, Correo, Balance, Prestamos, TipoPrestamo, Cuenta) VALUES
        (701006, '702890948', 'YAKIR HERMAN BUSTOS', '6543 1234', 'San Jose, Barrio Escalante', 'yakir.herman@hotmail.com', 4421987.12, 'SI', 'H01', ?),
        (701027, '702890950', 'MARLENNY MAROTO GUADAMUZ', '8745 6789', 'Heredia, San Francisco', 'marleny.maroto@yahoo.com', 2310985.98, 'NO', NULL, ?),
        (701019, '702890951', 'ANNIA CORTES SOLANO', '9032 1567', 'Alajuela, San Rafael', 'annia.cortes@gmail.com', 1298745.22, 'NO', NULL, ?),
        (701014, '702890952', 'LILLIAM VILLAVICENCIO HIDALGO', '7834 9087', 'Cartago, Paraiso', 'lilliam.villavicencio@hotmail.com', 450987.45, 'NO', NULL, ?),
        (504004, '504380806', 'ANA HERNANDEZ TORRES', '6012 3456', 'San Jose, La Sabana', 'ana.hernandez@yahoo.com', 654987.33, 'SI', 'H02', ?),
        (203004, '901460040', 'NESTOR AURELIO CHACON MONCADA', '6546 8901', 'Cartago, Tejar', 'nestor.chacon@hotmail.com', 87654.22, 'NO', NULL, ?);
    )";
        sqlite3_stmt *stmt;
    const char *pzTest;
    char *errMsg = nullptr;

    int rc = sqlite3_prepare_v2(db, insertDataSQL, strlen(insertDataSQL), &stmt, &pzTest);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    for (int i = 1; i <= 6; i++) {
        sqlite3_bind_text(stmt, i*10, generarCuenta(), -1, SQLITE_STATIC);
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return rc;

}
// Función para seleccionar y mostrar datos de la tabla de clientes
int seleccionarYMostrarDatosClientes(sqlite3 *db) {
    const char* selectDataSQL = "SELECT * FROM Clientes";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL, callback, nullptr, &errMsg);
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