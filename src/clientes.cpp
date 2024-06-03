#include <iostream>
#include <sqlite3.h>

static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

int main() {
    sqlite3 *db;
    const char* dbFile = "clientes.db";
    char *errMsg = 0;
    int rc;

    // Abrir una conexion a la base de datos
    rc = sqlite3_open("clientes.db", &db);
    if (rc) {
        std::cerr << "No se puede abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    }

    // Crear tabla Clientes
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Clientes (
            IdCliente INTEGER PRIMARY KEY,
            Cedula TEXT,
            Nombre TEXT,
            Telefono TEXT,
            Direccion TEXT,
            Correo TEXT,
            Balance REAL,
            Prestamos TEXT,
            TipoPrestamo TEXT
        );
    )";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Insertar datos en la tabla
    const char* insertDataSQL = R"(
        INSERT INTO Clientes (IdCliente, Cedula, Nombre, Telefono, Direccion, Correo, Balance, Prestamos, TipoPrestamo) VALUES
        (701006, 702890948, 'YAKIR HERMAN BUSTOS', '6543 1234', 'San Jose, Barrio Escalante', 'yakir.herman@hotmail.com', 4421987.12, 'SI', 'H01'),
        (701027, 702890950, 'MARLENNY MAROTO GUADAMUZ', '8745 6789', 'Heredia, San Francisco', 'marleny.maroto@yahoo.com', 2310985.98, 'NO', NULL),
        (701019, 702890951, 'ANNIA CORTES SOLANO', '9032 1567', 'Alajuela, San Rafael', 'annia.cortes@gmail.com', 1298745.22, 'NO', NULL),
        (701014, 702890952, 'LILLIAM VILLAVICENCIO HIDALGO', '7834 9087', 'Cartago, Paraiso', 'lilliam.villavicencio@hotmail.com', 450987.45, 'NO', NULL),
        (504004, 504380806, 'ANA HERNANDEZ TORRES', '6012 3456', 'San Jose, La Sabana', 'ana.hernandez@yahoo.com', 654987.33, 'SI', 'H02'),
        (506016, 504380807, 'VERA SOLANO TORRES', '7890 2345', 'Guanacaste, Liberia', 'vera.solano@gmail.com', 892164.22, 'SI', 'PR02'),
        (213035, 504380808, 'GLENDA ALVARADO RAMIREZ', '8901 5678', 'Puntarenas, Jaco', 'glenda.alvarado@hotmail.com', 765431.99, 'SI', 'PE01'),
        (501016, 504380809, 'ELIECER UREÑA LEIVA', '6789 1234', 'Limon, Puerto Viejo', 'eliecer.urena@yahoo.com', 345876.88, 'NO', NULL),
        (505002, 504380810, 'FERNANDO AGUILAR JIMENEZ', '7654 8901', 'San Jose, Santa Ana', 'fernando.aguilar@gmail.com', 987654.11, 'SI', 'PE02'),
        (305001, 302940001, 'FERNANDO MONTERO MATA', '8902 3456', 'Heredia, Santo Domingo', 'fernando.montero@hotmail.com', 123456.77, 'SI', 'VE01'),
        (301006, 302940002, 'BEATRIZ MORA JIMENEZ', '6548 7231', 'Alajuela, Grecia', 'beatriz.mora@yahoo.com', 456789.55, 'NO', NULL),
        (301018, 302940003, 'NICOLAS JIMENEZ CORDERO', '9012 6789', 'Cartago, Oreamuno', 'nicolas.jimenez@gmail.com', 987654.33, 'SI', 'VE02'),
        (118006, 302940004, 'TRINIDAD VINDAS PEREZ', '7832 5678', 'San Jose, Pavas', 'trinidad.vindas@hotmail.com', 222345.22, 'SI', 'VIV01'),
        (301016, 302940005, 'INOCENCIA MEZA VEGA', '6784 1234', 'Guanacaste, Tamarindo', 'inocencia.meza@yahoo.com', 555555.11, 'NO', NULL),
        (102007, 114310431, 'GERMAN CARVAJAL BERMUDEZ', '8906 3456', 'Puntarenas, Monteverde', 'german.carvajal@gmail.com', 333333.77, 'NO', NULL),
        (118003, 114310432, 'BENITIVO ARIAS CAMPOS', '6541 8901', 'Limon, Cahuita', 'benitivo.arias@hotmail.com', 777777.99, 'SI', 'VIV02'),
        (101026, 114310433, 'POMPILIO DIAZ CHINCHILLA', '7823 5678', 'San Jose, Escazu', 'pompilio.diaz@yahoo.com', 444444.88, 'NO', NULL),
        (101012, 114310435, 'CARMEN PARRA PARRA', '9018 1234', 'Heredia, Barva', 'carmen.parra@gmail.com', 666666.66, 'NO', NULL),
        (102001, 114310436, 'DAISY DURAN CHINCHILLA', '6787 3456', 'Alajuela, Naranjo', 'daisy.duran@hotmail.com', 888888.55, 'SI', 'PE01'),
        (101018, 111340989, 'FLORA CORELLA CORELLA', '7652 8901', 'Cartago, El Guarco', 'flora.corella@yahoo.com', 999999.33, 'NO', NULL),
        (103021, 111340991, 'EMMANUEL VARELA CASTRO', '8907 5678', 'San Jose, Rohrmoser', 'emmanuel.varela@gmail.com', 222222.22, 'SI', 'VIV01'),
        (303003, 111340993, 'GABRIELA CUBILLO ALFARO', '6545 1234', 'Guanacaste, Playa del Coco', 'gabriela.cubillo@hotmail.com', 111111.11, 'NO', NULL),
        (401006, 111340994, 'BRANDON PORRAS BARRANTES', '7835 3456', 'Puntarenas, Puntarenas Centro', 'brandon.porras@yahoo.com', 7777777.99, 'SI', 'H02'),
        (815001, 111340995, 'EIDA CHACON MEZA', '9015 8901', 'Limon, Limon Centro', 'eida.chacon@gmail.com', 8888888.88, 'NO', NULL),
        (101007, 111340996, 'ALVARO MONGE SANABRIA', '6781 5678', 'San Jose, Curridabat', 'alvaro.monge@hotmail.com', 9999999.66, 'NO', NULL),
        (103026, 104270061, 'JULIETA DELGADO ALVARADO', '7658 1234', 'Heredia, San Joaquin', 'julieta.delgado@yahoo.com', 1234567.22, 'NO', NULL),
        (104002, 104270062, 'GLORIA DIAZ PALMA', '8903 3456', 'Alajuela, Sarchi', 'gloria.diaz@gmail.com', 9876543.11, 'SI', 'VIV01'),
        (601095, 104270066, 'ANGELOBERNARDO CORDERO FOLLANO', '6549 8901', 'Cartago, Turrialba', 'angelobernardo.cordero@hotmail.com', 8765432.33, 'NO', NULL),
        (101033, 104270067, 'MABETH ABREGO TRAÑA', '7837 5678', 'San Jose, Desamparados', 'mabeth.abrego@yahoo.com', 7654321.77, 'NO', NULL),
        (104001, 104270068, 'STEPHANI SANTAMARIA SALAZAR', '9013 1234', 'Guanacaste, Santa Cruz', 'stephani.santamaria@gmail.com', 6543210.99, 'NO', NULL),
        (215001, 104270069, 'LINA ARIAS ALFARO', '6785 3456', 'Puntarenas, Paquera', 'lina.arias@hotmail.com', 5432109.88, 'SI', 'VE01'),
        (101008, 104270070, 'ERASMO CALDERON JIMENEZ', '7656 8901', 'Limon, Guapiles', 'erasmo.calderon@yahoo.com', 4321098.66, 'NO', NULL),
        (301028, 104270071, 'GLORIA ROSALES CASTRO', '8904 5678', 'San Jose, Hatillo', 'gloria.rosales@gmail.com', 3210987.55, 'NO', NULL),
        (301019, 104270072, 'BLADIMIR VILLALOBOS BARQUERO', '6542 1234', 'Heredia, Belen', 'bladimir.villalobos@hotmail.com', 2109876.33, 'NO', NULL),
        (301021, 104270073, 'ELENA ESQUIVEL MIRANDA', '7838 3456', 'Alajuela, Poas', 'elena.esquivel@yahoo.com', 1098765.22, 'SI', 'H01'),
        (103033, 101141655, 'DANIEL VASQUEZ MORA', '8905 5678', 'San Jose, Moravia', 'daniel.vasquez@gmail.com', 8765432.33, 'SI', 'VIV01'),
        (112007, 101142031, 'HEATHER SIBAJA VARGAS', '6546 1234', 'Heredia, Belen', 'heather.sibaja@hotmail.com', 7654321.66, 'SI', 'VIV02'),
        (119001, 101164392, 'JENGER UZIEL MATARRITA BERMUDEZ', '7831 3456', 'Alajuela, Palmares', 'jenger.matarrita@yahoo.com', 6543210.55, 'SI', 'H02'),
        (823001, 101240037, 'MELANIE FIORELLA SOLANO MENA', '9014 8901', 'Cartago, La Union', 'melanie.solano@gmail.com', 5432109.33, 'SI', 'PR02'),
        (601047, 101240732, 'HILLARY FABIOLA ANCHIA GUTIERREZ', '6782 5678', 'San Jose, Hatillo', 'hillary.anchia@hotmail.com', 8765432.22, 'NO', NULL),
        (103008, 101280947, 'CALET SCOTT MURILLO PANIAGUA', '7659 1234', 'Guanacaste, Nosara', 'calet.murillo@yahoo.com', 7654321.11, 'SI', 'VE02'),
        (101010, 101290149, 'JUSTIN MAURICIO ALVARADO GUADAMUZ', '8908 3456', 'Puntarenas, Parrita', 'justin.alvarado@gmail.com', 6543210.77, 'SI', 'VIV01'),
        (104014, 101290354, 'DARLYN DANELIZ COLINDRES FONSECA', '6542 8901', 'Limon, Siquirres', 'darlyn.colindres@hotmail.com', 5432109.22, 'NO', NULL),
        (102002, 101310431, 'SONIA PAMELA BARRANTES CHAVARRIA', '7838 5678', 'San Jose, Tibas', 'sonia.barrantes@yahoo.com', 4321098.99, 'SI', 'H01'),
        (107001, 101310983, 'ROSA ISELA MATA QUIROS', '9019 1234', 'Heredia, Flores', 'rosa.mata@gmail.com', 8765432.66, 'SI', 'PR01'),
        (201048, 101320047, 'JUAN ENRIQUE RAMIREZ CANTILLO', '6783 3456', 'Alajuela, San Carlos', 'juan.ramirez@hotmail.com', 7654321.33, 'NO', NULL),
        (113007, 101320433, 'DORA EMILIA CARDENAS ARCE', '7657 8901', 'Cartago, Jimenez', 'dora.cardenas@yahoo.com', 6543210.88, 'SI', 'VE01'),
        (201037, 207070179, 'GABRIEL ESTEBAN AVILA MOLINA', '8900 5678', 'San Jose, Zapote', 'gabriel.avila@gmail.com', 5432109.66, 'NO', NULL),
        (201049, 207070180, 'KATHERINE ALEJANDRA CASTRO AGUILAR', '6547 1234', 'Guanacaste, Nicoya', 'katherine.castro@hotmail.com', 6543210.22, 'SI', 'VIV02'),
        (205010, 207070181, 'MIGUEL ANGEL PERLAZA SOLANO', '7833 3456', 'Puntarenas, Esparza', 'miguel.perlaza@yahoo.com', 5432109.11, 'SI', 'H02'),
        (201056, 207070182, 'ALISON VALERIA ROJAS MARIN', '9017 8901', 'Limon, Matina', 'alison.rojas@gmail.com', 6543210.77, 'SI', 'PR02'),
        (604001, 207070183, 'RAMON ESTEBAN RODRIGUEZ CORDERO', '6788 5678', 'San Jose, Guadalupe', 'ramon.rodriguez@hotmail.com', 5432109.33, 'SI', 'PE02'),
        (201021, 207070184, 'ADRIANA GUISELLE MENA SANCHEZ', '7650 1234', 'Heredia, San Isidro', 'adriana.mena@yahoo.com', 4321098.88, 'SI', 'VE02'),
        (210020, 207070185, 'BLANCA STEPHANY DIAZ HENRIQUEZ', '8904 3456', 'Alajuela, Upala', 'blanca.diaz@gmail.com', 7689345765, 'NO', NULL),
        (201003, 207070186, 'EDUARDO JOSUE DIAZ BRENES', '6540 8901', 'Cartago, Alvarado', 'eduardo.diaz@hotmail.com', 5678943299, 'NO', NULL),
        (208011, 207070187, 'TANIA ELIETH CALDERON FERNANDEZ', '7839 5678', 'San Jose, San Pedro', 'tania.calderon@yahoo.com', 6778943266, 'SI', 'H01'),
        (201042, 207070188, 'MARTA EDUVIGES MADRIGAL CHAVARRIA', '9016 1234', 'Guanacaste, Cañas', 'marta.madrigal@gmail.com', 6543908765, 'SI', 'PR01'),
        (301003, 301540724, 'JOSE FRANCISCO DUARTE QUESADA', '6786 3456', 'Puntarenas, Buenos Aires', 'jose.duarte@hotmail.com', 7901234568, 'NO', NULL),
        (301038, 301540729, 'ANA MARIA PEREZ PEREZ', '7653 8901', 'Limon, Pococi', 'ana.perez@yahoo.com', 8234567890, 'SI', 'VE01'),
        (301027, 301540730, 'MARIA JOSEFA CARVAJAL AGUERO', '8909 5678', 'San Jose, Aserri', 'maria.carvajal@gmail.com', 7432654987, 'SI', 'VIV01'),
        (301002, 301540732, 'JOSE VICENTE ACUÑA ACUÑA', '6544 1234', 'Heredia, Sarapiqui', 'jose.acuna@hotmail.com', 7865432191, 'SI', 'VIV02'),
        (307012, 301540739, 'ALEXANDER DAVID HERNANDEZ ROJAS', '7836 3456', 'Alajuela, Zarcero', 'alexander.hernandez@yahoo.com', 8543210988, 'NO', NULL),
        (108006, 301540740, 'KATHERINE MARIA CAMPOS MOLINA', '9011 8901', 'Cartago, Cervantes', 'katherine.campos@gmail.com', 9009876543, 'NO', NULL),
        (307001, 301540742, 'LUIS ENRIQUE TRAÑA TRAÑA', '6780 5678', 'San Jose, Goicoechea', 'luis.trana@hotmail.com', 8001234568, 'SI', 'PE02'),
        (305010, 301540746, 'LUIS DIEGO SANCHEZ RAMIREZ', '7655 1234', 'Guanacaste, Bagaces', 'luis.sanchez@yahoo.com', 7321654988, 'NO', NULL),
        (301001, 301540747, 'WALTER GERARDO SOTO VARGAS', '8902 3456', 'Puntarenas, Corredores', 'walter.soto@gmail.com', 8765432190, 'NO', NULL),
        (301004, 301540748, 'EMMANUEL JOSE RODRIGUEZ SALAZAR', '6541 8901', 'Limon, Valle La Estrella', 'emmanuel.rodriguez@hotmail.com', 7098765432, 'SI', 'VIV02'),
        (307003, 301540749, 'KEVIN ALFONSO CASTILLO VIQUEZ', '7834 5678', 'San Jose, Puriscal', 'kevin.castillo@yahoo.com', 8654987235, 'SI', 'H01'),
        (814004, 901520615, 'ADOLFO HUMBERTO AGUILAR CORTES', '9010 1234', 'Heredia, San Pablo', 'adolfo.aguilar@gmail.com', 9456782345, 'NO', NULL),
        (814007, 901520636, 'BLANCA ROSA RAMIREZ BRENES', '6789 3456', 'Alajuela, San Mateo', 'blanca.ramirez@hotmail.com', 8234908765, 'NO', NULL),
        (201005, 901520655, 'MARCO TULIO GONZALEZ MOYA', '7654 8901', 'Cartago, Cot', 'marco.gonzalez@yahoo.com', 8654982134, 'NO', NULL),
        (827001, 901520661, 'ANNIA MARIA SERRANO CARVAJAL', '8903 5678', 'San Jose, San Sebastian', 'annia.serrano@gmail.com', 9456723423, 'NO', NULL),
        (827002, 901520662, 'FLOR MARIA NAVARRO MORALES', '6548 1234', 'Guanacaste, Tilaran', 'flor.navarro@hotmail.com', 8567439822, 'NO', NULL),
        (824002, 901520664, 'LIDIETH MARGARITA NUÑEZ FUENTES', '7837 3456', 'Puntarenas, Golfito', 'lidieth.nunez@yahoo.com', 258974.66, 'NO', NULL),
        (101006, 901520666, 'MARIA CECILIA GARITA MONTENEGRO', '9012 8901', 'Limon, Bataan', 'maria.garita@gmail.com', 123458.44, 'SI', 'PR02'),
        (215014, 901520684, 'IDALIA NAYELI HERRERA MENDEZ', '6784 5678', 'San Jose, Tarrazu', 'idalia.herrera@hotmail.com', 98436.33, 'NO', NULL),
        (814006, 901450847, 'KATHERYN MICHELL VALVERDE GONZALEZ', '7651 1234', 'Heredia, Vara Blanca', 'katheryn.valverde@yahoo.com', 196543.11, 'NO', NULL),
        (814008, 901450851, 'JACQUELINE MARIA DAVIS VIQUEZ', '8905 3456', 'Alajuela, Poas', 'jacqueline.davis@gmail.com', 78965.22, 'NO', NULL),
        (119112, 901450852, 'VICTORIA ALESSANDRA SOLIS BRAVO', '6549 8901', 'Cartago, Pacayas', 'victoria.solis@hotmail.com', 123477.77, 'NO', NULL),
        (505007, 901450856, 'MARIA PAULA HERNANDEZ OVIEDO', '7838 5678', 'San Jose, Dota', 'maria.hernandez@yahoo.com', 234567.99, 'NO', NULL),
        (814001, 901450859, 'JESIEL ALEJANDRO CORTEZ CANO', '9013 1234', 'Guanacaste, Hojancha', 'jesiel.cortez@gmail.com', 54321.11, 'NO', NULL),
        (814009, 901450863, 'PAULA SOFIA LEZCANO ARAYA', '6785 3456', 'Puntarenas, Osa', 'paula.lezcano@hotmail.com', 123456.55, 'NO', NULL),
        (827003, 901450864, 'MARITZA ESTHER OREAMUNO COREA', '7658 8901', 'Limon, Hone Creek', 'maritza.oreamuno@yahoo.com', 87654.77, 'SI', 'VE01'),
        (704004, 901450879, 'EVANGELINA NOEL CHAVES TRITLE', '8907 5678', 'San Jose, Perez Zeledon', 'evangelina.chaves@gmail.com', 23456.22, 'SI', 'VIV01'),
        (214009, 901450881, 'KARLA MARJIANN SOLANO FERNANDEZ', '6543 1234', 'Heredia, San Rafael de Heredia', 'karla.solano@hotmail.com', 87654.66, 'NO', NULL),
        (814005, 901450882, 'KEYLOR FAURICIO ZUÑIGA VINDAS', '7831 3456', 'Alajuela, Los Chiles', 'keylor.zuniga@yahoo.com', 8765.33, 'SI', 'H02'),
        (610023, 901450883, 'STEPHANIE MARIA OROZCO ROJAS', '9014 8901', 'Cartago, San Nicolas', 'stephanie.orozco@gmail.com', 6789.11, 'SI', 'PR02'),
        (213015, 901450885, 'MIA CASSANDRA RAMOS FALLAS', '6786 5678', 'San Jose, Montes de Oca', 'mia.ramos@hotmail.com', 98765.77, 'SI', 'PE02'),
        (213014, 901450886, 'CARLOS ANDRES CAAMAÑO LONDOÑO', '7656 1234', 'Guanacaste, La Cruz', 'carlos.caamano@yahoo.com', 43211.99, 'SI', 'VE02'),
        (214016, 901450916, 'DENIS BAYARDO ALEMAN BRENES', '8908 3456', 'Puntarenas, Cobano', 'denis.aleman@gmail.com', 98765.88, 'NO', NULL),
        (210080, 901450920, 'KATHIA ELIZABETH GUERRA CABALLERO', '6542 8901', 'Limon, Bri Bri', 'kathia.guerra@hotmail.com', 54321.33, 'SI', 'VIV02'),
        (824001, 901450922, 'MELVIN ANTONIO ABURTO GUZMAN', '7839 5678', 'San Jose, Leon Cortes', 'melvin.aburto@yahoo.com', 98765.22, 'NO', NULL),
        (119006, 901450923, 'MAURICIO ANTONIO ABURTO GUZMAN', '9019 1234', 'Heredia, La Ribera', 'mauricio.aburto@gmail.com', 87654.11, 'SI', 'PR01'),
        (402010, 901450924, 'CESAR ESTEYLOR ARCE AMAYA', '6782 3456', 'Alajuela, Atenas', 'cesar.arce@hotmail.com', 65432.55, 'SI', 'PE01'),
        (404004, 901450999, 'MILENA CRISTOBALINA MORERA DUMAS', '7657 8901', 'Cartago, Juan Viñas', 'milena.morera@yahoo.com', 98765.77, 'SI', 'VE01'),
        (821001, 901460001, 'LEYLA YAHAIRA NUÑEZ MEDAL', '8900 5678', 'San Jose, Coronado', 'leyla.nunez@gmail.com', 23456.99, 'SI', 'VIV01'),
        (119119, 901460004, 'CHRISTOPHER ALBERTO PRADO QUESADA', '6545 1234', 'Guanacaste, Santa Rosa', 'christopher.prado@hotmail.com', 87654.88, 'NO', NULL),
        (802001, 901460006, 'WILLIAN STEWART RAMIREZ GONZALEZ', '7836 3456', 'Puntarenas, Paquera', 'willian.ramirez@yahoo.com', 23456.33, 'SI', 'H02'),
        (110005, 901460009, 'JOHANNES GABRIEL LEHRL FERNANDEZ', '9018 8901', 'Limon, Pandora', 'johannes.lehrl@gmail.com', 98765.11, 'NO', NULL),
        (214014, 901460012, 'CATHERINE DANIELA CERDAS SUAREZ', '6783 5678', 'San Jose, Ciudad Colon', 'catherine.cerdas@hotmail.com', 23456.77, 'NO', NULL),
        (406003, 901460013, 'MARIA MACARENA APOLONIO PACHECO', '7659 1234', 'Heredia, Mercedes', 'maria.apolonio@yahoo.com', 98765.99, 'NO', NULL),
        (201010, 901460026, 'JOSHUA ISAIAH MONTERO LEON', '8909 3456', 'Alajuela, Rio Segundo', 'joshua.montero@gmail.com', 65432.88, 'NO', NULL),
        (203004, 901460040, 'NESTOR AURELIO CHACON MONCADA', '6546 8901', 'Cartago, Tejar', 'nestor.chacon@hotmail.com', 87654.22, 'NO', NULL);
    )";
    
    rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Seleccionar datos de la tabla y mostrarlos
    const char* selectDataSQL = "SELECT * FROM Clientes";
    rc = sqlite3_exec(db, selectDataSQL, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Cerrar la conexion a la base de datos
    sqlite3_close(db);

    std::cout << "Datos insertados correctamente en la base de datos 'clientes.db'" << std::endl;

        // Eliminar la base de datos
    if (remove(dbFile) != 0) {
        std::cerr << "Error al eliminar la base de datos '" << dbFile << "'" << std::endl;
    } else {
        std::cout << "Base de datos '" << dbFile << "' eliminada correctamente" << std::endl;
    }
    return 0;
}