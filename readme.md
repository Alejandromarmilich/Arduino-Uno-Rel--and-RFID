# Generating a README.md file with the updated project information.

content = """
# Sistema de Control con RFID

Este proyecto implementa un sistema de encendido y apagado basado en la tecnología **RFID** utilizando Arduino y un microcontrolador compatible. El sistema permite verificar una llave RFID autorizada para activar o desactivar un relé que controla el encendido de un dispositivo. Cuenta con indicadores visuales (LEDs), un buzzer para notificaciones sonoras y una pantalla LCD para mostrar información sobre el estado del sistema en tiempo real.

## Características principales

- **Verificación de llaves RFID**: Detecta el UID de tarjetas o llaves RFID y lo compara con la llave permitida.
- **Control de relé**: Activa o desactiva el relé en función de si se detecta una llave correcta o incorrecta.
- **Indicadores visuales y sonoros**:
  - **LED Rojo**: Parpadea cuando el sistema está apagado.
  - **LED Amarillo**: Indica la transición de encendido/apagado.
  - **LED Azul**: Se ilumina cuando el sistema está encendido y el servo está en 90°.
  - **Buzzer**: Emite tonos distintos para llaves correctas e incorrectas.
- **Pantalla LCD**: Muestra el UID de las llaves detectadas y el estado del sistema.
- **Servo Motor**: Cambia de posición de forma periódica cuando el sistema está encendido.

## Requisitos de hardware

- **Microcontrolador compatible con Arduino** (ej. Arduino Uno)
- **Lector RFID RC522**
- **Pantalla LCD 16x2 con módulo I2C**
- **Buzzer**
- **Relé**
- **Servo motor** (Tower Pro SG90 o similar)
- **LEDs**: Rojo, Amarillo y Azul
- **Llaves o tarjetas RFID**

## Conexiones de hardware

| Componente          | Pin en Arduino |
|---------------------|----------------|
| Lector RFID (SS)    | 10             |
| Lector RFID (RST)   | 9              |
| Buzzer              | 8              |
| LED Rojo            | 7              |
| LED Amarillo        | 6              |
| Relé                | 5              |
| LED Azul            | 4              |
| Servo               | 3              |
| LCD I2C (SDA/SCL)   | SDA: A4, SCL: A5 (para Arduino Uno) |

### Detalles de Conexión del Lector RFID RC522

- **SDA**: Pin 10 (SS)
- **SCK**: Pin 13
- **MOSI**: Pin 11
- **MISO**: Pin 12
- **RST**: Pin 9
- **VCC**: 3.3V
- **GND**: GND

## Librerías necesarias

Este proyecto está configurado para usarse con **PlatformIO** en **VS Code**. Asegúrate de tener instaladas las siguientes librerías en tu entorno `platformio.ini`:

- **MFRC522**: Para el control del lector RFID.
- **LiquidCrystal_I2C**: Para la pantalla LCD I2C.
- **Servo**: Para el control del servo motor.

Para añadir estas librerías, incluye en `platformio.ini`:

```ini
lib_deps = 
    miguelbalboa/MFRC522 @ ^1.4.10
    fmalpartida/LiquidCrystal@^1.5.0
    arduino/Servo@^1.1.8
