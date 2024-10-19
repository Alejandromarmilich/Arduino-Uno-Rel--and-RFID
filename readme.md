# Control de Encendido/Apagado con RFID, LEDs, Relé y Buzzer

Este programa implementa un sistema de control basado en un lector RFID que alterna el encendido y apagado de un sistema utilizando LEDs, un relé y un buzzer. El sistema verifica si una tarjeta o llavero RFID es correcto para cambiar su estado entre encendido y apagado. Además, se enciende un LED azul si el sistema está activado.

## Componentes Utilizados

- **MFRC522 RFID Reader**: Se utiliza para leer las llaves RFID.
- **Buzzer**: Proporciona señales audibles para llaves correctas o incorrectas.
- **LED Rojo**: Parpadea cuando el sistema está apagado.
- **LED Amarillo**: Indica cuando el sistema está encendido.
- **LED Azul**: Se enciende cuando el relé está activado.
- **Relé**: Controla la activación de un dispositivo externo cuando el sistema está encendido.
- **Llave RFID**: Se compara contra una llave permitida para controlar el sistema.

## Pinout

- `SS_PIN`: Pin 10, utilizado como pin de selección de esclavo para el lector RFID.
- `RST_PIN`: Pin 9, utilizado para resetear el lector RFID.
- `BUZZER_PIN`: Pin 8, para el buzzer.
- `LED_ROJO_PIN`: Pin 7, para el LED rojo.
- `LED_AMARILLO_PIN`: Pin 6, para el LED amarillo.
- `RELE_PIN`: Pin 5, para controlar el relé.
- `LED_AZUL_PIN`: Pin 4, para el LED azul (nuevo en la implementación).

## Variables

- `llavePermitida[]`: UID de la tarjeta RFID permitida para controlar el sistema.
- `sistemaEncendido`: Variable booleana que almacena el estado del sistema. `true` si está encendido, `false` si está apagado.

## Funciones

### `setup()`
- Inicializa el puerto serial, el lector RFID y los pines de los componentes.
- Apaga el sistema al inicio.
- Imprime un mensaje en el serial indicando que se aproxime una tarjeta.

### `loop()`
- Parpadea el LED rojo cuando el sistema está apagado.
- Espera la presencia de una tarjeta RFID nueva.
- Si una tarjeta está presente, lee el UID y lo compara con la llave permitida.
- Si la llave es correcta, el sistema alterna entre encendido y apagado.
- Si la llave es incorrecta, suena el buzzer con un tono diferente.

### `compararLlave(byte* uidLeido)`
- Compara el UID leído con la `llavePermitida[]` para verificar si la llave es correcta.
- Retorna `true` si la llave es correcta, `false` si no lo es.

### `parpadeoRojo()`
- Controla el parpadeo del LED rojo cuando el sistema está apagado.
- Cambia el estado del LED cada 100 milisegundos.

### `apagarSistema()`
- Apaga el sistema estableciendo `sistemaEncendido` en `false`.
- Enciende el LED rojo, apaga el LED amarillo y el relé.
- Apaga el LED azul para indicar que el relé está desactivado.
- Imprime "Sistema apagado" en el serial.

### `encenderSistema()`
- Enciende el sistema estableciendo `sistemaEncendido` en `true`.
- Apaga el LED rojo, enciende el LED amarillo y activa el relé.
- Enciende el LED azul para indicar que el relé está activado.
- Imprime "Sistema encendido" en el serial.

## Flujo del Programa

1. El programa comienza con el sistema apagado y el LED rojo parpadeando.
2. Cuando se aproxima una tarjeta o llavero RFID, se lee el UID de la tarjeta.
3. Si el UID coincide con `llavePermitida[]`, el buzzer suena, y el sistema alterna su estado entre encendido y apagado.
4. Cuando el sistema se enciende, el LED rojo se apaga, el LED amarillo se enciende, y se activa el relé junto con el LED azul.
5. Si el sistema está encendido y se aproxima nuevamente la tarjeta correcta, el sistema se apaga, apagando los LEDs y el relé.

## Notas Adicionales

- El buzzer emite un tono alto para llaves correctas (2000 Hz) y un tono bajo para llaves incorrectas (100 Hz).
- Se ha añadido un LED azul que se enciende cuando el relé está activo, indicando visualmente que el sistema está encendido.
