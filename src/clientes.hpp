//g++ -o prestamo main2.cpp prestamos.cpp -lsqlite3
#ifndef CLIENTES_HPP
#define CLIENTES_HPP

#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>
#include <sqlite3.h>
#include <cstdlib> // Para generar numeros aleatorios
#include <cstring>

/**
 * @file clientes.hpp
 * 
 * @author Evelyn Feng, Daniel De La O, Caleb Arias
 * @date 30/06/24
 * @license MIT License
 * Este programa está sujeto a los términos y condiciones de la licencia resente en el archivo 'licencia.txt'.
 */


/**
 * @brief Crea la tabla de clientes en la base de datos.
 *
 * @param db Puntero a la base de datos SQLite.
 * @return SQLITE_OK si la operación fue exitosa, de lo contrario el código de error.
 */
int crearTablaClientes(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Clientes (
            IdCliente INTEGER PRIMARY KEY UNIQUE,
            Cedula TEXT,
            Nombre TEXT,
            Telefono TEXT,
            Direccion TEXT,
            Correo TEXT,
            Balance INT,
            TipoCuenta TEXT
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

/**
 * @brief Inserta datos de ejemplo en la tabla de clientes.
 *
 * @param db Puntero a la base de datos SQLite.
 * @return SQLITE_OK si la operación fue exitosa, de lo contrario el código de error.
 */
int insertarDatosClientes(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO Clientes (IdCliente, Cedula, Nombre, Telefono, Direccion, Correo, Balance, TipoCuenta) VALUES
        (2701006, '702890948', 'YAKIR HERMAN BUSTOS', '65431234', 'San Jose, Barrio Escalante', 'yakir.herman@hotmail.com', 87654.22, 'Dolares'),
        (1701006, '702890948', 'YAKIR HERMAN BUSTOS', '65431234', 'San Jose, Barrio Escalante', 'yakir.herman@hotmail.com', 250000, 'Colones'),
        (2701027, '702890950', 'MARLENNY MAROTO GUADAMUZ', '87456789', 'Heredia, San Francisco', 'marleny.maroto@yahoo.com', 20985.98, 'Dolares'),
        (2701019, '702890951', 'ANNIA CORTES SOLANO', '90321567', 'Alajuela, San Rafael', 'annia.cortes@gmail.com', 98745.22, 'Dolares'),
        (1701014, '702890952', 'LILLIAM VILLAVICENCIO HIDALGO', '78349087', 'Cartago, Paraiso', 'lilliam.villavicencio@hotmail.com', 1450987.45, 'Colones'),
        (1504004, '504380806', 'ANA HERNANDEZ TORRES', '60123456', 'San Jose, La Sabana', 'ana.hernandez@yahoo.com', 654987.33, 'Colones'),
        (1203004, '901460040', 'NESTOR AURELIO CHACON MONCADA', '65468901', 'Cartago, Tejar', 'nestor.chacon@hotmail.com', 4421987.12, 'Colones');
    )";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    return rc;
}

/**
 * @brief Verifica si una cédula existe en la base de datos.
 *
 * @param db Puntero a la base de datos SQLite.
 * @param cedula Cédula a buscar en la base de datos.
 * @return true si la cédula existe, false si no.
 */
bool existeCedula(sqlite3 *db, const std::string &cedula) {
    std::string sql = "SELECT 1 FROM Clientes WHERE Cedula = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, cedula.c_str(), -1, SQLITE_STATIC);
    bool existe = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return existe;
}

/**
 * @brief Imprime la informacion del cliente.
 *
 * @param db Puntero a la base de datos SQLite.
 * @param cedula Cédula a buscar en la base de datos.
 * @return imprime datos.
 */
void imprimirInfoCliente(sqlite3 *db, const std::string &cedula) {
    std::string sql = "SELECT Cedula, Nombre, Balance FROM Clientes WHERE Cedula = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, cedula.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string cedula = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            double balance = sqlite3_column_double(stmt, 2);
            std::cout << "Cedula: " << cedula << "\nNombre: " << nombre << "\nBalance: " << balance << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }
}

/**
 * @brief Valida el nombre ingresado, permitiendo solo letras y espacios. Usando regex.
 *
 * @param nombre Nombre a validar.
 * @throws std::invalid_argument Si el nombre contiene caracteres no permitidos.
 */
void validarNombre(const std::string& nombre) {
    if (!std::regex_match(nombre, std::regex("^[a-zA-Z ]+$"))) {
        throw std::invalid_argument("El nombre solo debe contener letras y espacios.");
    }
}

/**
 * @brief Valida el número de teléfono ingresado, en formato 12345678.
 *
 * @param telefono Teléfono a validar.
 * @throws std::invalid_argument Si el formato del teléfono es incorrecto.
 */
void validarTelefono(const std::string& telefono) {
    if (!std::regex_match(telefono, std::regex("\\d{8}"))) {
        throw std::invalid_argument("El telefono debe estar en el formato 12345678.");
    }
}

/**
 * @brief Valida la dirección ingresada, permitiendo solo letras, números y espacios.
 *
 * @param direccion Dirección a validar.
 * @throws std::invalid_argument Si la dirección contiene caracteres no permitidos.
 */
void validarDireccion(const std::string& direccion) {
    if (!std::regex_match(direccion, std::regex("^[a-zA-Z0-9 ]+$"))) {
        throw std::invalid_argument("La direccion solo debe contener letras, numeros y espacios.");
    }
}

/**
 * @brief Valida el correo electrónico ingresado, en formato ejemplo@dominio.com.
 *
 * @param correo Correo electrónico a validar.
 * @throws std::invalid_argument Si el formato del correo electrónico es incorrecto.
 */
