#include <iostream>
#include <sqlite3.h>
#include <string>

double obtenerBalance(sqlite3* db, int idCliente);

bool actualizarBalance(sqlite3* db, int idCliente, double nuevoBalance);
