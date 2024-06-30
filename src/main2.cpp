//COMANDO PARA COMPILAR (Actualizar con cada commit para facilitar el trabajo).
//g++ main2.cpp clientes2.cpp Operaciones.cpp -o prueba.exe -lsqlite3

/*
Pendientes:
 - hacer un generador de idPrestamos 
*/
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <regex>
#include "tasas.hpp"
#include "edc.hpp"
#include "clientes.hpp"
#include "transferencia.hpp"
#include "clientes2.hpp"
#include "Operaciones.hpp"
#include "tablacdpOtra.hpp"
#include "tablaPrestamosOtra.hpp"
#include "tablaTransaccionOtra.hpp"

// Enum para el menu principal.
enum Opciones {
    ATENCION = 1,
    INFO,
    SALIR
};

// Enum para el menu de atencion al cliente.
enum Atencion {
    ESTADO = 1,
    TASACDP,
    CREARCDP,
    CONSULTARCDP,
    TRANSFERENCIA,
    DEPOSITO,
    SOLICITARP,
    ABONARP,
    ABONAREXTRAP,
    OBTENER,
    REGRESAR
};

// Enum para el menu de informacion.
enum INFO {
    TIPOPRESTAMOS = 1,
    TABLAINTERES1,
    TABLAINTERES2,
    TABLAPAGOS,
    REGRESAR2
};

