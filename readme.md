# Sistema de Control con RFID

Este proyecto implementa un sistema de control de encendido y apagado basado en la tecnología **RFID** utilizando Arduino. El sistema permite verificar una llave RFID autorizada para activar o desactivar un relé que controla el encendido de un dispositivo. Además, cuenta con indicadores visuales (LEDs), un buzzer para notificaciones sonoras, y una pantalla LCD que muestra información en tiempo real sobre el estado del sistema.

## Características principales

- **Verificación de llaves RFID**: Detecta el UID de tarjetas o llaves RFID y compara con una lista de llaves permitidas.
- **Control de relé**: El relé se activa o desactiva dependiendo de si se detecta una llave correcta o incorrecta.
- **Indicadores visuales y sonoros**:
  - **LED Rojo**: Parpadea cuando el sistema está apagado.
  - **LED Amarillo**: Indica la transición de encendido/apagado.
  - **LED Azul**: Se ilumina cuando el sistema está encendido.
  - **Buzzer**: Emite tonos diferentes para llaves correctas e incorrectas.
- **Pantalla LCD**: Muestra el UID de las llaves detectadas y el estado del sistema (encendido o apagado).

## Requisitos de hardware

- **Arduino Uno (u otro compatible)**
- **Lector RFID RC522**
- **Pantalla LCD 16x2 con módulo I2C**
- **Buzzer**
- **Relé**
- **LEDs**: Rojo, Amarillo, Azul
- **Llaves o tarjetas RFID**

## Conexiones de hardware

| Componente          | Pin en Arduino |
|---------------------|----------------|
| Lector RFID (SS)     | 10             |
| Lector RFID (RST)    | 9              |
| Buzzer              | 8              |
| LED Rojo            | 7              |
| LED Amarillo        | 6              |
| Relé                | 5              |
| LED Azul            | 4              |
| LCD I2C (SDA/SCL)   | Depende del modelo (por lo general, SDA a A4, SCL a A5 en Arduino Uno) |

### Conexiones del módulo RFID RC522

- **SDA**: Pin 10 (SS)
- **SCK**: Pin 13
- **MOSI**: Pin 11
- **MISO**: Pin 12
- **RST**: Pin 9
- **VCC**: 3.3V
- **GND**: GND

### Conexiones del LCD I2C

- **SDA**: Conecta al pin SDA en Arduino (normalmente A4)
- **SCL**: Conecta al pin SCL en Arduino (normalmente A5)

## Librerías necesarias

Antes de cargar el código, asegúrate de instalar las siguientes librerías desde el **Library Manager** del IDE de Arduino:

- **MFRC522**: Para controlar el lector RFID.
- **LiquidCrystal_I2C**: Para manejar la pantalla LCD I2C.

Puedes instalarlas directamente desde el IDE de Arduino buscando sus nombres en el gestor de librerías.

## Funcionamiento del sistema

1. **Inicio del sistema**: Al iniciar, la pantalla LCD mostrará el mensaje "Aproxime tarjeta", indicando que el lector RFID está listo para recibir una llave o tarjeta.
2. **Verificación de la llave**:
   - Si se detecta una llave correcta (UID autorizado), el buzzer emitirá un tono, el relé se activará, el LED azul se encenderá, y la pantalla LCD mostrará "Sistema encendido".
   - Si se detecta una llave incorrecta, el buzzer emitirá un tono de error, y la pantalla mostrará "Llave incorrecta".
3. **Control del relé**: El sistema alterna entre encendido y apagado con la misma llave autorizada. Si el sistema está encendido, el uso de una llave autorizada lo apagará, y viceversa.
4. **Indicadores LED**:
   - El **LED rojo** parpadea cuando el sistema está apagado, como señal de espera.
   - El **LED amarillo** parpadea brevemente al encender el sistema y luego se apaga.
   - El **LED azul** permanece encendido mientras el sistema está en funcionamiento.
5. **Pantalla LCD**: Muestra en tiempo real el UID de la llave detectada y el estado del sistema (encendido o apagado).

## Instalación y configuración

1. **Clona el repositorio**:
   ```bash
   git clone https://github.com/usuario/sistema-control-rfid.git
Carga el código: Abre el archivo .ino en el IDE de Arduino y cárgalo en tu placa Arduino.

Asegúrate de las conexiones: Realiza las conexiones descritas en la sección anterior.

Configura las llaves permitidas: En el código fuente, puedes modificar el array llavePermitida[] para definir las llaves RFID autorizadas.

Prueba el sistema: Una vez cargado el código y realizadas las conexiones, el sistema estará listo para probar. Acerque una tarjeta o llave RFID al lector y observe cómo el sistema responde.

## Uso
Encender el sistema: Utiliza una llave autorizada para encender el relé y activar el sistema.
Apagar el sistema: Usa la misma llave autorizada para apagar el sistema.
Ver mensajes en la pantalla: La pantalla LCD te guiará a lo largo del proceso mostrando si una llave es correcta o incorrecta y el estado actual del sistema.

## Licencia
Este proyecto está licenciado bajo la MIT License.

Si tienes alguna pregunta o sugerencia, no dudes en abrir un issue o hacer una pull request. ¡Gracias por contribuir!