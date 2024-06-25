#include "Operaciones.hpp"
#include <iostream>
#include <ctime>

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

void crearPrestamo(sqlite3 *db, Cliente* cliente) {
    std::string idPrestamo; // Falta realizar metodo para generar id de prestamos
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
    int cuotasFaltantes = cuotasTotales - cuotasPagadas;

    std::string sql = "INSERT INTO tablaPrestamos (IdCliente, IdPrestamo, FechaCreacion, Divisa, FechaVencimiento, TipoPrestamo, MontoTotal, TasaInteres, CuotasTotales, CuotasPagadas, CuotasFaltantes, Columna12, Columna13, Columna14, Columna15) VALUES (";
    sql += std::to_string(cliente->getIdCliente()) + ", ";
    sql += "'" + idPrestamo + "', ";
    sql += "'" + fechaCreacion + "', ";
    sql += "'" + divisa + "', ";
    sql += "'" + fechaVencimiento + "', ";
    sql += "'" + tipoPrestamo + "', ";
    sql += std::to_string(montoTotal) + ", ";
    sql += std::to_string(tasaInteres) + ", ";
    sql += std::to_string(cuotasTotales) + ", ";
    sql += std::to_string(cuotasPagadas) + ", ";
    sql += std::to_string(cuotasFaltantes) + ", ";
    sql += "0, 0, 0, 0);";

    // Ejecutar la sentencia SQL
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al insertar el dato: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }
}