void mostrarMenuInfo(sqlite3 *db) {
    int operacion_info;
    do {
        std::cout << "\n1. Tipos de prestamos" << std::endl;
        std::cout << "2. Tasas de interes colones" << std::endl;
        std::cout << "3. Tasas de interes dolares" << std::endl;
        std::cout << "4. Generar tabla de pagos esperada" << std::endl;
        std::cout << "5. Regresar al menu principal." << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> operacion_info;
        std::cout << std::endl;

        switch (operacion_info) {
            case TIPOPRESTAMOS:
                if (!tablaExiste(db, "Prestamos")) {
                    crearInfoPrestamos(db);
                    insertarDatosPrestamos(db);
                }
                imprimirDatosPrestamos(db);
                break;
            case TABLAINTERES1:
                if (!tablaExiste(db, "TasasColones")) {
                    crearTabla1(db);
                    insertarData1(db);
                }
                printHeader1();
                selectData1(db);
                break;
            case TABLAINTERES2:
                if (!tablaExiste(db, "TasasDolares")) {
                    crearDolares(db);
                    insertarDolares(db);
                }
                printHeader2();
                mostrarDolares(db);
                break;
            case TABLAPAGOS:
                std::cout << "Seleccione la moneda del prestamo:" << std::endl;
                std::cout << "1. Colones" << std::endl;
                std::cout << "2. Dolares" << std::endl;
                int opcionMoneda;
                std::cout << "\nIngrese el numero correspondiente a la moneda del prestamo: ";
                std::cin >> opcionMoneda;
                if (opcionMoneda == 1) {
                    imprimirMenuTipo1(db);
                } else if (opcionMoneda == 2) {
                    imprimirMenuTipo2(db);
                } else {
                    std::cerr << "Opcion no valida" << std::endl;
                }
                break;
            case REGRESAR2:
                std::cout << "Regresando al menu principal...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo...\n";
                break;
        }
    } while (operacion_info != REGRESAR2);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("base_de_datos.db", &db);
    if (rc) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } else {
        std::cout << "Base de datos abierta exitosamente" << std::endl;
    }

    // Crear tablas si no existen
    if (!tablaExiste(db, "TasasCDP")) {
        crearTabla1(db);
        insertarData1(db);
    }
    if (!tablaExiste(db, "TasasDolares")) {
        crearDolares(db);
        insertarDolares(db);
    }
    if (!tablaExiste(db, "TasasColones")) {
        crearCdp(db);
        insertarCdp(db);
    }
    if (!tablaExiste(db, "Clientes")) {
        crearTablaClientes(db);
        insertarDatosClientes(db);
    }
    if (!tablaExiste(db, "tablaTransacciones")) {
        crearTablaTransacciones(db);
        insertarTransacciones(db);
    }
    if (!tablaExiste(db, "tablaPrestamos")) {
        crearTablaPrestamos(db);
        insertarPrestamos(db);
    }
    if (!tablaExiste(db, "tablaCDP")) {
        crearTablaCDP(db);
        insertarCDP(db);
    }

    std::string tabla;
    int opcion;
    do {
        std::cout << "\n1. Atencion al cliente." << std::endl;
        std::cout << "2. Obtener informacion sobre prestamos bancarios." << std::endl;
        std::cout << "3. Salir." << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cout << std::endl;

        switch (opcion) {
            case ATENCION: {
                int identificador;
                std::string cedula;

                while (true) {
                    std::cout << "\n------Verificacion de cedula------\n";
                    std::cout << "Ingrese la cedula (9 numeros o 0 para salir): ";
                    std::cin >> cedula;
                    if (cedula == "0") {
                        std::cout << "Saliendo del registro de cliente." << std::endl;
                        break;
                    }
                    if (!std::regex_match(cedula, std::regex("\\d{9}"))) {
                        std::cerr << "Error: La cedula debe contener 9 numeros." << std::endl;
                        continue;
                    }

                    if (existeCedula(db, cedula)) {
                        imprimirInfoCliente(db, cedula);
                    } else {
                        int opcion;
                        std::cout << "Cedula no encontrada. Elija una opcion:\n1. Salir\n2. Crear nuevo cliente\nOpcion: ";
                        std::cin >> opcion;
                        if (opcion == 1) {
                            break;
                        } else if (opcion == 2) {
                            agregarNuevoCliente(db);
                        }
                    }

                    Cliente cliente(db, identificador);
                    Operacion ejecutar(db, &cliente);
                    int operacion;
                    do {
                        std::cout << "\n1. Consultar el estado de cuenta." << std::endl;
                        std::cout << "2. Tasas de un certificado de deposito a plazo." << std::endl;
                        std::cout << "3. Crear un certificado de deposito a plazo." << std::endl;
                        std::cout << "4. Consultar certificado de deposito a plazo." << std::endl;
                        std::cout << "5. Realizar una transferencia." << std::endl;
                        std::cout << "6. Realizar un deposito." << std::endl;
                        std::cout << "7. Solicitar un prestamo." << std::endl;
                        std::cout << "8. Realizar un abono a un prestamo (existente)." << std::endl;
                        std::cout << "9. Realizar un abono extraordinario a un prestamo (existente)." << std::endl;
                        std::cout << "10. Obtener informacion de prestamos." << std::endl;
                        std::cout << "11. Regresar al menu principal." << std::endl;
                        std::cout << "Seleccione una operacion a realizar: ";
                        std::cin >> operacion;
                        std::cout << std::endl;

                        switch (operacion) {
                            case ESTADO: {
                                // Ingresa el IdCliente para encontrar la info
                                int IdCliente;
                                std::string fechaInicio;
                                std::string fechaFin;

                                std::cout << "Ingrese IdCliente: ";
                                std::cin >> IdCliente;

                                // Ingresa el rango de fechas
                                std::cout << "Ingrese la fecha de inicio (YYYY-MM-DD): ";
                                std::cin >> fechaInicio;
                                std::cout << "Ingrese la fecha de fin (YYYY-MM-DD): ";
                                std::cin >> fechaFin;
                            
                                regresarDatosTransaccion(db, IdCliente, fechaInicio, fechaFin);
                            }
                                break;
                            case TASACDP:
                                if (!tablaExiste(db, "TasasCDP")) {
                                    crearCdp(db);
                                    insertarCdp(db);
                                }
                                printTableHeaders();
                                mostrarTablaTasas(db);
                                break;
                            case CREARCDP:
                                ejecutar.crearCDP();
                                break;
                            case CONSULTARCDP:
                                ejecutar.consultarCDP();
                                break;
                            case TRANSFERENCIA: {
                                int idOrigen, idDestino;
                                double monto;

                                while (true) {
                                    std::cout << "Ingrese la cuenta de origen (0 para salir): ";
                                    std::cin >> idOrigen;
                                    if (idOrigen == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (!cuentaExiste1(db, idOrigen)) {
                                        std::cerr << "La cuenta de origen no existe. Intente de nuevo." << std::endl;
                                    } else {
                                        break; // La cuenta existe, sale del bucle
                                    }
                                }

                                if (idOrigen == 0) {
                                    sqlite3_close(db);
                                    break;
                                }

                                while (true) {
                                    std::cout << "Ingrese la cuenta de destino (0 para salir): ";
                                    std::cin >> idDestino;
                                    if (idDestino == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (!cuentaExiste1(db, idDestino)) {
                                        std::cerr << "La cuenta de destino no existe." << std::endl;
                                    } else {
                                        break;
                                    }
                                }

                                if (idDestino == 0) {
                                    sqlite3_close(db);
                                    break;
                                }

                                while (true) {
                                    std::cout << "Ingrese el monto a transferir (0 para salir): ";
                                    std::cin >> monto;
                                    if (monto == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (monto <= 0) {
                                        std::cerr << "El monto de la transferencia debe ser mayor a 0." << std::endl;
                                    } else {
                                        break;
                                    }
                                }

                                if (monto == 0) {
                                    sqlite3_close(db);
                                    break;
                                }

                                try {
                                    realizarTransferencia(db, idOrigen, idDestino, monto);
                                } catch (const std::exception &e) {
                                    std::cerr << "Error: " << e.what() << std::endl;
                                }
                                break;
                            }
                            case DEPOSITO: {
                                int idOrigen2, idDestino2;
                                double monto2;
                                while (true) {
                                    std::cout << "Ingrese cuenta a depositar (0 para salir): ";
                                    std::cin >> idOrigen2;
                                    if (idOrigen2 == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (!cuentaExiste1(db, idOrigen2)) {
                                        std::cerr << "La cuenta de origen no existe. Intente de nuevo." << std::endl;
                                    } else {
                                        break; // La cuenta existe, sale del bucle
                                    }
                                }

                                if (idOrigen2 == 0) {
                                    sqlite3_close(db);
                                    break;
                                }
                                 while (true) {
                                    std::cout << "Ingrese el monto a transferir (0 para salir): ";
                                    std::cin >> monto2;
                                    if (monto2 == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (monto2 <= 0) {
                                        std::cerr << "El monto de la transferencia debe ser mayor a 0." << std::endl;
                                    } else {
                                        break;
                                    }
                                }

                                if (monto2 == 0) {
                                    sqlite3_close(db);
                                    break;
                                }

                                try {
                                    realizarDeposito(db, idOrigen2, idDestino2, monto2);
                                } catch (const std::exception &e) {
                                    std::cerr << "Error: " << e.what() << std::endl;
                                }

                                break;
                            }
                            case SOLICITARP:
                                ejecutar.crearPrestamo();
                                break;
                            case ABONARP:
                                int idCuenta;
                                int idPrestamo;
                                double monto;


                                while (true) {
                                    std::cout << "Ingrese la cuenta a debitar (0 para salir): ";
                                    std::cin >> idCuenta;
                                    if (idCuenta == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (!cuentaExiste1(db, idCuenta)) {
                                        std::cerr << "La cuenta de origen no existe. Intente de nuevo." << std::endl;
                                    } else {
                                        break; // La cuenta existe, sale del bucle
                                    }
                                }

                                if (idCuenta == 0) {
                                    sqlite3_close(db);
                                    break;
                                }

                                while (true) {
                                    std::cout << "Ingrese el ID del prestamo (0 para salir): ";
                                    std::cin >> idPrestamo;
                                    if (idPrestamo == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (!prestamoExiste(db, idPrestamo)) {
                                        std::cerr << "El prestamo no existe." << std::endl;
                                    } else {
                                        break;
                                    }
                                }

                                if (idPrestamo == 0) {
                                    sqlite3_close(db);
                                    break;
                                }

                                while (true) {
                                    std::cout << "Ingrese el monto a abonar: ";
                                    std::cin >> monto;
                                    if (monto == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (monto <= 0) {
                                        std::cerr << "El monto de la transferencia debe ser mayor a 0." << std::endl;
                                    } else {
                                        int resultado = realizarAbonoPrestamo(db, idCuenta, idPrestamo, monto);
                                        if (resultado == SQLITE_OK) {
                                            break;
                                        } else {
                                            std::cerr << "Error al realizar el abono. Intente de nuevo." << std::endl;
                                        }
                                    }
                                }
                                break;
                            case ABONAREXTRAP: {
                                int idCuenta3;
                                int idPrestamo2;
                                double monto3;
                                std::string cedula;
                                
                                while (true) {
                                    std::cout << "Ingrese la cuenta de origen (0 para salir): ";
                                    std::cin >> idCuenta3;
                                    if (idCuenta3 == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (!cuentaExiste1(db, idCuenta3)) {
                                        std::cerr << "La cuenta de origen no existe. Intente de nuevo." << std::endl;
                                    } else {
                                        break; // La cuenta existe, sale del bucle
                                    }
                                }
                            
                                if (idCuenta3 == 0) {
                                    sqlite3_close(db);
                                    return 0;
                                }
                            
                                while (true) {
                                    std::cout << "Ingrese el ID del préstamo (0 para salir): ";
                                    std::cin >> idPrestamo2;
                                    if (idPrestamo2 == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (!prestamoExiste(db, idPrestamo2)) {
                                        std::cerr << "El préstamo no existe." << std::endl;
                                    } else {
                                        break;
                                    }
                                }
                            
                                if (idPrestamo2 == 0) {
                                    sqlite3_close(db);
                                    return 0;
                                }
                            
                                while (true) {
                                    std::cout << "Ingrese el monto a abonar: ";
                                    std::cin >> monto3;
                                    if (monto3 == 0) {
                                        std::cout << "Saliendo" << std::endl;
                                        break;
                                    }
                                    if (monto3 <= 0) {
                                        std::cerr << "El monto de la transferencia debe ser mayor a 0." << std::endl;
                                    } else {
                                        int resultado = realizarAbonoExtraordinario(db, idCuenta3, idPrestamo2, monto3);
                                        if (resultado == SQLITE_OK) {
                                            break;
                                        } else {
                                            std::cerr << "Error al realizar el abono. Intente de nuevo." << std::endl;
                                        }
                                    }
                                }
                            }

                                break;
                            case OBTENER:
                                mostrarMenuInfo(db);
                                break;
                            case REGRESAR:
                                std::cout << "Regresando al menu principal...\n";
                                break;
                            default:
                                std::cout << "Opcion no valida. Intente de nuevo...\n";
                                break;
                        }
                    } while (operacion != REGRESAR);
                    break;
                }
                break;
            }
            case INFO:
                mostrarMenuInfo(db);
                break;
            case SALIR:
                std::cout << "Saliendo del programa...\n";
                sqlite3_close(db);
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo...\n";
                break;
        }
    } while (opcion != SALIR);

    return 0;
}