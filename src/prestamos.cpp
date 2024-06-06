#include "prestamos.hpp"

// Constructor
Prestamo::Prestamo(int id, double monto, double interes, int meses, int anios, string frecuencia)
    : idPrestamo(id), montoPrestamo(monto), interesMensual(interes), plazoMeses(meses), 
      plazoAnios(anios), FrecuenciaPagoMensual(frecuencia), numCuotas(0), 
      CuotaAPagar(0.0), PagosAdelantados(0.0), InteresTotal(0.0) {}

// Destructor
Prestamo::~Prestamo() {
    // Add any cleanup code if needed in the future
    cout << "Prestamo with ID " << idPrestamo << " is being destroyed." << endl;
}

// 
void Prestamo::solicitarPrestamo(double monto, double interes, int meses, int anios, string frecuencia) {
    montoPrestamo = monto;
    interesMensual = interes;
    plazoMeses = meses;
    plazoAnios = anios;
    FrecuenciaPagoMensual = frecuencia;
    numCuotas = plazoMeses; // Assuming one payment per month
    calcularCuotaAPagar();
    calcularInteresTotal();
    cout << "Prestamo solicitado con exito!" << endl;
}

// 
void Prestamo::estadoPrestamo() {
    cout << "ID Prestamo: " << idPrestamo << endl;
    cout << "Monto Prestamo: " << montoPrestamo << endl;
    cout << "Interes Mensual: " << interesMensual << "%" << endl;
    cout << "Plazo en Meses: " << plazoMeses << endl;
    cout << "Plazo en Anios: " << plazoAnios << endl;
    cout << "Frecuencia de Pago: " << FrecuenciaPagoMensual << endl;
    cout << "Numero de Cuotas: " << numCuotas << endl;
    cout << "Cuota a Pagar: " << CuotaAPagar << endl;
    cout << "Pagos Adelantados: " << PagosAdelantados << endl;
    cout << "Interes Total: " << InteresTotal << endl;
}

//
void Prestamo::abonoPrestamo(double monto) {
    PagosAdelantados += monto;
    cout << "Pago realizado con exito!" << endl;
}

// 
void Prestamo::abonoExtraordinario(double monto) {
    PagosAdelantados += monto;
    cout << "Abono extraordinario realizado con exito!" << endl;
}

void Prestamo::calcularCuotaAPagar() {
    // 
    if (plazoMeses > 0) {
        CuotaAPagar = (montoPrestamo * (1 + (interesMensual / 100) * plazoMeses)) / plazoMeses;
    }
}

void Prestamo::calcularInteresTotal() {
    // 
    InteresTotal = montoPrestamo * (interesMensual / 100) * plazoMeses;
}
