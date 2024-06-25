#include "clientes2.hpp"

Cliente::Cliente(sqlite3* db, const int idCliente) : db(db), idCliente(idCliente) {}

int Cliente::getIdCliente() const {
    return idCliente;
}
//tabla de clientes
std::string Cliente::getInfoClientes(const std::string& tabla, const std::string& dato, int idCliente) {   
    std::string sql = "SELECT " + dato + " FROM " + tabla + " WHERE IdCliente = " + std::to_string(idCliente) + ";";
    sqlite3_stmt *stmt;
    std::string info = "-1";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            if (text) {
                info = reinterpret_cast<const char*>(text);
            }
        } else {
            std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error en la preparación de la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    return info;
}


void Cliente::setInfoClientes(const std::string& tabla, const std::string& dato, const std::string& datoActualizado, int idCliente) {
    std::string sql = "UPDATE " + tabla + " SET " + dato + " = '" + datoActualizado + "' WHERE IdCliente = " + std::to_string(idCliente) + ";";
    char *errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al actualizar el dato: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }
}

//Tabla de Tasas
std::string Cliente::getInfoInteres(const std::string& tabla, const std::string& dato, int id) {   
    std::string sql = "SELECT " + dato + " FROM " + tabla + " WHERE id = " + std::to_string(id) + ";";
    sqlite3_stmt *stmt;
    std::string info = "-1";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            if (text) {
                info = reinterpret_cast<const char*>(text);
            }
        } else {
            std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error en la preparación de la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    return info;
}




/*#include "clientes.hpp"
#include <iostream>
#include <sqlite3.h>
#include <conio.h> // Para getch(), solo en sistemas Windows
#include <random>
#include <unordered_set>

// Estructura para representar un cliente
struct Cliente {
    int idCliente;
    std::string cedula;
    std::string nombre;
    std::string telefono;
    std::string direccion;
    std::string correo;
    double balance;
    std::string prestamos;
    std::string tipoPrestamo;
};

// Función para manejar el callback
static int callback(void *data, int argc, char **argv, char **azColName) {
    static int headerPrinted = 0;
    if (!headerPrinted) {
        for (int i = 0; i < argc; i++) {
            printf("%-15s", azColName[i]);
        }
        printf("\n");
        headerPrinted = 1;
    }

    for (int i = 0; i < argc; i++) {
        printf("%-15s", argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;

}

static int callback2(void *data, int argc, char **argv, char **azColName) {
    if (argc < 3) {
        // No hay suficientes columnas para representar un cliente válido
        return 1; // Retorna 1 para indicar un error en el callback
    }

    // Imprimir solo el nombre, la cedula y el balance
    std::cout << "Cedula: " << argv[1] << std::endl;
    std::cout << "Nombre: " << argv[2] << std::endl;
    std::cout << "Balance: " << argv[6] << std::endl;

    return 0; // Retorna 0 para indicar exito en el callback
}


// Función para crear un nuevo cliente en la base de datos
void crearNuevoCliente(sqlite3 *db) {
    Cliente nuevoCliente;
    //nuevoCliente.idCliente = generarIdClienteUnico(db); // Generar un ID de cliente unico

    // Solicitar al usuario que ingrese los datos del nuevo cliente
    std::cout << "Ingrese el numero de cedula del nuevo cliente: ";
    std::cin >> nuevoCliente.cedula;
    std::cout << "Ingrese el nombre del nuevo cliente: ";
    std::cin.ignore(); // Ignorar el '\n' en el buffer de entrada
    std::getline(std::cin, nuevoCliente.nombre);
    std::cout << "Ingrese el telefono del nuevo cliente: ";
    std::cin >> nuevoCliente.telefono;
    std::cout << "Ingrese la dirección del nuevo cliente: ";
    std::cin.ignore(); // Ignorar el '\n' en el buffer de entrada
    std::getline(std::cin, nuevoCliente.direccion);
    std::cout << "Ingrese el correo electrónico del nuevo cliente: ";
    std::cin >> nuevoCliente.correo;
    std::cout << "Ingrese el balance del nuevo cliente: ";
    std::cin >> nuevoCliente.balance;
    std::cout << "El cliente tiene prestamos (SI/NO): ";
    std::cin >> nuevoCliente.prestamos;
    std::cout << "Ingrese el tipo de prestamo del nuevo cliente (opcional, dejar vacío si no aplica): ";
    std::cin.ignore(); // Ignorar el '\n' en el buffer de entrada
    std::getline(std::cin, nuevoCliente.tipoPrestamo);

    // Construir la consulta SQL para insertar el nuevo cliente
    std::string insertDataSQL = "INSERT INTO Clientes (IdCliente, Cedula, Nombre, Telefono, Direccion, Correo, Balance, Prestamos, TipoPrestamo) "
                                 "VALUES (" + std::to_string(nuevoCliente.idCliente) + ", '" + nuevoCliente.cedula + "', '" + nuevoCliente.nombre + "', '" + nuevoCliente.telefono + "', '" + nuevoCliente.direccion + "', '" + nuevoCliente.correo + "', " 
                                 + std::to_string(nuevoCliente.balance) + ", '" + nuevoCliente.prestamos + "', '" + nuevoCliente.tipoPrestamo + "')";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, insertDataSQL.c_str(), callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al insertar el nuevo cliente: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Nuevo cliente insertado correctamente." << std::endl;
    }
}


Cliente buscarClientePorCedula(sqlite3 *db, const std::string& cedula) {
    Cliente cliente;
    std::string selectDataSQL = "SELECT * FROM Clientes WHERE Cedula = '" + cedula + "'";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL.c_str(), callback2, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Verificar si se encontró algun cliente
    // Si se encontró, mostrar un mensaje de cliente encontrado
    // De lo contrario, mostrar un mensaje de cliente no encontrado
    if (rc == SQLITE_OK) {
        std::cout << "El cliente existe." << std::endl;
    } else {
        std::cout << "El cliente no existe." << std::endl;
        std::cout << "\n¿Desea crear un nuevo cliente? (SI/NO): ";
        std::string respuesta;
        std::cin >> respuesta;
        if (respuesta == "SI" || respuesta == "si" || respuesta == "Si") {
            crearNuevoCliente(db);
        } else {
            std::cout << "Saliendo del programa..." << std::endl;
            sqlite3_close(db);
            return cliente;
        }
    }
    return cliente;
}


int main() {
    sqlite3 *db;
    const char* dbFile = "clientes.db";
    char *errMsg = 0;
    int rc;

    // Abrir una conexión a la base de datos
    rc = sqlite3_open("clientes.db", &db);
    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    crearTablaClientes(db);
    insertarDatosClientes(db);

    std::string cedula;
    std::cout << "Ingrese el numero de cedula del cliente: ";
    std::cin >> cedula;

    // Buscar el cliente por su numero de cedula
    Cliente clienteEncontrado = buscarClientePorCedula(db, cedula);

    

    // Cerrar la conexión a la base de datos
    sqlite3_close(db);

    return 0;
}
*/