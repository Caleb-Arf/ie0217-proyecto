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

//Tabla de Prestamos
std::string Cliente::getInfoPrestamos(const std::string& dato, int idPrestamos) {   
    std::string sql = "SELECT " + dato + " FROM tablaPrestamos WHERE idPrestamo = " + std::to_string(idPrestamos) + ";";
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

void Cliente::setInfoPrestamos(const std::string& dato, const std::string& datoActualizado, int idPrestamo) {
    std::string sql = "UPDATE tablaPrestamos SET " + dato + " = '" + datoActualizado + "' WHERE IdPrestamo = " + std::to_string(idPrestamo) + ";";
    char *errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al actualizar el dato: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }
}

//Tasas de CDP
std::string Cliente::getInfoTasasCDP(const std::string& dato, int idCDP) {   
    std::string sql = "SELECT " + dato + " FROM TasasCDP WHERE id = " + std::to_string(idCDP) + ";";
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

//Tabla de CDPs

std::string Cliente::getInfoCDPs(const std::string& dato, int idCDP) {   
    std::string sql = "SELECT " + dato + " FROM tablaCDP WHERE IdCDP = " + std::to_string(idCDP) + ";";
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

void Cliente::setInfoCDPs(const std::string& dato, const std::string& datoActualizado, int idCDP) {
    std::string sql = "UPDATE tablaCDP SET " + dato + " = '" + datoActualizado + "' WHERE IdCDP = " + std::to_string(idCDP) + ";";
    char *errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al actualizar el dato: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }
}