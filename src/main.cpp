#include <iostream>

//enum para el menú.

enum Opciones{
    ATENCION = 1,
    INFO,
    SALIR
};

enum Atencion{
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

main(){
    int idCliente;
    std::cout << "Por favor ingrese su número de cédula: " << std::endl;
    std::cin >> idCliente;

    //comprobar si el cliente está en la base de datos de clientIDs.
    

    int opcion;
    do{

        std::cout << "1. Atención al cliente." << std::endl;
        std::cout << "2. Obtener información sobre préstamos bancarios." << std::endl;
        std::cout << "3. Salir." << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cout << std::endl;

        switch(opcion){
            
            case ATENCION:
                int operacion;
                
                do{
                    std::cout << "1. Consultar el estado de cuenta." << std::endl;
                    std::cout << "2. Crear un certificado de depósito a plazo." << std::endl;
                    std::cout << "3. Consultar certificado de depósito a plazo." << std::endl;
                    std::cout << "4. Realizar una transferencia." << std::endl;
                    std::cout << "5. Realizar un depósito." << std::endl;
                    std::cout << "6. Solicitar un préstamo." << std::endl;
                    std::cout << "7. Realizar un abono a un préstamo (existente)." << std::endl;
                    std::cout << "8. Realizar un abono extraordinario a un préstamo (existente)." << std::endl;
                    std::cout << "9. Regresar al menú principal." << std::endl;
                    std::cout << "Seleccione una opción: ";
                    std::cin >> operacion;
                    std::cout << std::endl;

                    switch(operacion){
                        
                        case ESTADO:
                            //desplegar el estado de cuenta.
                            break;
                        case CREARCDP:
                            //crear certificado de depósito a plazo.
                            break;
                        case CONSULTARCDP:
                            //desplegar el estado del CDP.
                            break;
                        case TRANSFERENCIA:
                            //realizar una transferencia.
                            break;
                        case DEPOSITO:
                            //realizar un depósito.
                            break;
                        case SOLICITARP:
                            //operación de solicitar préstamo.
                            break;
                        case ABONARP:
                            //operación de abonar a un préstamo.
                            break;
                        case ABONAREXTRAP:
                            //operación de abono extraordinario.
                            break;
                        case REGRESAR:
                            std::cout << "Regresando al menú principal...";
                            break;
                        default:
                            std::cout << "Opcion no valida. Intente de nuevo...\n";
                            break;
                    }
                }
                while(opcion != REGRESAR);
            
            case INFO:

            case SALIR:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo...\n"; 
                break;   
        }
    }
    while(opcion != SALIR);
    return 0;
}

 