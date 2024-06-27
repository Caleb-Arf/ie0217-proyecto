//COMANDO PARA COMPILAR (Actualizar con cada commit para facilitar el trabajo).
//g++ main2.cpp prestamos.cpp clientes2.cpp Operaciones.cpp -o prueba.exe -lsqlite3

/*
Pendientes:
 - hacer un generador de idPrestamos 
*/
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <regex>
#include "prestamos.hpp"
#include "tasas.hpp"
#include "clientes.hpp"
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
                            case ESTADO:
                                // Consultar el estado de cuenta
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
                                int idDestino;
                                std::cout << "Ingrese el ID de cuenta al cual desea realizar la transferencia: ";
                                std::cin >> idDestino;
                                double montoTransferencia;
                                std::cout << "Ingrese el monto para realizar la transferencia: ";
                                std::cin >> montoTransferencia;
                                ejecutar.transferencia(montoTransferencia, idDestino);
                                break;
                            }
                            case DEPOSITO: {
                                double montoDeposito;
                                std::cout << "Ingrese el monto para realizar el deposito: ";
                                std::cin >> montoDeposito;
                                ejecutar.deposito(montoDeposito);
                                break;
                            }
                            case SOLICITARP:
                                ejecutar.crearPrestamo();
                                break;
                            case ABONARP:
                                ejecutar.abonoPrestamo();
                                break;
                            case ABONAREXTRAP:
                                ejecutar.abonoPrestamoExtraordinario();
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
