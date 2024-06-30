#include "Operaciones.hpp"
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <climits>
#include <cstdio>
/**
 * @file Operaciones.cpp
 * @brief Definiciones de las operaciones financieras para clientes.
 */
/**
 * @brief Función para obtener la fecha actual en formato YYYY-MM-DD.
 * @return La fecha actual como una cadena de texto.
 */
std::string obtenerFechaActual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::string fechaActual = std::to_string(ltm->tm_year + 1900) + '-' +
                                   std::to_string(ltm->tm_mon + 1) + '-' +
                                   std::to_string(ltm->tm_mday);
    return fechaActual;
}
    /**
     * @brief Constructor de la clase Operacion.
     * @param db Base de datos SQLite3.
     * @param cliente Cliente asociado a las operaciones.
     */
Operacion::Operacion(sqlite3* db, Cliente* cliente) : db(db), cliente(cliente) {}
    /**
     * @brief Realiza una transferencia de dinero entre dos cuentas.
     * @param montoTransferencia Monto a transferir.
     * @param idDestino ID del cliente destino.
     */
void Operacion::transferencia(double montoTransferencia, int idDestino) {
    std::string tabla = "Clientes";
    std::string dato = "Balance";

    std::string balanceO = cliente->getInfoClientes(tabla, dato, cliente->getIdCliente());
    double balanceOrigen = std::stod(balanceO);

    std::string balandeD = cliente->getInfoClientes(tabla, dato, idDestino);
    double balanceDestino = std::stod(balandeD);

    if (balanceOrigen < montoTransferencia) {
        std::cout << "Saldo insuficiente para realizar la transaccion." << std::endl;
        return;
    }

    double nuevoBalanceOrigen = balanceOrigen - montoTransferencia;
    double nuevoBalanceDestino = balanceDestino + montoTransferencia;

    cliente->setInfoClientes("Clientes", "Balance", std::to_string(nuevoBalanceOrigen), cliente->getIdCliente());
    cliente->setInfoClientes("Clientes", "Balance", std::to_string(nuevoBalanceDestino), idDestino);
    std::cout << "Transferencia realizada con exito." << std::endl;
}

    /**
     * @brief Realiza un depósito en la cuenta del cliente.
     * @param montoDeposito Monto a depositar.
     */
void Operacion::deposito(double montoDeposito) {
    std::string tabla = "Clientes";
    std::string dato = "Balance";

    double balance = std::stod(cliente->getInfoClientes(tabla, dato, cliente->getIdCliente()));

    double nuevoBalance = balance + montoDeposito;

    cliente->setInfoClientes("Clientes", "Balance", std::to_string(nuevoBalance), cliente->getIdCliente());
    std::cout << "Depósito realizado con exito." << std::endl;
}
 /**
     * @brief Crea un nuevo préstamo para el cliente.
     * @param idCliente ID del cliente que solicita el préstamo.
     * @return ID del préstamo creado, -1 si hay un error.
     */
