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
    std::string tipoCuentaOrigen, tipoCuentaDestino, cedulaOrigen, cedulaDestino;
    double balanceOrigen, balanceDestino;

    // Obtener datos de la cuenta de origen
    std::string sql = "SELECT Balance, TipoCuenta, Cedula FROM Clientes WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idOrigen);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balanceOrigen = sqlite3_column_double(stmt, 0);
        tipoCuentaOrigen = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cedulaOrigen = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    } else {
        std::cerr << "Cuenta de origen no encontrada." << std::endl;
        sqlite3_finalize(stmt);
        return SQLITE_ERROR;
    }
    sqlite3_finalize(stmt);

    // Verificar si el balance de origen es suficiente
    if (balanceOrigen < monto) {
        std::cerr << "El balance de la cuenta de origen es insuficiente." << std::endl;
        return SQLITE_ERROR;
    }

    // Obtener datos de la cuenta de destino
    sql = "SELECT Balance, TipoCuenta, Cedula FROM Clientes WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idDestino);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balanceDestino = sqlite3_column_double(stmt, 0);
        tipoCuentaDestino = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cedulaDestino = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
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
    sqlite3_bind_text(stmt, 3, cedulaOrigen.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, fecha.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, hora.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 6, balanceOrigen); // Balance después de la transacción
    sqlite3_bind_text(stmt, 7, "Transferencia realizada", -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 8, monto); // Débito
    sqlite3_bind_text(stmt, 9, tipoCuentaOrigen.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 10, tipoCuentaDestino.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Insertar transacción de crédito en la cuenta de destino
    sql = R"(
        INSERT INTO tablaTransacciones (IdTransaccion, IdCliente, Cedula, FechaTransaccion, Hora, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, 0, ?, ?);
    )";

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id + 1);
    sqlite3_bind_int(stmt, 2, idDestino);
    sqlite3_bind_text(stmt, 3, cedulaDestino.c_str(), -1, SQLITE_STATIC);
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

int realizarDeposito(sqlite3 *db, int idOrigen2, int idDestino2, double monto2) {
    const double tipoCambio = 530.0;
    sqlite3_stmt *stmt = nullptr;
    std::string tipoCuentaOrigen, tipoCuentaDestino, cedulaOrigen;
    double balanceOrigen, balanceDestino;

    // Obtiene datos de la cuenta de origen
    std::string sql = "SELECT Balance, TipoCuenta, Cedula FROM Clientes WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idOrigen2);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balanceOrigen = sqlite3_column_double(stmt, 0);
        tipoCuentaOrigen = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cedulaOrigen = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    } else {
        std::cerr << "Cuenta a depositar no encontrada." << std::endl;
        sqlite3_finalize(stmt);
        return SQLITE_ERROR;
    }
    sqlite3_finalize(stmt);

    // Verifica si el balance de origen es suficiente
    if (balanceOrigen < monto2) {
        std::cerr << "El balance de la cuenta de origen es insuficiente." << std::endl;
        return SQLITE_ERROR;
    }

    // Actualiza balances
    balanceOrigen += monto2;

    // Genera id aleatorio
    int id;
    sql = "SELECT COUNT(*) FROM tablaTransacciones WHERE IdTransaccion = ?";
    do {
        id = 4000000 + rand() % 1000000;

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
    sqlite3_bind_int(stmt, 2, idOrigen2);
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
    sqlite3_bind_int(stmt, 2, idOrigen2);
    sqlite3_bind_text(stmt, 3, cedulaOrigen.c_str(), -1, SQLITE_STATIC); // Cedula de origen
    sqlite3_bind_text(stmt, 4, fecha.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, hora.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 6, balanceOrigen); // Balance después de la transacción
    sqlite3_bind_text(stmt, 7, "Depósito realizado", -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 8, monto2); // Crédito
    sqlite3_bind_text(stmt, 9, tipoCuentaOrigen.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 10, tipoCuentaOrigen.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    std::cout << "Depósito realizado con éxito." << std::endl;
    return SQLITE_OK;

    // Print tablaTransacciones
    sql = "SELECT * FROM tablaTransacciones WHERE IdTransaccion = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idTransaccion);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "\nTransacción finalizada:" << std::endl;
        std::cout << "Numero de Transaccion: " << id << std::endl;
        std::cout << "IdCliente: " << idOrigen2 << std::endl;
        std::cout << "FechaTransaccion: " << fecha.c_str() << std::endl;
        std::cout << "Hora: " << hora.c_str() << std::endl;
        std::cout << "SaldoBalance: " << balanceOrigen << std::endl;
        std::cout << "Detalle: " << "Depósito realizado" << std::endl;
        std::cout << "Credito: " << monto2 << std::endl;


    }
    sqlite3_finalize(stmt);
}

