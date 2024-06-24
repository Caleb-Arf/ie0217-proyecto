#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

void imprimirTablaAmortizacion1(double monto, double tasaInteres, int plazoMeses);
void obtenerTasaYPlazoDesdeTabla1(sqlite3 *db, const std::string& tipoPrestamo, double& tasaInteres, int& plazoMeses);
void imprimirResumenPrestamo1(const std::string& tipoPrestamo, double monto, double tasaInteres, int plazoMeses);
void obtenerTasaYPlazoDesdeTabla2(sqlite3 *db, const std::string& tipoPrestamo, double& tasaInteres, int& plazoMeses);

// Crea la base de datos de tipos de prestamos
void crearInfoPrestamos(sqlite3* db) {
    const char *sql_create_table = "CREATE TABLE DescripcionPrestamos ("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "Tipo TEXT NOT NULL,"
                                   "Descripcion TEXT NOT NULL);";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error creando la tabla: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Funcion auxiliar para insertar datos
void insertarPrestamo(sqlite3* db, const char* tipo, const char* descripcion) {
    const char *sql_insert = "INSERT INTO DescripcionPrestamos (Tipo, Descripcion) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    
    int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta de insercion: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    
    sqlite3_bind_text(stmt, 1, tipo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, descripcion, -1, SQLITE_STATIC);
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error al insertar datos: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Datos insertados correctamente" << std::endl;
    }
    
    sqlite3_finalize(stmt);
}

// Inserta datos de prestamos en la tabla de la base de datos
void insertarDatosPrestamos(sqlite3* db) {
    insertarPrestamo(db, "Prestamos Hipotecarios", "Los prestamos hipotecarios estan destinados a la compra de bienes raices, como casas o terrenos. El bien inmueble adquirido se utiliza como garantia del prestamo.\nTasa de Interes: Varian entre el 7% y el 9% anual, dependiendo del banco y las condiciones especificas del prestamo.");
    insertarPrestamo(db, "Prestamos Prendarios", "Los prestamos prendarios son aquellos que utilizan un bien mueble, como un vehiculo, joyas, o maquinaria, como garantia del prestamo. Son comunes para obtener liquidez rapida.\nTasa de Interes: Las tasas de interes para prestamos prendarios suelen ser mas altas que las de los hipotecarios, vaiando entre el 10% y el 15% anual.");
    insertarPrestamo(db, "Prestamos Personales", "Los prestamos personales se otorgan para diversos fines, como consolidacion de deudas, gastos medicos, viajes, etc. No requieren una garantia especifica, aunque pueden depender de la solvencia del solicitante.\nTasa de Interes: Varian tipicamente entre el 12% y el 25% anual, dependiendo del perfil crediticio del solicitante y el banco.");
    insertarPrestamo(db, "Prestamos para Vehiculo", "Estos prestamos estan disenados especificamente para la compra de vehiculos nuevos o usados. El vehiculo adquirido generalmente se utiliza como garantia del prestamo.\nTasa de Interes: Dicha tasa de interes suele estar en el rango del 7% al 12% anual, dependiendo del modelo del vehiculo y la institucion financiera.");
    insertarPrestamo(db, "Prestamos para Vivienda", "Estos estan destinados a la adquisicion, construccion, o mejora de una vivienda. La vivienda puede ser la garantia del prestamo.\nTasa de Interes: Oscilar entre el 6% y el 9% anual, dependiendo de las condiciones del prestamo y la institucion financiera.");
}

