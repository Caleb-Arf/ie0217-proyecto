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

    // Method to solicit a loan
    void solicitarPrestamo(double monto, double interes, int meses, int anios, string frecuencia);

    // Method to check loan status
    void estadoPrestamo();

    // Method to make a payment
    void abonoPrestamo(double monto);

    // Method to make an extra payment
    void abonoExtraordinario(double monto);
};

#endif // PRESTAMO_HPP
