#include <iostream>
#include "prestamos.hpp"
#include <sqlite3.h>
#include "tablacdp.hpp"
#include "prestamos_colones.hpp"
#include "prestamos_dolares.hpp"

// Enum para el menu principal.
enum Opciones {
    ATENCION = 1,
    INFO,
    SALIR
};

// Enum para el menu de atencion al cliente.
enum Atencion {
    ESTADO = 1,
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
    TABLAINTERES,
    TABLAPAGOS,
    REGRESAR2
};
int main() {
    int idCliente;
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Abrir una conexión a la base de datos en memoria
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    // Crear e insertar la tabla de préstamos en colones
    crearCdp(db);
    insertarCdp(db);

    // Crear e insertar la tabla CDP
    crearTabla1(db);
    insertarData1(db);

    // Crear e insertar la tabla CDP
    crearDolares(db);
    insertarDolares(db);

    std::cout << "Por favor ingrese su numero de cedula: " << std::endl;
    std::cin >> idCliente;

    Prestamo prestamo1(1, 10000, 5, 12, 1, "Mensual");
    // Comprobar si el cliente esta en la base de datos de clientIDs.
    
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
                    std::cout << "2. Crear un certificado de deposito a plazo." << std::endl;
                    std::cout << "3. Consultar certificado de deposito a plazo." << std::endl;
                    std::cout << "4. Realizar una transferencia." << std::endl;
                    std::cout << "5. Realizar un deposito." << std::endl;
                    std::cout << "6. Solicitar un prestamo." << std::endl;
                    std::cout << "7. Realizar un abono a un prestamo (existente)." << std::endl;
                    std::cout << "8. Realizar un abono extraordinario a un prestamo (existente)." << std::endl;
                    std::cout << "9. Regresar al menu principal." << std::endl;
                    std::cout << "Seleccione una operacion a realizar: ";
                    std::cin >> operacion;
                    std::cout << std::endl;

                    switch(operacion) {
                        case ESTADO:
                            // Logica para consultar el estado de cuenta.
                            prestamo1.estadoPrestamo();
                            break;
                        case CREARCDP:
                            
                            break;
                        case CONSULTARCDP:
                                if (rc) {
                                    std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
                                    return rc;
                                } else {
                                    std::cout << "Conectado a la base de datos exitosamente" << std::endl;
                                }
                                mostrarTablaTasas(db);
                                
                            break;
                        case TRANSFERENCIA:
                            
                            break;
                        case DEPOSITO:
                            break;
                        case SOLICITARP:
                          
                            prestamo1.solicitarPrestamo(10000, 5, 12, 1, "Mensual");
                            break;
                        case ABONARP:
                            
                            prestamo1.abonoPrestamo(500);
                            prestamo1.estadoPrestamo();
                            break;
                        case ABONAREXTRAP:
                            
                            prestamo1.abonoExtraordinario(1000);
                            prestamo1.estadoPrestamo();
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
                    std::cout << "2. Tasas de interes" << std::endl;
                    std::cout << "3. Generar tabla de pagos esperada" << std::endl;
                    std::cout << "4. Regresar al menu principal." << std::endl;
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> operacion_info;
                    std::cout << std::endl;

                    switch(operacion_info) {
                        case TIPOPRESTAMOS:
                            prestamo1.tipoPrestamo();
                            break;
                        case TABLAINTERES:
                            selectData1(db);
                            mostrarDolares(db);
                            break;
                        case TABLAPAGOS:
                            // Logica para generar tabla de pagos esperada.
                            break;
                        case REGRESAR2:
                            // Regresar al menu principal.
                            std::cout << "Regresando al menu principal...\n";
                            break;
                            break;

                        default:
                            std::cout << "Opcion no valida. Intente de nuevo...\n";
                            break;
                    }
                } while(operacion_info != REGRESAR);
                break;
            }
            case SALIR:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo...\n";
                break;
        }
    } while(opcion != SALIR);
    eliminarDatosTabla(db);
    elimnarTabla1(db);
    eliminarDolares(db);
    return 0;
}