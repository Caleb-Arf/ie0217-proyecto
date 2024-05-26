# Propuesta de Proyecto Final G10

Universidad de Costa Rica

Estructuras Abstractas de Datos y Algoritmos para Ingeniería IE0217

Profesor: Rafael Esteban Badilla Alvarado

Estudiantes: 

Caleb Arias Fallas - C20739

Daniel De La O Rojas - B82528

Evelyn Feng Wu - B82870

I Semestre 2024


# Propuesta de investigación y diseño para un sistema de gestión bancaria

## Explciación por pasos del sistema de gestión bancaria

### Paso 1:  Verificación de id_cliente del cliente

En caso de no existir el cliente: Creación del id_cliente

A partir de la cédula del cliente se crea un usuario o id_cliente el cual contiene la información  de este. Contiene el nombre, la dirección de vivienda, el número de teléfono y correo electrónico.

Luego se elige la cuenta que desea crear: Colones o Dólares. A partir de la selección anterior, se genera un id_cuenta que comienza con 01 en caso de la cuenta de colones o 02 en caso de cuenta en dólares.

Se le pide al cliente depositar al menos 5000 colones o 10 dólares para activar la cuenta y que quede con un fondo base.

En caso de existir el cliente pasa al paso 2, el ingreso al menú de modalidades. 

### Paso 2: Menú de modalidades









### Supuestos:
- Los préstamos y cuentas tomadas en cuenta son únicamente personales. No se toma en cuenta los DIMEX ni las cuentas empresariales.

- Solo se tomará en cuenta para dicho ejercicio 5 tipos de préstamos. 

- Las tasas de interés son tomadas del Banco Popular:
chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://www.bancopopular.fi.cr/wp-content/uploads/2024/05/Banca-Personas.pdf



## Esquema inicial Menú
Pedir ID del cliente (verificación)
## Modalidades
1. Modalidad de atención a clientes
- Estado de cuenta del cliente
  - Selecciona rango de fechas y tipo de cuenta bancaria (dol o col)
  - Si la cuenta no existe, la crea.
	
Consultar CDPs
Crear CDP
Indica la cuenta (dol o col)
Indica el monto 
Se le muestra el plazo y de acuerdo al plazo se le aplica el interés
Transferencia
Resta la cantidad seleccionada y la suma a la cuenta seleccionada
Depósito
Suma la cantidad seleccionada a la cuenta.
Préstamos
Crear
Colones o dólares
Tipo de préstamo
Tasa de interés de acuerdo al tipo de préstamo
Periodo en meses predefinidos según el tipo de préstamo
Cuota mensual predefinido
Abono a préstamos
Abono extraordinario a préstamo
Obtener información sobre préstamos **

Tipos de préstamos
Hipotecarios
Prendarios
Personales
Vehículo
Vivienda

Tabla de pagos
Ingrese monto
Cuota mensual predef.
Cantidad de cuotas
Tasa de interés predef.
Periodo en meses predef.

Salir

2. Información general sobre préstamos bancarios **


Cliente
Identificación de cliente: Cédula