int Operacion::crearPrestamo(int idCliente) {
    int idPrestamo;
    sqlite3_stmt *stmt = nullptr;
    std::string sql = "SELECT COUNT(*) FROM tablaPrestamos WHERE IdPrestamo = ?";
    
    // Bucle para generar un ID de préstamo único
    do {
        idPrestamo = 5000000 + rand() % 1000000;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
            return -1;
        }

        sqlite3_bind_int(stmt, 1, idPrestamo);

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

    std::string cedula;
    std::string divisa;

    // Consulta para obtener la cédula y la divisa del cliente
    sql = "SELECT Cedula, TipoCuenta FROM Clientes WHERE idCliente = ?";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, idCliente);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            cedula = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            divisa = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        } else {
            std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return -1;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    // Selección de divisa y tipo de préstamo
    int seleccionarDivisa;
    std::string tipoPrestamo;
    int idInteres;
    std::string tabla;

    bool condicion = false;
    while (!condicion) {
        std::cout << "\nSeleccione la divisa del préstamo:\n1. Colones\n2. Dólares\nElija 1 para Colones o 2 para Dólares: ";
        std::cin >> seleccionarDivisa;

        switch (seleccionarDivisa) {
            case 1: {
                divisa = "Colones";
                tabla = "TasasColones";
                int seleccionarTipoPrestamoColones;
                bool stop1 = false;
                while (!stop1) {
                    std::cout << "\nEscoja el tipo de préstamo:\n";
                    std::cout << "1. Crédito Personal Hipotecario colones\n";
                    std::cout << "2. Prendario colones\n";
                    std::cout << "3. Vivienda Consumo Cuota única colones\n";
                    std::cout << "4. Vehículo Nuevo colones\n";
                    std::cout << "5. Cancelación de Pasivos - atracción de clientes\n";
                    std::cout << "6. Fiduciaria a corto plazo\n";
                    std::cout << "7. Personal Back to Back colones\n";
                    std::cout << "Tipo de préstamo (1-7): ";
                    std::cin >> seleccionarTipoPrestamoColones;

                    switch (seleccionarTipoPrestamoColones) {
                        case 1:
                            tipoPrestamo = "Crédito Personal Hipotecario colones";
                            idInteres = 12;
                            stop1 = true;
                            break;
                        case 2:
                            tipoPrestamo = "Prendario colones";
                            idInteres = 14;
                            stop1 = true;
                            break;
                        case 3:
                            tipoPrestamo = "Vivienda Consumo Cuota única colones";
                            idInteres = 24;
                            stop1 = true;
                            break;
                        case 4:
                            tipoPrestamo = "Vehículo Nuevo colones";
                            idInteres = 41;
                            stop1 = true;
                            break;
                        case 5:
                            tipoPrestamo = "Cancelación de Pasivos - atracción de clientes";
                            idInteres = 59;
                            stop1 = true;
                            break;
                        case 6:
                            tipoPrestamo = "Fiduciaria a corto plazo";
                            idInteres = 70;
                            stop1 = true;
                            break;
                        case 7:
                            tipoPrestamo = "Personal Back to Back colones";
                            idInteres = 93;
                            stop1 = true;
                            break;
                        default:
                            std::cout << "Seleccione una opción válida.\n";
                            stop1 = false;
                            break;
                    }
                }
                condicion = true;
                break;
            }
            case 2: {
                divisa = "Dólares";
                tabla = "TasasDolares";
                int seleccionarTipoPrestamoDolares;
                bool stop = false;
                while (!stop) {
                    std::cout << "\nEscoja el tipo de préstamo:\n";
                    std::cout << "1. Prendario Dólares\n";
                    std::cout << "2. Vivienda Consumo Cuota única Dólares\n";
                    std::cout << "3. Vehículo Nuevo dólares\n";
                    std::cout << "4. Personal Back to Back Dólares\n";
                    std::cout << "5. Crédito Personal Hipotecario en Dólares\n";
                    std::cout << "Tipo de préstamo (1-5): ";
                    std::cin >> seleccionarTipoPrestamoDolares;

                    switch (seleccionarTipoPrestamoDolares) {
                        case 1:
                            tipoPrestamo = "Prendario Dólares";
                            idInteres = 18;
                            stop = true;
                            break;
                        case 2:
                            tipoPrestamo = "Vivienda Consumo Cuota única Dólares";
                            idInteres = 24;
                            stop = true;
                            break;
                        case 3:
                            tipoPrestamo = "Vehículo Nuevo dólares";
                            idInteres = 90;
                            stop = true;
                            break;
                        case 4:
                            tipoPrestamo = "Personal Back to Back Dólares";
                            idInteres = 94;
                            stop = true;
                            break;
                        case 5:
                            tipoPrestamo = "Crédito Personal Hipotecario en Dólares";
                            idInteres = 98;
                            stop = true;
                            break;
                        default:
                            std::cout << "Seleccione una opción válida.\n";
                            stop = false;
                            break;
                    }
                }
                condicion = true;
                break;
            }
            default:
                std::cout << "Seleccione una opción válida.\n";
                condicion = false;
                break;
        }
    }

    // Consulta para obtener plazo y tasa de interés
    int plazo = 0;
    double tasaInteres = 0.0;
    sql = "SELECT Plazo_Meses, Tasa_Efectiva FROM " + tabla + " WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, idInteres);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            tasaInteres = sqlite3_column_double(stmt, 1);
            plazo = sqlite3_column_int(stmt, 0);
        } else {
            std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return -1;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    // Cálculo de la fecha de vencimiento
    std::time_t now = std::time(nullptr);
    std::tm* future = std::localtime(&now);
    future->tm_mon += plazo;
    std::time_t futureTime = mktime(future);
    std::tm* future_tm = std::localtime(&futureTime);
    std::string fechaVencimiento = std::to_string(future->tm_year + 1900) + '-' +
                                   std::to_string(future->tm_mon + 1) + '-' +
                                   std::to_string(future->tm_mday);

    // Ingreso del monto total del préstamo
    double montoTotal;
    bool montoCorrecto = false;
    while (!montoCorrecto) {
        std::cout << "Ingrese el monto del préstamo: ";
        std::cin >> montoTotal;
        if (montoTotal > 0) {
            montoCorrecto = true;
        } else {
            std::cout << "Por favor, ingrese un monto válido.\n";
        }
    }

    // Datos del préstamo
    int cuotasTotales = plazo;
    int cuotasPagadas = 0;
    int cuotasFaltantes = cuotasTotales;
    int diasVencidos = 0;
    int diasVencimiento = round(plazo * 30.4167);
    double tasaMensual = tasaInteres / 1200;
    double montoCuota = (montoTotal * tasaMensual) / (1 - pow(1 + tasaMensual, -plazo));

    // Inserción en la base de datos
    sql = "INSERT INTO tablaPrestamos (IdCliente, IdPrestamo, Cedula, FechaCreacion, Divisa, FechaVencimiento, TipoPrestamo, MontoTotalPrestamo, TasaInteresP, CuotasTotales, CuotasPagadas, CuotasFaltantes, DiasVencidos, DiasVencimiento, SaldoPrestamo, MontoCuota) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    sqlite3_bind_int(stmt, 1, idCliente);
    sqlite3_bind_int(stmt, 2, idPrestamo);
    sqlite3_bind_text(stmt, 3, cedula.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, obtenerFechaActual().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, divisa.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, fechaVencimiento.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, tipoPrestamo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 8, montoTotal);
    sqlite3_bind_double(stmt, 9, tasaInteres);
    sqlite3_bind_int(stmt, 10, cuotasTotales);
    sqlite3_bind_int(stmt, 11, cuotasPagadas);
    sqlite3_bind_int(stmt, 12, cuotasFaltantes);
    sqlite3_bind_int(stmt, 13, diasVencidos);
    sqlite3_bind_int(stmt, 14, diasVencimiento);
    sqlite3_bind_double(stmt, 15, montoTotal);
    sqlite3_bind_double(stmt, 16, montoCuota);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error al ejecutar la inserción: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    std::cout << "Préstamo agregado exitosamente." << std::endl;

    sqlite3_finalize(stmt);
    return idPrestamo;
}
  /**
     * @brief Realiza un abono a un préstamo existente del cliente.
     */
