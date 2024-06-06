#include "prestamos.hpp"

int main() {
    // Ejemplo prueba 1
    Prestamo prestamo1(1, 10000, 5, 12, 1, "Mensual");
    prestamo1.solicitarPrestamo(10000, 5, 12, 1, "Mensual");
    prestamo1.estadoPrestamo();
    prestamo1.abonoPrestamo(500);
    prestamo1.abonoExtraordinario(1000);
    prestamo1.estadoPrestamo();

    return 0;
}
