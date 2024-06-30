#ifndef CLIENTES2_HPP
#define CLIENTES2_HPP

#include <iostream>
#include <sqlite3.h>
#include <string>

/**
 * @brief Clase que representa un cliente y permite interactuar con la base de datos.
 */
class Cliente {
private:
    sqlite3* db; ///< Puntero a la base de datos SQLite.
    int idCliente; ///< ID del cliente.

public:
    /**
     * @brief Obtiene el ID del cliente.
     * @return ID del cliente.
     */
    int getIdCliente() const;

    /**
     * @brief Constructor de la clase Cliente.
     * @param db Puntero a la base de datos SQLite.
     * @param idCliente ID del cliente.
     */
    Cliente(sqlite3* db, int idCliente);

    /**
     * @brief Obtiene información de los clientes desde la base de datos.
     * @param tabla Nombre de la tabla de la cual obtener la información.
     * @param dato Nombre del dato a obtener.
     * @param idCliente ID del cliente.
     * @return Información solicitada.
     */
    std::string getInfoClientes(const std::string& tabla, const std::string& dato, int idCliente);

    /**
     * @brief Actualiza la información de los clientes en la base de datos.
     * @param tabla Nombre de la tabla en la cual actualizar la información.
     * @param dato Nombre del dato a actualizar.
     * @param datoActualizado Nuevo valor del dato.
     * @param idCliente ID del cliente.
     */
    void setInfoClientes(const std::string& tabla, const std::string& dato, const std::string& datoActualizado, int idCliente);

    /**
     * @brief Obtiene información de las tasas de interés desde la base de datos.
     * @param tabla Nombre de la tabla de la cual obtener la información.
     * @param dato Nombre del dato a obtener.
     * @param id ID asociado.
     * @return Información solicitada.
     */
    std::string getInfoInteres(const std::string& tabla, const std::string& dato, int id);

    /**
     * @brief Obtiene información de los préstamos desde la base de datos.
     * @param dato Nombre del dato a obtener.
     * @param idPrestamos ID del préstamo.
     * @return Información solicitada.
     */
    std::string getInfoPrestamos(const std::string& dato, int idPrestamos);

    /**
     * @brief Actualiza la información de los préstamos en la base de datos.
     * @param dato Nombre del dato a actualizar.
     * @param datoActualizado Nuevo valor del dato.
     * @param idPrestamo ID del préstamo.
     */
    void setInfoPrestamos(const std::string& dato, const std::string& datoActualizado, int idPrestamo);

    /**
     * @brief Obtiene información de las tasas de CDP desde la base de datos.
     * @param dato Nombre del dato a obtener.
     * @param idCDP ID del CDP.
     * @return Información solicitada.
     */
    std::string getInfoTasasCDP(const std::string& dato, int idCDP);

    /**
     * @brief Obtiene información de los CDPs desde la base de datos.
     * @param dato Nombre del dato a obtener.
     * @param idCDP ID del CDP.
     * @return Información solicitada.
     */
    std::string getInfoCDPs(const std::string& dato, int idCDP);

    /**
     * @brief Actualiza la información de los CDPs en la base de datos.
     * @param dato Nombre del dato a actualizar.
     * @param datoActualizado Nuevo valor del dato.
     * @param idCDP ID del CDP.
     */
    void setInfoCDPs(const std::string& dato, const std::string& datoActualizado, int idCDP);
};

#endif // CLIENTES2_HPP

