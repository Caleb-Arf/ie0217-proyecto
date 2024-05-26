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

## Objetivo principal

Crear una interfaz gráfica de un sistema de gestión bancaria que pueda realizar las operaciones básicas de un banco, así como mostrar información general sobre préstamos bancarios.


## Explicación por pasos del sistema de gestión bancaria

### Paso 1:  Verificación de id_cliente del cliente

En caso de no existir el cliente: Creación del id_cliente

A partir de la cédula del cliente se crea un usuario o id_cliente el cual contiene la información  de este. Contiene el nombre, la dirección de vivienda, el número de teléfono y correo electrónico.

Luego se elige la cuenta que desea crear: Colones o Dólares. A partir de la selección anterior, se genera un id_cuenta que comienza con 01 en caso de la cuenta de colones o 02 en caso de cuenta en dólares.

Se le pide al cliente depositar al menos 5000 colones o 10 dólares para activar la cuenta y que quede con un fondo base.

En caso de existir el cliente pasa al paso 2, el ingreso al menú de modalidades. 

### Paso 2: Menú de modalidades





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


## Alcances y limitaciones:
- Los préstamos y cuentas tomadas en cuenta son únicamente personales. No se toma en cuenta los DIMEX ni las cuentas empresariales.

- Solo se tomará en cuenta para dicho programa 5 tipos de préstamos preselectos (hipotecarios, prendarios, personales, vehiculares y de vivienda).

- Las tasas de interés para cada entidad bancaria es distinta. En nuestro caso se utilizarán las del Banco Popular:
www.bancopopular.fi.cr/wp-content/uploads/2024/05/Banca-Personas.pdf


## Referencias
1. BBVA México. (2024). Estado de Cuenta. 
https://www.bbva.mx/educacion-financiera/e/estado_de_cuenta.html

2. Instituto Nacional de Aprendizaje (INA). (2020). Instrumentos financieros para ahorrar. 
https://www.inavirtual.ed.cr/pluginfile.php/1932699/mod_resource/content/2/SERVER%20GUIA%20MEIC%20BLOQUE4%20ACT%20/t2apt1.html

3. Etecé. (2021). ¿Qué es interés?. 
https://concepto.de/interes/#:~:text=En%20econom%C3%ADa%2C%20el%20inter%C3%A9s%20es,que%20toma%20de%20un%20prestamista.

4. Giift. (2023). Amortización. 
https://www.getcompass.ai/es/glossary/amortization

5. Raisin GmbH. (2024). Glosario de términos bancarios. 
https://www.raisin.es/glosario/

6. Rocket Mortgage. (2023). Principal e intereses: fundamentos del pago hipotecario. 
https://www.rocketmortgage.com/es/learn/principal-e-intereses#:~:text=El%20principal%20es%20la%20cantidad%20que%20te%20presta%20el%20prestamista,cuenta%20de%20dep%C3%B3sito%20en%20garant%C3%ADa.


