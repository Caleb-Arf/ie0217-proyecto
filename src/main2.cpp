#include <iostream>
#include "prestamos.hpp"
#include <sqlite3.h>
#include <string> // Necesario para usar std::string

#include "tasas.hpp"
#include "clientes.hpp"



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
    REGRESAR
};

enum INFO {
    TIPOPRESTAMOS = 1,
    TABLAINTERES1,
    TABLAINTERES2,
    TABLAPAGOS,
    REGRESAR2
};


int main() {
    //acceder a tablas de tasas
    sqlite3 *db;
    int rc = sqlite3_open("base_de_datos.db", &db);
    if (rc) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } else {
        std::cout << "Base de datos abierta exitosamente" << std::endl;
    }

    crearTabla1(db);
    insertarData1(db);
    crearDolares(db);
    insertarDolares(db);
    crearCdp(db);
    insertarCdp(db);


    std::string tabla;
    int opcion;
    do {
        std::cout << "\n1. Atencion al cliente." << std::endl;
        std::cout << "2. Obtener informacion sobre prestamos bancarios." << std::endl;
        std::cout << "3. Salir." << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cout << std::endl;
        
        switch(opcion) {
            case ATENCION: {
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
                    std::cout << "10. Regresar al menu principal." << std::endl;
                    std::cout << "Seleccione una operacion a realizar: ";
                    std::cin >> operacion;
                    std::cout << std::endl;

                    switch(operacion) {
                        case ESTADO:

                            break;
                        case TASACDP:
                            if (!tablaExiste(db, "TasasCDP")) {
                                // Crear tabla para tasas de CDPs
                                crearCdp(db);
                                insertarCdp(db);
                                printTableHeaders();
                                mostrarTablaTasas(db);
                            } else {
                                printTableHeaders();
                                mostrarTablaTasas(db);
                            }
                           
                            break;
                        case CREARCDP:
                            
                            break;
                        case CONSULTARCDP:

                                
                            break;
                        case TRANSFERENCIA:
                            
                            break;
                        case DEPOSITO:
                            break;
                        case SOLICITARP:
                          
 
                            break;
                        case ABONARP:
                            

                            break;
                        case ABONAREXTRAP:
                            

                            break;
                        case REGRESAR:
                            // Regresar al menu principal.
                            std::cout << "Regresando al menu principal...\n";
                            break;
                        default:
                            std::cout << "Opcion no valida. Intente de nuevo...\n";
                            break;
                    }
                } while(operacion != REGRESAR);
                break;
            }
                case INFO: {
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

                    switch(operacion_info) {
                        case TIPOPRESTAMOS:
                            if (!tablaExiste(db, "Prestamos")) {
                                crearInfoPrestamos(db);
                                insertarDatosPrestamos(db);
                                imprimirDatosPrestamos(db);
                             } else {
                                imprimirDatosPrestamos(db);
                            }
                            break;
                        case TABLAINTERES1:
                            if (!tablaExiste(db, "TasasColones")) {
                                // Crear tabla para prestamos en colones
                                crearTabla1(db);
                                insertarData1(db);
                                printHeader1();
                                selectData1(db);
                            } else {
                                printHeader1();
                                selectData1(db);
                            }
                            break;
                        case TABLAINTERES2:
                            if (!tablaExiste(db, "TasasDolares")) {
                                // Crear tabla para prestamos en dolares
                                crearDolares(db);
                                insertarDolares(db);
                                printHeader2();
                                mostrarDolares(db);
                            } else {
                                printHeader2();
                                mostrarDolares(db);
                            }
                            break;
                        case TABLAPAGOS:
                            // Imprimir el menu de seleccion de moneda
                            std::cout << "Seleccione la moneda del prestamo:" << std::endl;
                            std::cout << "1. Colones" << std::endl;
                            std::cout << "2. Dolares" << std::endl;
                            // Solicitar al usuario seleccionar la moneda del prestamo
                            int opcionMoneda;
                            std::cout << "\nIngrese el numero correspondiente a la moneda del prestamo: ";
                            std::cin >> opcionMoneda;
                            // Mapear la opcion ingresada por el usuario a la tabla correspondiente
                            if (opcionMoneda == 1) {
                                tabla = "TasasColones";
                                imprimirMenuTipo1(db);
                            } else if (opcionMoneda == 2) {
                                tabla = "TasasDolares";
                                imprimirMenuTipo2(db);
                            } else {
                                std::cerr << "Opcion no valida" << std::endl;
                                break;
                            }
                            break;

                        case REGRESAR2:
                            // Regresar al menu principal.
                            std::cout << "Regresando al menu principal...\n";
                            break;

                        default:
                            std::cout << "Opcion no valida. Intente de nuevo...\n";
                            break;
                    }
                } while(operacion_info != REGRESAR2);
                break;
            }
            case SALIR:
                std::cout << "Saliendo del programa...\n";
                //QUITAR DESPUES
                //eliminarTabla1(db);
                //eliminarDolares(db);
                //eliminarDatosTabla(db);
                sqlite3_close(db);
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo...\n";
                break;
        }
    } while(opcion != SALIR);
    return 0;
}

