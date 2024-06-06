#include <iostream>
#include "prestamos.hpp"

// Enum para el menú principal.
enum Opciones {
    ATENCION = 1,
    INFO,
    SALIR
};

// Enum para el menú de atención al cliente.
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

int main() {
    int idCliente;
    std::cout << "Por favor ingrese su número de cédula: " << std::endl;
    std::cin >> idCliente;

    Prestamo prestamo1(1, 10000, 5, 12, 1, "Mensual");
    // Comprobar si el cliente está en la base de datos de clientIDs.
    
    int opcion;
    do {
        std::cout << "1. Atención al cliente." << std::endl;
        std::cout << "2. Obtener información sobre préstamos bancarios." << std::endl;
        std::cout << "3. Salir." << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cout << std::endl;
        
        switch(opcion) {
            case ATENCION: {
                int operacion;
                do {
                    std::cout << "1. Consultar el estado de cuenta." << std::endl;
                    std::cout << "2. Crear un certificado de depósito a plazo." << std::endl;
                    std::cout << "3. Consultar certificado de depósito a plazo." << std::endl;
                    std::cout << "4. Realizar una transferencia." << std::endl;
                    std::cout << "5. Realizar un depósito." << std::endl;
                    std::cout << "6. Solicitar un préstamo." << std::endl;
                    std::cout << "7. Realizar un abono a un préstamo (existente)." << std::endl;
                    std::cout << "8. Realizar un abono extraordinario a un préstamo (existente)." << std::endl;
                    std::cout << "9. Regresar al menú principal." << std::endl;
                    std::cout << "Seleccione una operación a realizar: ";
                    std::cin >> operacion;
                    std::cout << std::endl;

                    switch(operacion) {
                        case ESTADO:
                            // Lógica para consultar el estado de cuenta.
                            prestamo1.estadoPrestamo();
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
                            // Regresar al menú principal.
                            std::cout << "Regresando al menú principal...\n";
                            break;
                        default:
                            std::cout << "Opción no válida. Intente de nuevo...\n";
                            break;
                    }
                } while(operacion != REGRESAR);
                break;
            }
            case INFO:
                
                break;
            case SALIR:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo...\n";
                break;
        }
    } while(opcion != SALIR);

    return 0;
}