void Operacion::abonoPrestamo(){
    std::cout << "Prestamos Disponibles para el cliente" << cliente->getIdCliente() << "."<< std::endl;
    std::string sql = "SELECT IdPrestamo, TipoPrestamo, MontoTotalPrestamo FROM tablaPrestamos WHERE IdCliente = " + std::to_string(cliente->getIdCliente()) + ";";
    sqlite3_stmt* stmt;
    int i = 1;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int idPrestamo = sqlite3_column_int(stmt, 0);
            const unsigned char* tipoPrestamoText = sqlite3_column_text(stmt, 1);
            std::string tipoPrestamo = tipoPrestamoText ? reinterpret_cast<const char*>(tipoPrestamoText) : "";
            double montoTotal = sqlite3_column_double(stmt, 2);

            std::cout << "Prestamo # " << i << std::endl;
            std::cout << "IdPrestamo: " << idPrestamo << std::endl;
            std::cout << "Tipo de Prestamo: " << tipoPrestamo << std::endl;
            std::cout << "Monto Total: " << montoTotal << std::endl << std::endl;
            i += 1;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error en la preparación de la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    int idPrestamo;
    std::cout << "Ingrese el id del prestamo al que desea realizar el abono: ";
    std::cin >> idPrestamo;
 
    int cuotasPagadas = std::stoi(cliente->getInfoPrestamos("CuotasPagadas", idPrestamo));
    int cuotasFaltantes = std::stoi(cliente->getInfoPrestamos("CuotasFaltantes", idPrestamo));
    double cuotaMensual = std::stod(cliente->getInfoPrestamos("MontoCuota", idPrestamo));
    double intereses = std::stod(cliente->getInfoPrestamos("SaldoPrestamo", idPrestamo)) * (std::stod(cliente->getInfoPrestamos("TasaInteresP", idPrestamo)) / 1200);
    double montoCuota = cuotaMensual + intereses;
    double balanceCliente = std::stod(cliente->getInfoClientes("Clientes", "Balance", cliente->getIdCliente()));

    if (balanceCliente < montoCuota){
        std::cout << "No se pudo realizar la trasaccion, fondos insuficientes.";
        return;
    }

    std::string nuevoCuotasP = std::to_string(cuotasPagadas + 1);
    cliente->setInfoPrestamos("CuotasPagadas", nuevoCuotasP, idPrestamo);
    std::string nuevoCuotasF = std::to_string(cuotasFaltantes - 1);
    cliente->setInfoPrestamos("CuotasFaltantes", nuevoCuotasF, idPrestamo);
    std::string nuevoBalanceC = std::to_string(balanceCliente - montoCuota);
    cliente->setInfoClientes("Clientes", "Balance", nuevoBalanceC, cliente->getIdCliente());
    std::string nuevoSaldoPrestamo = std::to_string(std::stod(cliente->getInfoPrestamos("SaldoPrestamo", idPrestamo)) - montoCuota);
    cliente->setInfoPrestamos("SaldoPrestamo", nuevoSaldoPrestamo, idPrestamo);
    std::cout << "Abono realizado exitosamente." << std::endl;
}
    /**
     * @brief Realiza un abono extraordinario a un préstamo existente del cliente.
     */