void validarCorreo(const std::string& correo) {
    if (!std::regex_match(correo, std::regex("^[\\w.%+-]+@[\\w.-]+\\.[a-zA-Z]{2,}$"))) {
        throw std::invalid_argument("El correo debe estar en el formato ejemplo@dominio.com.");
    }
}

/**
 * @brief Valida el tipo de cuenta ingresado, permitiendo solo "Dolares" o "Colones".
 *
 * @param tipoCuenta Tipo de cuenta a validar.
 * @throws std::invalid_argument Si el tipo de cuenta no es "Dolares" ni "Colones".
 */
void validarTipoCuenta(const std::string& tipoCuenta) {
    if (tipoCuenta != "Dolares" && tipoCuenta != "Colones") {
        throw std::invalid_argument("El tipo de cuenta debe ser 'Dolares' o 'Colones'.");
    }
}


/**
 * @brief Agrega un nuevo cliente a la base de datos.
 *
 * @param db Puntero a la base de datos SQLite.
 */
void agregarNuevoCliente(sqlite3 *db) {
    std::string cedula, nombre, telefono, direccion, correo, tipoCuenta;
    double balance = 0.0;

    while (true) {
        std::cout << "Ingrese la cedula (9 numeros, ingrese '0' para salir): ";
        std::cin >> cedula;
        if (cedula == "0") {
            std::cout << "Saliendo del registro de cliente." << std::endl;
            return;
        }
        if (existeCedula(db, cedula)) {
            std::cerr << "La cedula ya existe. Por favor, ingrese una cedula valida." << std::endl;
            continue;
        } else {
            break;
        }
    }
    
    while (true) {
        std::cout << "Ingrese el nombre (solo letras y espacios): ";
        std::cin.ignore();
        std::getline(std::cin, nombre);
        if (nombre == "0") {
            std::cout << "Saliendo del registro de cliente." << std::endl;
            break;
        }
    
        // Convertir el nombre a mayusculas
        std::transform(nombre.begin(), nombre.end(), nombre.begin(), ::toupper);
        try {
            validarNombre(nombre);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    while (true) {
        std::cout << "Ingrese el telefono (formato: 12345678): ";
        std::cin >> telefono;
        if (telefono == "0") {
            std::cout << "Saliendo del registro de cliente." << std::endl;
            break;
        }
        try {
            validarTelefono(telefono);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    while (true) {
        std::cout << "Ingrese la direccion: ";
        std::cin.ignore();
        std::getline(std::cin, direccion);
        if (direccion == "0") {
            std::cout << "Saliendo del registro de cliente." << std::endl;
            break;
        }
        try {
            validarDireccion(direccion);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    while (true) {
        std::cout << "Ingrese el correo (formato: ejemplo@dominio.com): ";
        std::cin >> correo;
        if (correo == "0") {
            std::cout << "Saliendo del registro de cliente." << std::endl;
            break;
        }
        try {
            validarCorreo(correo);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    while (true) {
        std::cout << "Ingrese el tipo de cuenta (Dolares o Colones): ";
        std::cin >> tipoCuenta;
        if (tipoCuenta == "0") {
            std::cout << "Saliendo del registro de cliente." << std::endl;
            break;
        }
        try {
            validarTipoCuenta(tipoCuenta);
            break;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    int id;
    int primerDigito = (tipoCuenta == "Dolares") ? 2 : 1;
    std::string sql = "SELECT COUNT(*) FROM Clientes WHERE TipoCuenta = ?";
    sqlite3_stmt *stmt;

    do {
        id = primerDigito * 1000000 + rand() % 1000000;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
            break;
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) != SQLITE_ROW) {
            std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            break;
        }

        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        if (count == 0) {
            break;
        }
    } while (true);


    std::cout << "El ID de la cuenta en " << tipoCuenta << "es: " << id << std::endl;

/**
 * @brief Agrega un nuevo cliente a la base de datos.
 *
 * @param db Puntero a la base de datos SQLite.
 */
    sql = R"(
        INSERT INTO Clientes (IdCliente, Cedula, Nombre, Telefono, Direccion, Correo, Balance, TipoCuenta) 
        VALUES (?, ?, ?, ?, ?, ?, ?, ?);
    )";


    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, cedula.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, nombre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, telefono.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, direccion.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, correo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 7, balance); // Asegúrate de que balance sea del tipo correcto según la estructura de tu tabla
    sqlite3_bind_text(stmt, 8, tipoCuenta.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error al ejecutar la insercion: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Cliente agregado exitosamente" << std::endl;
        
    }

    sqlite3_finalize(stmt);
   
}

/**
 * @brief Imprime los IDs de cliente y tipos de cuenta asociados a una cédula dada.
 *
 * @param db Puntero a la base de datos SQLite.
 * @param cedula Cédula del cliente para buscar en la base de datos.
 */
void imprimirIdClientesPorCedula(sqlite3* db, const std::string& cedula) {
    const char* sql = "SELECT IdCliente, TipoCuenta FROM Clientes WHERE Cedula = ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparando la declaración SQL: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Conectar la cédula al parámetro
    sqlite3_bind_text(stmt, 1, cedula.c_str(), -1, SQLITE_STATIC);

    // Imprimir resultados
    std::cout << "\nIdCuenta | Tipo de Cuenta" << std::endl;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int idCliente = sqlite3_column_int(stmt, 0);
        const unsigned char* tipoCuenta = sqlite3_column_text(stmt, 1);
        std::cout << idCliente << "  | " << tipoCuenta << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error ejecutando la declaración SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    // Finalizar la declaración
    sqlite3_finalize(stmt);
}

#endif //CLIENTES_HPP
