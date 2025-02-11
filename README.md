# Proyecto Final G10

Universidad de Costa Rica

Estructuras Abstractas de Datos y Algoritmos para Ingeniería IE0217

Profesor: Rafael Esteban Badilla Alvarado

Estudiantes: 

Caleb Arias Fallas - C20739

Daniel De La O Rojas - B82528

Evelyn Feng Wu - B82870

I Semestre 2024


# Link de Netlify
https://6681f44e8770a6b93dec81ed--joyful-capybara-f288f8.netlify.app/files.html

# Investigación, diseño e implementación de un sistema de gestión bancaria

## Objetivo principal

Crear un sistema de gestión bancaria que pueda realizar las operaciones básicas de un banco, así como mostrar información general sobre préstamos bancarios.


## Desarrollo del sistema

### Sección 1:  Verificación de id\_cliente del cliente

1. En caso de no existir el cliente: **Creación del id_cliente**

A partir de la cédula del cliente se crea un usuario o id\_cliente el cual contiene la información  de este. Contiene el nombre, la dirección de vivienda, el número de teléfono y correo electrónico.

Luego se elige el tipo de cuenta que desea crear: Colones o Dólares. A partir de la selección anterior, se genera un id\_cuenta que comienza con 01 en caso de la cuenta de colones o 02 en caso de cuenta en dólares.

Se le pide al cliente depositar al menos 5000 colones o 10 dólares para activar la cuenta y que quede con un fondo base.

2. En caso de existir el cliente pasa a la sección 2, el ingreso al menú de modalidades. 

### Sección 2: Menú de modalidades

**Opción 1**. Modalidad de atención a clientes

1. Estado de cuenta del cliente: 
   1. Selecciona rango de fechas y tipo de cuenta bancaria (dol o col)
   1. Si la cuenta no existe, la crea.
1. Crear CDP
   1. Seleccionar el id\_cuenta (dólares o colones)
   1. Debe indicar el monto a retirar de la cuenta actual
   1. Se le muestra el plazo y de acuerdo al plazo se le aplica el interés
1. Consultar CDP
1. Transferencia
   1. Seleccionar el id\_cuenta (dólares o colones) de origen
   1. Ingresar el id\_cuenta al que se le va a realizar la transferencia (destino)
   1. Digitar monto a transferir
   1. Seleccionar aceptar
1. Depósito
   1. Ingresar el id\_cuenta (dólares o colones) destino
   1. Digitar monto a transferir
   1. Seleccionar aceptar
1. Solicitar préstamo
   1. Digitar monto y plazo en meses. Se le despliega la tasa de interés predeterminada así como el monto de las cuotas. (Se crea un nuevo id\_prestamo con la información del préstamo nuevo)

   Nota: Se va a suponer que ya la información financiera del cliente ya se revisó y verificó con anterioridad y ya tiene permiso para crear uno.

1. Abonar a préstamo
   1. Selecciona el id\_préstamo
   1. Le aparece la información general del préstamo (número de cuota, deuda pendiente, monto del principal más interés del periodo (amortización) y la casilla para ingresar el monto a pagar)
   1. Seleccionar aceptar
1. Abono extraordinario a préstamo
   1. Selecciona el id\_préstamo
   1. Le aparece la información general del préstamo (deuda pendiente y la casilla para ingresar el monto extraordinario a pagar)
   1. Seleccionar aceptar



**Opción 2**. Obtener información sobre préstamos bancarios

1. Tipos de préstamos
   1. Hipotecarios
   1. Prendarios
   1. Personales
   1. Vehículo
   1. Vivienda
1. Tasas de interés
1. Generar tabla de pagos esperada
   1. Seleccione el tipo de préstamo
   1. Seleccione el tipo de moneda
   1. Ingrese el monto
   1. Ingrese el plazo
   1. Seleccione calcular

**Opción 3**. Salir

## Instrucciones de ejecución
### Estos comando son para realizar en la carpeta ie0217-proyecto
Primero se utiliza el comando ```make clean``` para deshacerse de su objeto y archivos ejecutables.

Luego se utiliza ```make build``` para compilar todos los archivos fuente del proyecto.

El siguiente comando es ```make run``` que se usa para correr el programa compilado.