void Operacion::abonoPrestamoExtraordinario(){
    
    std::cout << "Prestamos Disponibles para el cliente" << cliente->getIdCliente() << "."<< std::endl;
    std::string sql = "SELECT IdPrestamo, TipoPrestamo, MontoTotalPrestamo FROM tablaPrestamos WHERE IdCliente = " + std::to_string(cliente->getIdCliente()) + ";";
    sqlite3_stmt* stmt;
    int i = 1;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int idPrestamo = sqlite3_column_int(stmt, 0);
            const unsigned char* tipoPrestamoText = sqlite3_column_text(stmt, 1);
            std::string tipoPrestamo = tipoPrestamoText ? reinterpret_cast<const char*>(tipoPrestamoText) : "";
            double montoTotal = sqlite3_column_double(stmt, 2);

            std::cout << "Prestamo # " << i << std::endl;
            std::cout << "IdPrestamo: " << idPrestamo << std::endl;
            std::cout << "Tipo de Prestamo: " << tipoPrestamo << std::endl;
            std::cout << "Monto Total: " << montoTotal << std::endl << std::endl;
            i += 1;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error en la preparación de la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    int idPrestamo;
    std::cout << "Ingrese el id del prestamo al que desea realizar el abono: ";
    std::cin >> idPrestamo;    

    double abono;
    std::cout << "Ingrese el monto que desea abonar de manera extraordinaria al prestamo seleccionado: ";
    std::cin >> abono;
    double balanceCliente = std::stod(cliente->getInfoClientes("Clientes", "Balance", cliente->getIdCliente()));
    
    if (abono > balanceCliente){
        std::cout << "El cliente no cuenta con el balance suficiente para realizar el abono.";
        return;
    }
    
    double saldoPrestamo = std::stod(cliente->getInfoPrestamos("SaldoPrestamo", idPrestamo));

    if (abono > saldoPrestamo){
        std::cout << "Se requiere de un abono inferior para cancelar el prestamo." << std::endl;
        std::cout << "Abono necesario: " << saldoPrestamo;
        return;
    }

    std::string nuevoBalanceC = std::to_string(balanceCliente - abono);
    cliente->setInfoClientes("Clientes", "Balance", nuevoBalanceC, cliente->getIdCliente());

    std::string nuevoSaldoP = std::to_string(saldoPrestamo - abono);
    cliente->setInfoPrestamos("SaldoPrestamo", nuevoSaldoP, idPrestamo);
    std::cout << "Abono extraordinario realizado exitosamente." << std::endl;
}
    /**
     * @brief Crea un Certificado de Depósito a Plazo (CDP) para el cliente.
     * @param idCliente ID del cliente que solicita el CDP.
     */
