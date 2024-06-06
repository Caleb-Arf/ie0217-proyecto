//Clase de prestamos
#ifndef PRESTAMOS_HPP
#define PRESTAMOS_HPP

#include <iostream>
#include <string>
using namespace std;

class Prestamo {
private:
    int idPrestamo;
    double montoPrestamo;
    double interesMensual;
    int plazoMeses;
    int plazoAnios;
    string FrecuenciaPagoMensual;
    int numCuotas;
    double CuotaAPagar;
    double PagosAdelantados;
    double InteresTotal;

    void calcularCuotaAPagar();
    void calcularInteresTotal();

public:
    // Constructor
    Prestamo(int id, double monto, double interes, int meses, int anios, string frecuencia);

    // Destructor
    ~Prestamo();

    void solicitarPrestamo(double monto, double interes, int meses, int anios, string frecuencia);
    void estadoPrestamo();
    void abonoPrestamo(double monto);
    void abonoExtraordinario(double monto);
};

#endif // PRESTAMO_HPP