Finalmente se usa el comando ```make``` que compila y ejecuta los archivos fuente.

## Términos importantes a considerar

- **Cuentas de “ahorro” o “corrientes**: se refieren a cuentas que las personas pueden abrir para administrar su dinero en entidades financieras como: bancos, mutuales, cooperativas de ahorro y crédito y asociaciones solidaristas. (INA, 2020)

- **Estado de cuenta del cliente**: es un documento que muestra todas las transacciones realizadas en una cuenta bancaria durante un período de tiempo seleccionado. Incluye depósitos, retiros, transferencias, intereses ganados y cargos aplicados. (BBVA México, 2024)

- **Tipo de cuenta bancaria**: determina la moneda en la que está denominada la cuenta bancaria. Puede ser en dólares (USD) o en colones (CRC). (Raisin GmbH, 2024)

- **Certificados de Depósito a Plazo (CDP)**: instrumento financiero emitido por una entidad bancaria que representa una suma de dinero depositada por un cliente durante un período de tiempo específico, conocido como plazo. A cambio de mantener el dinero en el banco durante ese tiempo, el banco paga al cliente una tasa de interés fija. Los CDPs se emiten en diferentes monedas y plazos, y la tasa de interés puede variar según el monto del depósito y la duración del plazo. Al vencimiento del CDP, el cliente recibe el capital depositado inicialmente junto con los intereses generados. Cada banco determinará las condiciones correspondiente en caso de hacer efectivo el CDP antes del vencimiento. (INA, 2020)

- **Transferencia**: la acción de mover una cantidad de dinero de una cuenta bancaria a otra, ya sea dentro del mismo banco o hacia otro banco. Se resta la cantidad de la cuenta de origen y se suma a la cuenta de destino. (Raisin GmbH, 2024)

- **Depósito**: acción de agregar fondos a una cuenta bancaria. La cantidad seleccionada se suma al saldo de la cuenta. (Raisin GmbH, 2024)

- **Préstamos**: proceso mediante el cual un cliente solicita y recibe una cantidad de dinero del banco, con la obligación de devolverlo en un plazo determinado junto con los intereses acordados. (Raisin GmbH, 2024)

- **Tasa de interés**: magnitud, generalmente expuesta como un porcentaje (o tasa) que paga una persona física o jurídica por el uso del dinero que toma de un prestamista. (Etecé, 2021)

- **Cuota mensual predefinida**: Cantidad fija que el prestatario debe pagar mensualmente, la cual incluye tanto el principal como los intereses del préstamo. (Raisin GmbH, 2024)

- **Principal**: cantidad de dinero inicial que le presta una entidad bancaria, en este caso. (Rocket Mortgage, 2023)
 
- **Amortización:** cuotas periódicas pagadas por el préstamo, incluyen tanto el principal como los intereses. (Giift, 2023)

- **Abono a préstamos**: pago realizado para reducir el saldo pendiente del préstamo. Puede ser el pago de la cuota mensual o un pago adicional. (Raisin GmbH, 2024)

- **Abono extraordinario a préstamo**: pago adicional al pago mensual regular, destinado a reducir el saldo del principal del préstamo. Esto puede disminuir el tiempo total del préstamo y los intereses pagados. (Raisin GmbH, 2024)


### Algunos cálculos importantes
````
Tasa de interés mensual (i% mensual)  = Tasa nominal anual / 12 (meses)

Intereses (mensuales) = (Saldo principal pendiente al mes anterior) x (i% mensual) 

Cuota mensual = (P * i) / (1 - (1 + i) ^ (-n))

Donde:

P = Monto del préstamo
i = Tasa de interés mensual
n = Plazo del crédito en meses - Cantidad de cuotas totales - (años * 12)

Total pagado (mensual) = Cuota mensual + abono extraordinario

Capital amortizado = Total pagado (mensual)  - Intereses (mensuales)

Saldo = Saldo anterior - Capital amortizado