void Operacion::crearCDP(int idCliente) {
    sqlite3_stmt *stmt = nullptr;
    std::string sql;

    // Generación de ID único para el CDP
    int idCDP;
    do {
        idCDP = 7000000 + rand() % 1000000;
        sql = "SELECT COUNT(*) FROM tablaCDP WHERE IdCDP = ?";
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        sqlite3_bind_int(stmt, 1, idCDP);
        if (sqlite3_step(stmt) != SQLITE_ROW) {
            std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return;
        }
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        if (count == 0) {
            break;
        }
    } while (true);

    // Obtener datos del cliente
    std::string cedula;
    double balanceCliente;
    sql = "SELECT Cedula, Balance FROM Clientes WHERE IdCliente = ?";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, idCliente);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cedula = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        balanceCliente = sqlite3_column_double(stmt, 1);
    } else {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    // Ingreso del monto en el CDP
    double montoCDP;
    do {
        std::cout << "Ingrese el monto a ingresar en el CDP: ";
        std::cin >> montoCDP;
        if (montoCDP < 0) {
            std::cout << "Valor incorrecto, intente de nuevo" << std::endl;
        } else if (montoCDP > balanceCliente) {
            std::cout << "El balance es insuficiente para la operación." << std::endl;
            return;
        } else {
            break;
        }
    } while (true);

    // Selección de divisa
    std::string divisa, divisaTasa;
    int seleccionarDivisa;
    do {
        std::cout << "\nSeleccione la divisa del CDP: \n1. Colones \n2. Dólares\nElija 1 o 2: ";
        std::cin >> seleccionarDivisa;
        switch (seleccionarDivisa) {
            case 1:
                divisa = "Colones";
                divisaTasa = "negociable_en_banco";
                break;
            case 2:
                divisa = "Dólares";
                divisaTasa = "negociable_en_banco";
                break;
            default:
                std::cout << "Seleccione una opción válida." << std::endl;
                continue;
        }
        break;
    } while (true);

    // Plazo del CDP en días
    int tiempoCDP;
    do {
        std::cout << "Ingrese el plazo del CDP en días: ";
        std::cin >> tiempoCDP;
        if (tiempoCDP < 1) {
            std::cout << "Ingrese un plazo válido." << std::endl;
        } else {
            break;
        }
    } while (true);

    std::string fechaCreacion = obtenerFechaActual();

    std::time_t now = std::time(nullptr);
    std::tm* future = std::localtime(&now);

    // Añadir el número de días especificado de manera iterativa
    future->tm_mday += tiempoCDP;
    std::time_t futureTime = std::mktime(future);

    // Convertir la nueva fecha en una estructura tm
    std::tm* future_tm = std::localtime(&futureTime);

    // Formatear la fecha en el formato deseado (YYYY-MM-DD)
    std::string year = std::to_string(future_tm->tm_year + 1900);
    std::string month = std::to_string(future_tm->tm_mon + 1);
    std::string day = std::to_string(future_tm->tm_mday);

    // Añadir ceros a la izquierda si es necesario
    if (month.length() < 2) month = '0' + month;
    if (day.length() < 2) day = '0' + day;

    std::string fechaVencimiento = year + '-' + month + '-' + day;

    int idTasaInteres;
    //Seleccion de tasa de interes
    switch (tiempoCDP) {
        case 1 ... 6:
            idTasaInteres = 101;
            break;
        case 7 ... 13:
            idTasaInteres = 102;
            break;
        case 14 ... 20:
            idTasaInteres = 103;
            break;
        case 21 ... 29:
            idTasaInteres = 104;
            break;
        case 30 ... 59:
            idTasaInteres = 105;
            break;
        case 60 ... 80:
            idTasaInteres = 106;
            break;
        case 90 ... 119:
            idTasaInteres = 107;
            break;
        case 120 ... 149:
            idTasaInteres = 108;
            break;
        case 150 ... 179:
            idTasaInteres = 109;
            break;
        case 180 ... 209:
            idTasaInteres = 110;
            break;
        case 210 ... 239:
            idTasaInteres = 111;
            break;
        case 240 ... 269:
            idTasaInteres = 112;
            break;
        case 270 ... 299:
            idTasaInteres = 113;
            break;
        case 300 ... 329:
            idTasaInteres = 114;
            break;
        case 330 ... 359:
            idTasaInteres = 115;
            break;
        case 360 ... 539:
            idTasaInteres = 116;
            break;
        case 540 ... 719:
            idTasaInteres = 117;
            break;
        case 720 ... 1079:
            idTasaInteres = 118;
            break;
        case 1080 ... 1439:
            idTasaInteres = 119;
            break;
        case 1440 ... 1799:
            idTasaInteres = 120;
            break;
        case 1800 ... INT_MAX:
            idTasaInteres = 121;
            break;
        default:
            std::cout << "Fuera de rango\n";
            break;
    }
    // Consulta para obtener la tasa de interés
    double tasaInteres;
    sql = "SELECT "+ divisaTasa +" FROM TasasCDP WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, idTasaInteres);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        tasaInteres = sqlite3_column_double(stmt, 0);
    } else {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    // Cálculo de intereses
    double interesBruto = (montoCDP * tasaInteres) * tiempoCDP / 360.0;
    double impuesto = interesBruto * 0.15;
    double interesNeto = interesBruto - impuesto;

    // Actualización del balance del cliente
    double nuevoBalanceCliente = balanceCliente - montoCDP;
    sql = "UPDATE Clientes SET Balance = ? WHERE IdCliente = ?";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_double(stmt, 1, nuevoBalanceCliente);
    sqlite3_bind_int(stmt, 2, idCliente);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error al ejecutar la actualización: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    // Inserción del CDP en la tabla
    sql = "INSERT INTO tablaCDP (IdCDP, Cedula, IdCliente, FechaCreacionCDP, DivisaCDP, FechaVencimientoCDP, MontoCDP, InteresesGanados, TasaInteresCDP, MesesFaltantesCDP, Plazo) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, idCDP);
    sqlite3_bind_text(stmt, 2, cedula.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, idCliente);
    sqlite3_bind_text(stmt, 4, fechaCreacion.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, divisa.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, fechaVencimiento.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 7, montoCDP);
    sqlite3_bind_double(stmt, 8, interesNeto);
    sqlite3_bind_double(stmt, 9, tasaInteres);
    sqlite3_bind_int(stmt, 10, ceil(tiempoCDP/30.4167));
    sqlite3_bind_text(stmt, 11, std::to_string(tiempoCDP).c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error al ejecutar la inserción: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "CDP generado exitosamente." << std::endl;
    }
    sqlite3_finalize(stmt);
}

