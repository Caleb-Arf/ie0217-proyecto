#include <iostream>
#include <sqlite3.h>
#include <string>
#include <ctime>
#include <cstdlib>



std::string obtenerFechaHoraActual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char fechaHora[20];
    sprintf(fechaHora, "%04d-%02d-%02d %02d:%02d:%02d",
            1900 + ltm->tm_year,
            1 + ltm->tm_mon,
            ltm->tm_mday,
            ltm->tm_hour,
            ltm->tm_min,
            ltm->tm_sec);

    return std::string(fechaHora);
}

// Verifica si existe cuenta
bool cuentaExiste1(sqlite3 *db, int idCuenta) {
    sqlite3_stmt *stmt = nullptr;
    std::string sql = "SELECT COUNT(*) FROM Clientes WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idCuenta);

    bool existe = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }
    sqlite3_finalize(stmt);

    return existe;
}

int realizarTransferencia(sqlite3 *db, int idOrigen, int idDestino, double monto) {
    const double tipoCambio = 530.0;
    sqlite3_stmt *stmt = nullptr;
    std::string tipoCuentaOrigen, tipoCuentaDestino;
    double balanceOrigen, balanceDestino;

    // Obtiene datos de la cuenta de origen
    std::string sql = "SELECT Balance, TipoCuenta FROM Clientes WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idOrigen);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balanceOrigen = sqlite3_column_double(stmt, 0);
        tipoCuentaOrigen = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    } else {
        std::cerr << "Cuenta de origen no encontrada." << std::endl;
        sqlite3_finalize(stmt);
        return SQLITE_ERROR;
    }
    sqlite3_finalize(stmt);

    // Verifica si el balance de origen es suficiente
    if (balanceOrigen < monto) {
        std::cerr << "El balance de la cuenta de origen es insuficiente." << std::endl;
        return SQLITE_ERROR;
    }

    // Obtiene datos de la cuenta de destino
    sql = "SELECT Balance, TipoCuenta FROM Clientes WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idDestino);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balanceDestino = sqlite3_column_double(stmt, 0);
        tipoCuentaDestino = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    } else {
        std::cerr << "Cuenta de destino no encontrada." << std::endl;
        sqlite3_finalize(stmt);
        return SQLITE_ERROR;
    }
    sqlite3_finalize(stmt);

    // Verificar si es necesario aplicar tipo de cambio
    double montoDestino = monto;
    if (tipoCuentaOrigen != tipoCuentaDestino) {
        if (tipoCuentaOrigen == "Dolares" && tipoCuentaDestino == "Colones") {
            montoDestino *= tipoCambio;
        } else if (tipoCuentaOrigen == "Colones" && tipoCuentaDestino == "Dolares") {
            montoDestino /= tipoCambio;
        } else {
            std::cerr << "Error al aplicar el tipo de cambio." << std::endl;
            return SQLITE_ERROR;
        }
    }

    // Actualizar balances
    balanceOrigen -= monto;
    balanceDestino += montoDestino;

    // Generar id aleatorio
    int id;
    sql = "SELECT COUNT(*) FROM tablaTransacciones WHERE IdTransaccion = ?";
    do {
        id = 3000000 + rand() % 1000000;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
            return -1;
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) != SQLITE_ROW) {
            std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return -1;
        }

        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);

        if (count == 0) {
            break;
        }

    } while (true);

    // Actualizar cuenta de origen
    sql = "UPDATE Clientes SET Balance = ? WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_double(stmt, 1, balanceOrigen);
    sqlite3_bind_int(stmt, 2, idOrigen);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Actualizar cuenta de destino
    sql = "UPDATE Clientes SET Balance = ? WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_double(stmt, 1, balanceDestino);
    sqlite3_bind_int(stmt, 2, idDestino);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Insertar transacción en tablaTransacciones
    sql = R"(
        INSERT INTO tablaTransacciones (IdTransaccion, IdCliente, Cedula, FechaTransaccion, Hora, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino)
        VALUES (?, ?, ?, ?, ?, ?, ?, 0, ?, ?, ?);
    )";

    std::string fechaHoraActual = obtenerFechaHoraActual();
    std::string fecha = fechaHoraActual.substr(0, 10);
    std::string hora = fechaHoraActual.substr(11, 8);

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_int(stmt, 2, idOrigen);
    sqlite3_bind_text(stmt, 3, "N/A", -1, SQLITE_STATIC); // Debería buscar la cédula correspondiente
    sqlite3_bind_text(stmt, 4, fecha.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, hora.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 6, balanceOrigen); // Balance después de la transacción
    sqlite3_bind_text(stmt, 7, "Transferencia realizada", -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 8, monto); // Débito
    sqlite3_bind_text(stmt, 9, tipoCuentaOrigen.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 10, tipoCuentaDestino.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sql = R"(
        INSERT INTO tablaTransacciones (IdTransaccion, IdCliente, Cedula, FechaTransaccion, Hora, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, 0, ?, ?);
    )";
    // Insertar transacción de crédito en la cuenta de destino
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id + 1);
    sqlite3_bind_int(stmt, 2, idDestino);
    sqlite3_bind_text(stmt, 3, "N/A", -1, SQLITE_STATIC); // Debería buscar la cédula correspondiente
    sqlite3_bind_text(stmt, 4, fecha.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, hora.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 6, balanceDestino); // Balance después de la transacción
    sqlite3_bind_text(stmt, 7, "Transferencia recibida", -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 8, montoDestino); // Crédito
    sqlite3_bind_text(stmt, 9, tipoCuentaOrigen.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 10, tipoCuentaDestino.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    std::cout << "Transferencia realizada con éxito." << std::endl;
    return SQLITE_OK;
}