// Verifica si existe el préstamo
bool prestamoExiste(sqlite3 *db, int idPrestamo) {
    sqlite3_stmt *stmt = nullptr;
    std::string sql = "SELECT COUNT(*) FROM tablaPrestamos WHERE IdPrestamo = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idPrestamo);

    bool existe = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0) > 0;
    }
    sqlite3_finalize(stmt);

    return existe;
}

int realizarAbonoPrestamo(sqlite3 *db, int idCuenta, int idPrestamo, double montoAbono) {
    const double tipoCambio = 530.0;
    sqlite3_stmt *stmt = nullptr;
    std::string tipoCuenta, tipoPrestamo, cedula;
    double balanceCuenta, saldoPrestamo, cuotaMensual;
    int cuotasPagadas, cuotasFaltantes, diasVencidos;
    std::string fechaVencimiento, fechaCreacion;

    // Obtener datos de la cuenta
    std::string sql = "SELECT Balance, TipoCuenta, Cedula FROM Clientes WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idCuenta);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balanceCuenta = sqlite3_column_double(stmt, 0);
        tipoCuenta = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cedula = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    } else {
        std::cerr << "Cuenta no encontrada." << std::endl;
        sqlite3_finalize(stmt);
        return SQLITE_ERROR;
    }
    sqlite3_finalize(stmt);

    // Obtener datos del préstamo
    sql = "SELECT SaldoPrestamo, MontoCuota, Divisa, CuotasPagadas, CuotasFaltantes, FechaVencimiento, FechaCreacion, DiasVencidos FROM tablaPrestamos WHERE IdPrestamo = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idPrestamo);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        saldoPrestamo = sqlite3_column_double(stmt, 0);
        cuotaMensual = sqlite3_column_double(stmt, 1);
        tipoPrestamo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        cuotasPagadas = sqlite3_column_int(stmt, 3);
        cuotasFaltantes = sqlite3_column_int(stmt, 4);
        fechaVencimiento = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        fechaCreacion = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        diasVencidos = sqlite3_column_int(stmt, 7);
    } else {
        std::cerr << "Préstamo no encontrado." << std::endl;
        sqlite3_finalize(stmt);
        return SQLITE_ERROR;
    }
    sqlite3_finalize(stmt);


   double montoConvertido = montoAbono;
    if (tipoCuenta != tipoPrestamo) {
        if (tipoCuenta == "Colones" && tipoPrestamo == "Dolares") {
            montoConvertido = montoAbono / tipoCambio;
        } else if (tipoCuenta == "Dolares" && tipoPrestamo == "Colones") {
            montoConvertido = montoAbono * tipoCambio;
        } else {
            std::cerr << "Error al aplicar el tipo de cambio." << std::endl;
            return SQLITE_ERROR;
        }
    }

    // Verifica si el abono es mayor que la cuota
    if (montoConvertido > cuotaMensual) {
        std::cerr << "El abono no puede exceder el monto de la cuota mensual. Cuota: " << cuotaMensual << std::endl;
        return SQLITE_ERROR;
    }


    // Actualiza saldo del préstamo
    saldoPrestamo -= montoConvertido;

   // Actualiza balance de la cuenta
    balanceCuenta -= montoAbono;

    // Actualiza cuotas pagadas y faltantes
    cuotasPagadas += 1;
    cuotasFaltantes -= 1;

    // Verifica si la fecha de vencimiento es mayor a la fecha de creación
    if (fechaVencimiento > obtenerFechaHoraActual().substr(0, 10)) {
        diasVencidos += 1;
    }

    // Actualizar en la base de datos
    sql = "UPDATE Clientes SET Balance = ? WHERE IdCliente = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_double(stmt, 1, balanceCuenta);
    sqlite3_bind_int(stmt, 2, idCuenta);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sql = "UPDATE tablaPrestamos SET SaldoPrestamo = ?, CuotasPagadas = ?, CuotasFaltantes = ?, DiasVencidos = ? WHERE IdPrestamo = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_double(stmt, 1, saldoPrestamo);
    sqlite3_bind_int(stmt, 2, cuotasPagadas);
    sqlite3_bind_int(stmt, 3, cuotasFaltantes);
    sqlite3_bind_int(stmt, 4, diasVencidos);
    sqlite3_bind_int(stmt, 5, idPrestamo);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Insertar transacción en tablaTransacciones
    int idTransaccion;
    sql = "SELECT COUNT(*) FROM tablaTransacciones WHERE IdTransaccion = ?";
    do {
        idTransaccion = 5000000 + rand() % 1000000;
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, idTransaccion);

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

    sql = R"(
        INSERT INTO tablaTransacciones (IdTransaccion, IdCliente, Cedula, FechaTransaccion, Hora, SaldoBalance, Detalle, Credito, Debito, CuentaOrigen, CuentaDestino)
        VALUES (?, ?, ?, ?, ?, ?, ?, 0, ?, ?, 'Pago Prestamo');
    )";

    std::string fechaHoraActual = obtenerFechaHoraActual();
    std::string fecha = fechaHoraActual.substr(0, 10);
    std::string hora = fechaHoraActual.substr(11, 8);

    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idTransaccion);
    sqlite3_bind_int(stmt, 2, idCuenta);
    sqlite3_bind_text(stmt, 3, cedula.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, fecha.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, hora.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 6, balanceCuenta);
    sqlite3_bind_text(stmt, 7, "Abono a préstamo", -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 8, montoAbono);
    sqlite3_bind_text(stmt, 9, tipoCuenta.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    std::cout << "Abono realizado con éxito."<< std::endl;

    // Print tablaTransacciones
    sql = "SELECT * FROM tablaTransacciones WHERE IdTransaccion = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idTransaccion);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "\nTransacción finalizada:" << std::endl;
        std::cout << "Numero de Transaccion: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "IdCliente: " << sqlite3_column_int(stmt, 1) << std::endl;
        std::cout << "FechaTransaccion: " << fecha.c_str() << std::endl;
        std::cout << "Hora: " << hora.c_str() << std::endl;
        std::cout << "SaldoBalance: " << balanceCuenta << std::endl;
        std::cout << "Detalle: " << "Abono a préstamo" << std::endl;
        std::cout << "Debito: " << montoAbono << std::endl;


    }
    sqlite3_finalize(stmt);

    // Print tablaPrestamos
    sql = "SELECT * FROM tablaPrestamos WHERE IdPrestamo = ?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, idPrestamo);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "\nPréstamo actualizado:" << std::endl;
        std::cout << "IdPrestamo: " << sqlite3_column_int(stmt, 0) << std::endl;
        std::cout << "Saldo pendiente: " << saldoPrestamo << std::endl;
        std::cout << "CuotasPagadas: " << cuotasPagadas << std::endl;
        std::cout << "CuotasFaltantes: " << cuotasFaltantes << std::endl;
    }
    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

