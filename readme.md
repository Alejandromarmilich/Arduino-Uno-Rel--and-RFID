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

El proyecto está configurado para usarse con **PlatformIO** en **VS Code**. Asegúrate de tener instaladas las siguientes librerías en tu entorno `platformio.ini`:

- **MFRC522**: Para controlar el lector RFID.
- **LiquidCrystal_I2C**: Para manejar la pantalla LCD I2C.

Estas se pueden agregar en el archivo `platformio.ini` de la siguiente forma:

`
lib_deps = 
  rfid/MFRC522
  fdebrabander/Arduino-LiquidCrystal-I2C
`

## Instalación y configuración
Clonar el repositorio
Clona el repositorio:

git clone https://github.com/usuario/sistema-control-rfid.git
Abrir en VS Code:

Abre el directorio clonado en VS Code.
Asegúrate de que PlatformIO esté instalado y configurado.
Configurar el archivo platformio.ini: Verifica que el archivo platformio.ini incluya las configuraciones necesarias para tu placa Arduino. Asegúrate de que tu placa esté correctamente seleccionada, por ejemplo:

`[env:uno]
platform = atmelavr
board = uno
framework = arduino
lib_deps = 
    miguelbalboa/MFRC522 @ ^1.4.10
    fmalpartida/LiquidCrystal @ ^1.5.0`

Realizar las conexiones: Realiza las conexiones descritas en la sección de "Conexiones de hardware".

Configurar las llaves permitidas: En el código fuente (src/main.cpp), puedes modificar el array llavePermitida[] para definir las llaves RFID autorizadas. Simplemente agrega los UIDs de las llaves que quieras autorizar.

## Compilar y cargar el código:

Presiona Ctrl + Shift + P en VS Code, selecciona PlatformIO: Build para compilar el proyecto.
Luego selecciona PlatformIO: Upload para cargar el código en tu placa Arduino.
Prueba el sistema: Una vez que el código se haya subido correctamente, puedes probar el sistema acercando una tarjeta o llave RFID al lector y observar la respuesta del sistema.

## Uso
Encender el sistema: Utiliza una llave autorizada para encender el relé y activar el sistema.
Apagar el sistema: Usa la misma llave autorizada para apagar el sistema.
Ver mensajes en la pantalla: La pantalla LCD te guiará a lo largo del proceso mostrando si una llave es correcta o incorrecta y el estado actual del sistema.

## Licencia
Este proyecto está licenciado bajo la licencia **GPL-3.0**. Puedes ver más detalles en el siguiente enlace:

[GPL-3.0 License](https://www.gnu.org/licenses/gpl-3.0.html)

Si tienes alguna pregunta o sugerencia, no dudes en abrir un issue o hacer una pull request. ¡Gracias por contribuir!