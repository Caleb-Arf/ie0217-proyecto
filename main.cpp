#include "prestamos.hpp"

int main() {
    // Example usage
    Prestamo prestamo1(1, 10000, 5, 12, 1, "Mensual");
    prestamo1.solicitarPrestamo(10000, 5, 12, 1, "Mensual");
    prestamo1.estadoPrestamo();
    prestamo1.abonoPrestamo(500);
    prestamo1.abonoExtraordinario(1000);
    prestamo1.estadoPrestamo();

    return 0;
}