void Operacion::consultarCDP() {
    std::cout << "Certificados de Deposito a Plazo disponibles para el cliente" << cliente->getIdCliente() << "." << std::endl;
    std::string sql = "SELECT IdCDP, MontoCDP, FechaCreacion2, TasaInteresCDP FROM tablaCDP WHERE IdCliente = " + std::to_string(cliente->getIdCliente()) + ";";
    sqlite3_stmt* stmt;
    int i = 1;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int idCDP = sqlite3_column_int(stmt, 0);
            double montoCDP = sqlite3_column_double(stmt, 1);
            const unsigned char* fechaCreacionText = sqlite3_column_text(stmt, 2);
            std::string fechaCreacion = fechaCreacionText ? reinterpret_cast<const char*>(fechaCreacionText) : "";
            double tasaInteresCDP = sqlite3_column_double(stmt, 3);

            std::cout << "CDP # " << i << std::endl;
            std::cout << "Monto del CDP: " << montoCDP << std::endl;
            std::cout << "Fecha de creacion: " << fechaCreacion << std::endl;
            std::cout << "Tasa de interes: " << tasaInteresCDP << std::endl << std::endl;
            i += 1;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error en la preparación de la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }

    int idCDP;
    std::cout << "Ingrese el id del CDP que desea consultar: ";
    std::cin >> idCDP;

    std::time_t tiempoActual = std::time(0);
    std::tm* tiempoLocal = std::localtime(&tiempoActual);

    std::string fechaVencimiento = cliente->getInfoCDPs("FechaVencimiento2", idCDP);
    int diaVencimiento, mesVencimiento, vencimientoAnual;
    
    // Asignar fechaVencimiento a fechaV para utilizar en sscanf
    const char* fechaV = fechaVencimiento.c_str();
    
    // Utilizar sscanf para extraer los valores
    if (sscanf(fechaV, "%d/%d/%d", &diaVencimiento, &mesVencimiento, &vencimientoAnual) != 3) {
        std::cerr << "Error al interpretar la fecha.\n";
        return; // Salir de la función si hay un error
    }

    // Inicializar la estructura tm
    std::tm vencimiento = {};
    vencimiento.tm_mday = diaVencimiento;
    vencimiento.tm_mon = mesVencimiento - 1;  
    vencimiento.tm_year = vencimientoAnual - 1900;  
    
    std::time_t segundosActuales = std::mktime(tiempoLocal);
    std::time_t segundosVencimiento = std::mktime(&vencimiento);

    double segundosFaltantes = std::difftime(segundosVencimiento, segundosActuales); // Cambiar el orden para obtener el tiempo faltante correctamente
    double diasFaltantes = segundosFaltantes / (3600 * 24);

    cliente->setInfoCDPs("DiasFaltantesCDP", std::to_string(diasFaltantes), idCDP);
    std::cout << "Faltan " << diasFaltantes << " días para recuperar el dinero." << std::endl;
}