`````
### Ejemplo de Tabla de amortización:

| | | | | | | |
|-|-|-|-|-|-|-|
|Tabla de amortización| | | | | | |
|NÚMERO DE CUOTA|CUOTA A PAGAR|PAGO ANTICIPADO|TOTAL PAGADO|INTERÉS|CAPITAL AMORTIZADO|SALDO|
|0| | | | | |150000|
|1|6784.093718|10000|16784.09372|1000|15784.09372|134215.9063|
|2|6784.093718|10000|16784.09372|894.7727085|15889.32101|118326.5853|
|3|6784.093718|10000|16784.09372|788.8439018|15995.24982|102331.3355|
|4|6784.093718| |6784.093718|682.208903|6101.884815|96229.45064|
|5|6784.093718| |6784.093718|641.5296709|6142.564047|90086.88659|
|6|6784.093718| |6784.093718|600.5792439|6183.514474|83903.37212|
|7|6784.093718| |6784.093718|559.3558141|6224.737904|77678.63421|
|8|6784.093718| |6784.093718|517.8575614|6266.236157|71412.39806|
|9|6784.093718| |6784.093718|476.0826537|6308.011065|65104.38699|
|10|6784.093718| |6784.093718|434.0292466|6350.064472|58754.32252|
|11|6784.093718| |6784.093718|391.6954835|6392.398235|52361.92428|
|12|6784.093718| |6784.093718|349.0794952|6435.014223|45926.91006|
|13|6784.093718| |6784.093718|306.1794004|6477.914318|39448.99574|
|14|6784.093718| |6784.093718|262.993305|6521.100413|32927.89533|
|15|6784.093718| |6784.093718|219.5193022|6564.574416|26363.32091|
|16|6784.093718| |6784.093718|175.7554728|6608.338246|19754.98267|
|17|6784.093718| |6784.093718|131.6998845|6652.393834|13102.58883|
|18|6784.093718| |6784.093718|87.35059223|6696.743126|6405.845708|
|19|6784.093718| |6405.845708|42.70563805|6363.14007|0|



### Cálculo de interés para los CDP

Los intereses netos mensuales son calculados de la siguiente manera:
- Intereses Brutos = (Monto del CDP * Tasa de Interés)*30/360.
- Impuesto (15%) = Interés Bruto * 15%.
- Interés Neto = Interés Devengado - Impuesto.


### Tipos de Préstamos
A continuación, se describen los tipos de préstamos cubiertos dentro del sistema de gestión bancaria:

1. Préstamos Hipotecarios:
   - Los préstamos hipotecarios están destinados a la compra de bienes raíces, como casas o terrenos. El bien inmueble adquirido se utiliza como garantía del préstamo.
   - Tasa de Interés: Varían entre el 7% y el 9% anual, dependiendo del banco y las condiciones específicas del préstamo.
2. Préstamos Prendarios:
   - Los préstamos prendarios son aquellos que utilizan un bien mueble, como un vehículo, joyas, o maquinaria, como garantía del préstamo. Son comunes para obtener liquidez rápida.
   - Tasa de Interés: Las tasas de interés para préstamos prendarios suelen ser más altas que las de los hipotecarios, vaiando entre el 10% y el 15% anual.
3. Préstamos Personales:
   - Los préstamos personales se otorgan para diversos fines, como consolidación de deudas, gastos médicos, viajes, etc. No requieren una garantía específica, aunque pueden depender de la solvencia del solicitante.
   - Tasa de Interés: Varían típicamente entre el 12% y el 25% anual, dependiendo del perfil crediticio del solicitante y el banco.
4. Préstamos para Vehículo:
   - Estos préstamos están diseñados específicamente para la compra de vehículos nuevos o usados. El vehículo adquirido generalmente se utiliza como garantía del préstamo.
   - Tasa de Interés: Dicha tasa de interés suele estar en el rango del 7% al 12% anual, dependiendo del modelo del vehículo y la institución financiera.
5. Préstamos para Vivienda:
   - Estos están destinados a la adquisición, construcción, o mejora de una vivienda. La vivienda puede ser la garantía del préstamo.
   - Tasa de Interés: Oscilar entre el 6% y el 9% anual, dependiendo de las condiciones del préstamo y la institución financiera.


## Alcances y limitaciones:
- Los préstamos y cuentas tomadas en cuenta son únicamente personales. No se toma en cuenta los DIMEX ni las cuentas empresariales.

- Solo se tomará en cuenta para dicho programa 5 tipos de préstamos preselectos (hipotecarios, prendarios, personales, vehiculares y de vivienda).

-  Las tasas de interés para cada entidad bancaria es distinta. En nuestro caso se utilizarán las del Banco Popular para préstamos y las del Banco de Costa Rica para CDPs.


## Cronograma
|                                                         | MAYO  | JUNIO  | JUNIO  | JUNIO  | JUNIO | JULIO |
| ------------------------------------------------------- | ----- | ------ | ------ | ------ | ----- | ----- |
|                                                         | 27-31 | 3-7    | 10-14  | 17-21  | 24-28 | 1-5   |
| Propuesta del proyecto                                  | Todos |        |        |        |       |       |
| Menú general                                            | Todos |        |        |        |       |       |
| Creación de clases: clientes e información de prestamos |       | Daniel |        |        |       |       |
| Buscar información de librerías para integrar SQL       |       | Todos  |        |        |       |       |
| Creación de clases: operaciones                         |       | Caleb  |        |        |       |       |
| Creación de clases: préstamos                           |       | Evelyn |        |        |       |       |
| Creación de clases: cuentas y CDP                       |       | Daniel |        |        |       |       |
| Creación de métodos para las clases                     |       |        |        |        |       |       |
| Péstamos                                                |       |        | Caleb  | Caleb  |       |       |
| Operaciones                                             |       |        | Evelyn | Evelyn |       |       |
| Cuentas y CDP                                           |       |        | Daniel | Daniel |       |       |
| Aramar documento de avance                              |       |        |        | Todos  |       |       |
| Primeras pruebas del proyecto                           |       |        |        | Todos  |       |       |
| Avance del proyecto                                     |       |        |        | Todos  |       |       |
| Depuraciones                                            |       |        |        |        | Todos |       |
| Pruebas y verificaciones                                |       |        |        |        | Todos |       |
| Aramar documento de presentación final                  |       |        |        |        |       | Todos |
| Presentación final                                      |       |        |        |        |       | Todos |


## Anexos
1. Diagrama UML del proyecto.
![Diagrama UML del proyecto.](https://github.com/Caleb-Arf/ie0217-proyecto/blob/main/Anexos/Proyecto_UML.png)

2. Database schema del proyecto. 
![Database schema del proyecto.](https://github.com/Caleb-Arf/ie0217-proyecto/blob/main/Anexos/Proyecto_Schema.png)

## Referencias
1. BBVA México. (2024). Estado de Cuenta. 
https://www.bbva.mx/educacion-financiera/e/estado_de_cuenta.html

2. Banco de Costa Rica. (2024). Tasas de Interés para CDPs. https://www.bancobcr.com/wps/portal/bcr/bancobcr/personas/inversiones/certificados_de_deposito_a_plazo/tasas_de_interes_para_cdps/

3. Banco Popular. (2024). Banco Popular y de Desarrollo Comunal Tasa Efectiva Mayo 2024. www.bancopopular.fi.cr/wp-content/uploads/2024/05/Banca-Personas.pdf

4. Instituto Nacional de Aprendizaje (INA). (2020). Instrumentos financieros para ahorrar. 
https://www.inavirtual.ed.cr/pluginfile.php/1932699/mod_resource/content/2/SERVER%20GUIA%20MEIC%20BLOQUE4%20ACT%20/t2apt1.html

5. Etecé. (2021). ¿Qué es interés?. 
https://concepto.de/interes/#:~:text=En%20econom%C3%ADa%2C%20el%20inter%C3%A9s%20es,que%20toma%20de%20un%20prestamista.

6. Giift. (2023). Amortización. 
https://www.getcompass.ai/es/glossary/amortization

7. Raisin GmbH. (2024). Glosario de términos bancarios. 
https://www.raisin.es/glosario/

8. Rocket Mortgage. (2023). Principal e intereses: fundamentos del pago hipotecario. 
https://www.rocketmortgage.com/es/learn/principal-e-intereses#:~:text=El%20principal%20es%20la%20cantidad%20que%20te%20presta%20el%20prestamista,cuenta%20de%20dep%C3%B3sito%20en%20garant%C3%ADa.



