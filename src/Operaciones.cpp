#include "Operaciones.hpp"
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

Operacion::Operacion(sqlite3* db, Cliente* cliente) : db(db), cliente(cliente) {}

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
}

void Operacion::deposito(double montoDeposito) {
    std::string tabla = "Clientes";
    std::string dato = "Balance";

    double balance = std::stod(cliente->getInfoClientes(tabla, dato, cliente->getIdCliente()));

    double nuevoBalance = balance + montoDeposito;

    cliente->setInfoClientes("Clientes", "Balance", std::to_string(nuevoBalance), cliente->getIdCliente());
}

void Operacion::crearPrestamo() {
    int idPrestamo = 111111; // Falta realizar metodo para generar id de prestamos
    std::string cedula = cliente->getInfoClientes("Clientes", "Cedula", cliente->getIdCliente());
    
    // Toma la fecha actual, tambien es posible encontrar la hora exacta de la misma forma
    std::time_t tiempoActual = std::time(0);
    std::tm* tiempoLocal = std::localtime(&tiempoActual);
    std::string fechaCreacion = std::to_string(tiempoLocal->tm_mday) + "/" + std::to_string(tiempoLocal->tm_mon + 1) + "/" + std::to_string(tiempoLocal->tm_year + 1900);

    // Divisa
    int seleccionarDivisa;
    std::string divisa;
    std::string tipoPrestamo;
    int idInteres;
    std::string tabla;

    bool condicion = false;
    while (!condicion) {
        std::cout << "\nRealice la seleccion de la divisa del prestamo: \n1.Colones \n2.Dolares." << std::endl;
        std::cout << "Elija 1 para Colones o 2 para Dolares: ";
        std::cin >> seleccionarDivisa;

        switch (seleccionarDivisa) {
            case 1: {
                divisa = "Colones";
                tabla = "TasasColones";
                int seleccionarTipoPrestamoColones;
                bool stop1 = false;
                while (!stop1) {
                    std::cout << "\nEscoja el tipo de prestamo." << std::endl;
                    std::cout << "1. Credito Personal Hipotecario colones." << std::endl;
                    std::cout << "2. Prendario colones." << std::endl;
                    std::cout << "3. Vivienda Consumo Cuota unica colones." << std::endl;
                    std::cout << "4. Vehiculo Nuevo colones." << std::endl;
                    std::cout << "5. Cancelacion de Pasivos - atraccion de clientes." << std::endl;
                    std::cout << "6. Fiduciaria a corto plazo." << std::endl;
                    std::cout << "7. Personal Back to Back colones." << std::endl;
                    std::cout << "Tipo de prestamo (1,2,3,4,5,6,7): ";
                    std::cin >> seleccionarTipoPrestamoColones;

                    switch (seleccionarTipoPrestamoColones) {
                        case 1:
                            tipoPrestamo = "Credito Personal Hipotecario colones";
                            idInteres = 12;
                            stop1 = true;
                            break;
                        case 2:
                            tipoPrestamo = "Prendario colones";
                            idInteres = 14;
                            stop1 = true;
                            break;
                        case 3:
                            tipoPrestamo = "Vivienda Consumo Cuota unica colones";
                            idInteres = 24;
                            stop1 = true;
                            break;
                        case 4:
                            tipoPrestamo = "Vehiculo Nuevo colones";
                            idInteres = 41;
                            stop1 = true;
                            break;
                        case 5:
                            tipoPrestamo = "Cancelacion de Pasivos - atraccion de clientes";
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
                            std::cout << "Seleccione una opcion valida.";
                            stop1 = false;
                            break;
                    }
                }
                condicion = true;
                break;
            }
            case 2: {
                divisa = "Dolares";
                tabla = "TasasDolares";
                int seleccionarTipoPrestamoDolares;
                bool stop = false;
                while (!stop) {
                    std::cout << "\nEscoja el tipo de prestamo." << std::endl;
                    std::cout << "1. Prendario Dolares." << std::endl;
                    std::cout << "2. Vivienda Consumo Cuota unica Dolares." << std::endl;
                    std::cout << "3. Vehiculo Nuevo dolares." << std::endl;
                    std::cout << "4. Personal Back to Back Dolares." << std::endl;
                    std::cout << "5. Credito Personal Hipotecario en Dolares." << std::endl;
                    std::cout << "Tipo de prestamo (1,2,3,4,5): ";
                    std::cin >> seleccionarTipoPrestamoDolares;

                    switch (seleccionarTipoPrestamoDolares) {
                        case 1:
                            tipoPrestamo = "Prendario Dolares";
                            idInteres = 18;
                            stop = true;
                            break;
                        case 2:
                            tipoPrestamo = "Vivienda Consumo Cuota unica Dolares";
                            idInteres = 24;
                            stop = true;
                            break;
                        case 3:
                            tipoPrestamo = "Vehiculo Nuevo dolares";
                            idInteres = 90;
                            stop = true;
                            break;
                        case 4:
                            tipoPrestamo = "Personal Back to Back Dolares";
                            idInteres = 94;
                            stop = true;
                            break;
                        case 5:
                            tipoPrestamo = "Credito Personal Hipotecario en Dolares";
                            idInteres = 98;
                            stop = true;
                            break;
                        default:
                            std::cout << "Seleccione una opcion valida.";
                            stop = false;
                            break;
                    }
                }
                condicion = true;
                break;
            }
            default:
                std::cout << "Seleccione una opcion valida.";
                condicion = false;
                break;
        }
    }

    // realizar la fecha de vencimiento con el plazo
    int plazo = std::stoi(cliente->getInfoInteres(tabla, "Plazo_Meses", idInteres));
    int anual = plazo / 12;
    int mensual = plazo % 12;
    std::string fechaVencimiento = std::to_string(tiempoLocal->tm_mday) + "/" + std::to_string(tiempoLocal->tm_mon + 1 + mensual) + "/" + std::to_string(tiempoLocal->tm_year + 1900 + anual);

    // monto total del prestamo
    double montoTotal;
    std::cout << "Ingrese el monto del prestamo: ";
    std::cin >> montoTotal;

    // tasa de interes del prestamo
    double tasaInteres = std::stod(cliente->getInfoInteres(tabla, "Tasa_Efectiva", idInteres));
    
    // cuotas totales 
    int cuotasTotales = std::stoi(cliente->getInfoInteres(tabla, "Plazo_Meses", idInteres));

    // cuotas pagadas (Inicia en 0 por que se esta creando el prestamo)
    int cuotasPagadas = 0;

    // cuotas faltantes
    int cuotasFaltantes = cuotasTotales;

    // iniciar dias vencidos en 0 por que recien se crea el prestamo
    int diasVencidos = 0;

    //realizar el calculo para los dias de vencimiento
    int diasVencimiento = round(plazo*30.4167);

    //calculo del pago mensual
    double tasaMensual = tasaInteres / 1200; // Convertir la tasa anual a mensual
    double montoCuota = (montoTotal * tasaMensual) / (1 - pow(1 + tasaMensual, - plazo));

    // Construcción de la sentencia SQL
    std::string sql = "INSERT INTO tablaPrestamos (IdCliente, IdPrestamo, Cedula, FechaCreacion, Divisa, FechaVencimiento, TipoPrestamo, MontoTotalPrestamo, TasaInteresP, CuotasTotales, CuotasPagadas, CuotasFaltantes, DiasVencidos, DiasVencimiento, SaldoPrestamo, MontoCuota) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, cliente->getIdCliente());
    sqlite3_bind_int(stmt, 2, idPrestamo);
    sqlite3_bind_text(stmt, 3, cedula.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, fechaCreacion.c_str(), -1, SQLITE_STATIC);
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
        std::cerr << "Error al ejecutar la insercion: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Prestamo agregado exitosamente." << std::endl;
    }

    sqlite3_finalize(stmt);
}

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
}

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
}