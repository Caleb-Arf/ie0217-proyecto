#ifndef OPERACIONES_HPP
#define OPERACIONES_HPP

#include "sqlite3.h"
#include "clientes2.hpp" 

/**
 * @brief Clase que representa operaciones bancarias para un cliente.
 */
class Operacion {
private:
    sqlite3* db; ///< Puntero a la base de datos SQLite.
    Cliente* cliente; ///< Puntero al cliente asociado a las operaciones.

public:
    /**
     * @brief Constructor de la clase Operacion.
     * 
     * @param db Puntero a la base de datos SQLite.
     * @param cliente Puntero al cliente asociado a las operaciones.
     */
    Operacion(sqlite3* db, Cliente* cliente);

    /**
     * @brief Realiza una transferencia de dinero a otro cliente.
     * 
     * @param montoTransferencia Monto a transferir.
     * @param idDestino ID del cliente destino de la transferencia.
     */
    void transferencia(double montoTransferencia, int idDestino);

    /**
     * @brief Realiza un depósito en la cuenta del cliente.
     * 
     * @param montoDeposito Monto a depositar.
     */
    void deposito(double montoDeposito);

    /**
     * @brief Crea un préstamo para el cliente.
     * 
     * @param idCliente ID del cliente para el cual se crea el préstamo.
     * @return ID del préstamo creado.
     */
    int crearPrestamo(int idCliente);

    /**
     * @brief Realiza un abono al préstamo del cliente.
     */
    void abonoPrestamo();

    /**
     * @brief Realiza un abono extraordinario al préstamo del cliente.
     */
    void abonoPrestamoExtraordinario();

    /**
     * @brief Crea un Certificado de Depósito a Plazo (CDP) para el cliente.
     * 
     * @param idCliente ID del cliente para el cual se crea el CDP.
     */
    void crearCDP(int idCliente);

    /**
     * @brief Consulta el Certificado de Depósito a Plazo (CDP) del cliente.
     */
    void consultarCDP();
};

/**
 * @brief Obtiene la fecha actual como una cadena de caracteres.
 * 
 * @return Cadena de caracteres que representa la fecha actual.
 */
std::string obtenerFechaActual();

#endif // OPERACIONES_HPP