// Imprime los datos de la tabla de tipos de prestamos
void imprimirDatosPrestamos(sqlite3* db) {
    const char* consultaSQL = "SELECT * FROM DescripcionPrestamos;";
    sqlite3_stmt* declaracion;

    int rc = sqlite3_prepare_v2(db, consultaSQL, -1, &declaracion, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "Datos de la tabla Prestamos:" << std::endl;
    while ((rc = sqlite3_step(declaracion)) == SQLITE_ROW) {
        int id = sqlite3_column_int(declaracion, 0);
        const unsigned char* tipo = sqlite3_column_text(declaracion, 1);
        const unsigned char* descripcion = sqlite3_column_text(declaracion, 2);

        std::cout << "\nTipo: " << tipo << std::endl;
        std::cout << "Descripcion: " << descripcion << std::endl;
        std::cout << "-------------------------" << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(declaracion);
}


// Callback para impresion de tabla de Tasas CDP
static int callback(void *data, int argc, char **argv, char **azColName) {
    // Imprime los datos de la tabla.
    std::cout << std::setw(10) << (argv[0] ? argv[0] : "NULL") << " | "
              << std::setw(15) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(12) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(12) << (argv[3] ? argv[3] : "NULL") << std::endl;
    return 0;
}

//Imprime encabezados
void printTableHeaders() {
    std::cout << std::setw(40) << std::setfill(' ') << "Tasas de CDPs" << std::endl << std::endl;
    std::cout << std::setw(10) << "Id" << " | "
              << std::setw(15) << "Plazo en meses" << " | "
              << std::setw(12) << "Tasa en bolsa" << " | "
              << std::setw(12) << "Tasa en banco" << std::endl;
    std::cout << std::string(10, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(12, '-') << std::endl;
}

// Crea la tabla Tasas CDP
void crearCdp(sqlite3 *db) {
    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS TasasCDP ("
        "id INTEGER PRIMARY KEY UNIQUE,"
        "plazo TEXT,"
        "fisico_negociable_en_bolsa REAL,"
        "negociable_en_banco REAL"
        ");";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error creando la tabla: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Inserta datos en la tabla Tasas CDP
void insertarCdp(sqlite3 *db) {
    const char *sql_insert_data = 
        "INSERT INTO TasasCDP (id, plazo, fisico_negociable_en_bolsa, negociable_en_banco) VALUES"
        "(101, '1-6', NULL, 0.0018),"
        "(102, '7-13', NULL, 0.0020),"
        "(103, '14-20', NULL, 0.0062),"
        "(104, '21-29', NULL, 0.0121),"
        "(105, '30-59', 0.0301, 0.0311),"
        "(106, '60-80', 0.0345, 0.0355),"
        "(107, '90-119', 0.0388, 0.0398),"
        "(108, '120-149', 0.0453, 0.0463),"
        "(109, '150-179', 0.0501, 0.0511),"
        "(110, '180*-209', 0.0519, 0.0529),"
        "(111, '210-239', 0.0519, 0.0529),"
        "(112, '240-269', 0.0544, 0.0554),"
        "(113, '270-299', 0.0545, 0.0555),"
        "(114, '300-329', 0.0549, 0.0559),"
        "(115, '330-359', 0.0554, 0.0564),"
        "(116, '360-539', 0.0559, 0.0569),"
        "(117, '540-719', 0.0569, 0.0579),"
        "(118, '720-1079', 0.0604, 0.0614),"
        "(119, '1080-1439', 0.0624, 0.0634),"
        "(120, '1440-1799', 0.0638, 0.0648),"
        "(121, 'De 1800', 0.0652, 0.0662);";
    
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_insert_data, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error insertando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla Tasas CDP
void mostrarTablaTasas(sqlite3 *db) {
    const char *sql = "SELECT * FROM TasasCDP";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql, callback, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error ejecutando la consulta: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

// Elimina la tabla Tasas  CDP
void eliminarDatosTabla(sqlite3 *db) {
    const char *sql_delete_data = "DELETE FROM TasasCDP";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }
}


// Callback para impresion de tabla de Tasas en colones
static int callback1(void *data, int argc, char **argv, char **azColName) {
 // Imprime los datos de la tabla.
    std::cout << std::setw(55) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(15) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(12) << (argv[3] ? argv[3] : "NULL") << " | "
              << std::setw(10) << (argv[4] ? argv[4] : "NULL") << std::endl;
    
    return 0;
}

//Imprime encabezados
void printHeader1() {
    static bool printTitle = true;
    if (printTitle) {
        std::cout << std::setw(80) << std::setfill(' ') << "Tasas de prestamos en colones" << std::endl << std::endl;
        printTitle = false;
    }

    std::cout << std::setw(55) << "Credito" << " | "
              << std::setw(15) << "Tasa Efectiva %" << " | "
              << std::setw(12) << "Plazo Meses" << " | "
              << std::setw(10) << "Cuota Colones" << std::endl;
    std::cout << std::string(55, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << std::endl;
}

// Crea la tabla Tasas en colones
void crearTabla1(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS TasasColones (
            id INTEGER PRIMARY KEY UNIQUE,
            Credito TEXT,
            Tasa_Efectiva REAL,
            Plazo_Meses INTEGER,
            Cuota_Millon INTEGER
        );
    )";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Inserta datos en la tabla Tasas en colones
void insertarData1(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO TasasColones (id, Credito, Tasa_Efectiva, Plazo_Meses, Cuota_Millon) VALUES
        (012, 'Credito Personal Hipotecario colones (012)', 19.36, 240, 12281.84),
        (014, 'Prendario colones(014)', 10.50, 96, 7580.00),
        (093, 'Personal Back to Back Colones (093)', 11.51, 180, 11688.26),
        (041, 'Vehiculo Nuevo colones (041)', 16.03, 96, 17910.70),
        (024, 'Vivienda Consumo Cuota unica colones (024)', 13.85, 360, 8827.17),
        (070, 'Fiduciaria a corto plazo (070)', 18.85, 60, 25425.43),
        (059, 'Cancelacion de Pasivos - atraccion de clientes (059)', 17.85, 168, 16210.44);
    )";
    
    
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla Tasas en colones
void selectData1(sqlite3 *db) {
    const char* selectDataSQL = "SELECT * FROM TasasColones";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL, callback1, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

// Elimina la tabla Tasas en colones
void eliminarTabla1(sqlite3 *db) {
    const char* deleteTableSQL = "DROP TABLE IF EXISTS TasasColones";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, deleteTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Tabla eliminada exitosamente" << std::endl;
    }
}

// Callback para impresion de tabla de Tasas en dolares
static int callback3(void *data, int argc, char **argv, char **azColName) {  
    // Imprime los datos de la tabla.
    std::cout << std::setw(55) << (argv[1] ? argv[1] : "NULL") << " | "
              << std::setw(15) << (argv[2] ? argv[2] : "NULL") << " | "
              << std::setw(12) << (argv[3] ? argv[3] : "NULL") << " | "
              << std::setw(10) << (argv[4] ? argv[4] : "NULL") << std::endl;
    
    return 0;
}

//Imprime encabezados
void printHeader2() {
    static bool printTitle = true;
    if (printTitle) {
        std::cout << std::setw(80) << std::setfill(' ') << "Tasas de prestamos en dolares" << std::endl << std::endl;
        printTitle = false;
    }

    std::cout << std::setw(55) << "Credito" << " | "
              << std::setw(15) << "Tasa Efectiva %" << " | "
              << std::setw(12) << "Plazo Meses" << " | "
              << std::setw(10) << "Cuota $" << std::endl;
    std::cout << std::string(55, '-') << " | "
              << std::string(15, '-') << " | "
              << std::string(12, '-') << " | "
              << std::string(10, '-') << std::endl;
}

// Crea la tabla Tasas en dolares
void crearDolares(sqlite3 *db) {
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS TasasDolares (
            id INTEGER PRIMARY KEY,
            Credito TEXT,
            Tasa_Efectiva REAL,
            Plazo_Meses INTEGER,
            Cuota_USD INTEGER
        );
    )";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Tabla creada exitosamente" << std::endl;
    }
}

// Inserta datos en la tabla Tasas en dolares
void insertarDolares(sqlite3 *db) {
    const char* insertDataSQL = R"(
        INSERT INTO TasasDolares (id, Credito, Tasa_Efectiva, Plazo_Meses, Cuota_USD) VALUES
        (098, 'Credito Personal Hipotecario en Dolares (098)', 18.79, 180, 9.84),
        (018, 'Prendario Dolares(018)', 12.91, 360, 6.65),
        (094, 'Personal Back to Back Dolares (094)', 14.80, 180, 7.80),
        (090, 'Vehiculo Nuevo dolares (090)', 16.75, 96, 18.30),
        (024, 'Vivienda Consumo Cuota unica Dolares (024)', 14.18, 360, 7.17);
    )";
    
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Datos insertados exitosamente" << std::endl;
    }
}

// Selecciona y muestra datos de la tabla Tasas en dolares
void mostrarDolares(sqlite3 *db) {
    const char* selectDataSQL = "SELECT * FROM TasasDolares";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, selectDataSQL, callback3, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Consulta ejecutada exitosamente" << std::endl;
    }
}

// Elimina la tabla Tasas en dolares
void eliminarDolares(sqlite3 *db) {
    const char *sql_delete_data = "DELETE FROM TasasDolares";
    char *err_msg = nullptr;
    int rc = sqlite3_exec(db, sql_delete_data, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error eliminando datos: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    } else {
        std::cout << "Datos eliminados exitosamente" << std::endl;
    }
}

// Valida si existe la tabla
bool tablaExiste(sqlite3 *db, const std::string &nombreTabla) {
    std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + nombreTabla + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return rc == SQLITE_ROW;
    }
    return false;
}

// Solicita al usuario el monto del prestamo
double solicitarMonto1() {
    double monto;
    std::cout << "Ingrese el monto del prestamo: ";
    std::cin >> monto;
    return monto;
}

// Imprime el menu de seleccion de tipo de prestamo
void imprimirMenuTipo1(sqlite3 *db) {
    std::cout << "Seleccione el tipo de prestamo:" << std::endl;
    std::cout << "1. Credito Personal Hipotecario" << std::endl;
    std::cout << "2. Prestamo Prendario" << std::endl;
    std::cout << "3. Personal Back to Back" << std::endl;
    std::cout << "4. Prestamo Vehiculo Nuevo" << std::endl;
    std::cout << "5. Vivienda Consumo Cuota unica" << std::endl;
    std::cout << "6. Fiduciaria a Corto Plazo" << std::endl;
    std::cout << "7. Cancelacion de Pasivos" << std::endl;

    // Solicitar al usuario seleccionar el tipo de prestamo
    int opcion;
    std::cout << "\nIngrese el numero correspondiente al tipo de prestamo: ";
    std::cin >> opcion;

    // Mapear la opcion ingresada por el usuario al tipo de prestamo
    std::string tipoPrestamo;
    switch (opcion) {
        case 1:
            tipoPrestamo = "Credito Personal Hipotecario colones (012)";
            break;
        case 2:
            tipoPrestamo = "Prendario colones(014)";
            break;
        case 3:
            tipoPrestamo = "Personal Back to Back Colones (093)";
            break;
        case 4:
            tipoPrestamo = "Vehiculo Nuevo colones (041)";
            break;
        case 5:
            tipoPrestamo = "Vivienda Consumo Cuota unica colones (024)";
            break;
        case 6:
            tipoPrestamo = "Fiduciaria a corto plazo (070)";
            break;
        case 7:
            tipoPrestamo = "Cancelacion de Pasivos - atraccion de clientes (059)";
            break;
        default:
            std::cerr << "Opcion no valida" << std::endl;
            break;
    }

    // Solicitar al usuario el monto del prestamo
    double monto = solicitarMonto1();

    // Obtener la tasa de interes y el plazo desde la tabla segun el tipo de prestamo
    double tasaInteres = 0.0;
    int plazoMeses = 0;
    obtenerTasaYPlazoDesdeTabla1(db, tipoPrestamo, tasaInteres, plazoMeses);

    if (tasaInteres != 0.0 && plazoMeses != 0) {
        // Imprimir un resumen de los detalles del prestamo seleccionado
        imprimirResumenPrestamo1(tipoPrestamo, monto, tasaInteres, plazoMeses);
        // Imprimir la tabla de amortizacion
        imprimirTablaAmortizacion1(monto, tasaInteres, plazoMeses);
    }
}

// Obtiene la tasa de interes y el plazo desde la tabla segun el tipo de prestamo
void obtenerTasaYPlazoDesdeTabla1(sqlite3 *db, const std::string& tipoPrestamo, double& tasaInteres, int& plazoMeses) {
    std::string consultaSQL = "SELECT Tasa_Efectiva, Plazo_Meses FROM TasasColones WHERE Credito = '" + tipoPrestamo + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, consultaSQL.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            tasaInteres = sqlite3_column_double(stmt, 0);
            plazoMeses = sqlite3_column_int(stmt, 1);
        } else {
            std::cerr << "No se encontro informacion para el tipo de prestamo ingresado." << std::endl;
        }
    } else {
        std::cerr << "Error al ejecutar la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

// Imprime un resumen de los detalles del prestamo seleccionado
void imprimirResumenPrestamo1(const std::string& tipoPrestamo, double monto, double tasaInteres, int plazoMeses) {
    std::cout << "\nResumen del prestamo:" << std::endl;
    std::cout << "Tipo de prestamo: " << tipoPrestamo << std::endl;
    std::cout << "Monto: " << monto << std::endl;
    std::cout << "Tasa de interes: " << tasaInteres << "%" << std::endl;
    std::cout << "Plazo (meses): " << plazoMeses << std::endl;
}

// Calcula el pago mensual basado en la formula de amortizacion
double calcularPagoMensual1(double monto, double tasaInteres, int plazoMeses) {
    double tasaMensual = tasaInteres / 1200; // Convertir la tasa anual a mensual
    return (monto * tasaMensual) / (1 - pow(1 + tasaMensual, -plazoMeses));
}

// Imprime la tabla de amortizacion
void imprimirTablaAmortizacion1(double monto, double tasaInteres, int plazoMeses) {
    std::cout << "\nTabla de amortizacion" << std::endl;
    std::cout << "\nMes\tPago\t\tInteres\t\tPrincipal\tSaldo" << std::endl;
    double saldo = monto;
    double pagoTotal = 0.0;
    double interesTotal = 0.0;
    double principalTotal = 0.0;
    double pagoMensual = calcularPagoMensual1(monto, tasaInteres, plazoMeses);
    for (int mes = 1; mes <= plazoMeses; ++mes) {
        double interes = saldo * (tasaInteres / 1200);
        double principal = pagoMensual - interes;
        saldo -= principal;
        interesTotal += interes;
        principalTotal += principal;
        std::cout << mes << "\t" << pagoMensual << "\t\t" << interes << "\t\t" << principal << "\t\t" <<std::fixed << std::setprecision(2) << std::abs(saldo) << std::endl;
    }
    std::cout << "Total:\t" << " " << "\t\t" << interesTotal << "\t" << principalTotal << "\t" << std::fixed << std::setprecision(2) << std::abs(saldo) << std::endl;
}

// Imprime el menu de seleccion de tipo de prestamo
void imprimirMenuTipo2(sqlite3 *db) {
    std::cout << "Seleccione el tipo de prestamo:" << std::endl;
    std::cout << "1. Credito Personal Hipotecario" << std::endl;
    std::cout << "2. Prestamo Prendario" << std::endl;
    std::cout << "3. Personal Back to Back" << std::endl;
    std::cout << "4. Prestamo Vehiculo Nuevo" << std::endl;
    std::cout << "5. Vivienda Consumo Cuota unica" << std::endl;


    // Solicitar al usuario seleccionar el tipo de prestamo
    int opcion;
    std::cout << "\nIngrese el numero correspondiente al tipo de prestamo: ";
    std::cin >> opcion;

    // Mapear la opcion ingresada por el usuario al tipo de prestamo
    std::string tipoPrestamo;
    switch (opcion) {
        case 1:
            tipoPrestamo = "Credito Personal Hipotecario en Dolares (098)";
            break;
        case 2:
            tipoPrestamo = "Prendario Dolares(018)";
            break;
        case 3:
            tipoPrestamo = "Personal Back to Back Dolares (094)";
            break;
        case 4:
            tipoPrestamo = "Vehiculo Nuevo dolares (090)";
            break;
        case 5:
            tipoPrestamo = "Vivienda Consumo Cuota unica Dolares (024)";
            break;
        default:
            std::cerr << "Opcion no valida" << std::endl;
            break;
    }

    // Solicitar al usuario el monto del prestamo
    double monto = solicitarMonto1();

    // Obtener la tasa de interes y el plazo desde la tabla segun el tipo de prestamo
    double tasaInteres = 0.0;
    int plazoMeses = 0;
    obtenerTasaYPlazoDesdeTabla2(db, tipoPrestamo, tasaInteres, plazoMeses);

    if (tasaInteres != 0.0 && plazoMeses != 0) {
        // Imprimir un resumen de los detalles del prestamo seleccionado
        imprimirResumenPrestamo1(tipoPrestamo, monto, tasaInteres, plazoMeses);
        // Imprimir la tabla de amortizacion
        imprimirTablaAmortizacion1(monto, tasaInteres, plazoMeses);
    }
}

// Funcion para obtener la tasa de interes y el plazo desde la tabla segun el tipo de prestamo
void obtenerTasaYPlazoDesdeTabla2(sqlite3 *db, const std::string& tipoPrestamo, double& tasaInteres, int& plazoMeses) {
    std::string consultaSQL = "SELECT Tasa_Efectiva, Plazo_Meses FROM TasasDolares WHERE Credito = '" + tipoPrestamo + "'";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, consultaSQL.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            tasaInteres = sqlite3_column_double(stmt, 0);
            plazoMeses = sqlite3_column_int(stmt, 1);
        } else {
            std::cerr << "No se encontro informacion para el tipo de prestamo ingresado." << std::endl;
        }
    } else {
        std::cerr << "Error al ejecutar la consulta SQL: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}







//int main() {
//    sqlite3 *db;
//    int rc = sqlite3_open("datos_financieros.db", &db);
//    if (rc) {
//        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
//        return 1;
//    } else {
//        std::cout << "Base de datos abierta exitosamente" << std::endl;
//    }
//
//    if (!tablaExiste(db, "tasas")) {
//        // Crear tabla para tasas de CDPs
//        crearCdp(db);
//        insertarCdp(db);
//        mostrarTablaTasas(db);
//       // eliminarDatosTabla(db);
//    } else {
//        std::cout << "La tabla de tasas ya existe, no es necesario crearla" << std::endl;
//    }
//
//    if (!tablaExiste(db, "TasasColones")) {
//        // Crear tabla para prestamos en colones
//        crearTabla1(db);
//        insertarData1(db);
//        selectData1(db);
//       // eliminarTabla1(db);
//    } else {
//        std::cout << "La tabla de tasas ya existe, no es necesario crearla" << std::endl;
//    }
//    
//    if (!tablaExiste(db, "TasasDolares")) {
//        // Crear tabla para prestamos en dolares
//        crearDolares(db);
//        insertarDolares(db);
//        mostrarDolares(db);
//       // eliminarDolares(db);
//    } else {
//        std::cout << "La tabla de tasas ya existe, no es necesario crearla" << std::endl;
//    }
//
//    std::cout << "Base de datos cerrada exitosamente" << std::endl;
//    sqlite3_close(db);
//    return 0;
//}
//