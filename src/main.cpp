#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER_PIN 8    
#define LED_ROJO_PIN 7  
#define LED_AMARILLO_PIN 6  
#define RELE_PIN 5      
#define LED_AZUL_PIN 4
#define SERVO_PIN 3

Servo servoMotor;

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

byte llavePermitida[] = {0xAB, 0x31, 0xA6, 0x1B}; 

bool sistemaEncendido = false;
unsigned long ultimoMovimientoServo = 0;
const unsigned long intervaloMovimientoServo = 2000;  

void apagarSistema();
void encenderSistema();
void parpadeoRojo();
bool compararLlave(byte* uidLeido);
void moverServo();

void setup() {
  servoMotor.attach(SERVO_PIN);
  Serial.begin(9600);  
  SPI.begin();  
  rfid.PCD_Init();  

  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(BUZZER_PIN, OUTPUT);  
  pinMode(LED_ROJO_PIN, OUTPUT);
  pinMode(LED_AMARILLO_PIN, OUTPUT);
  pinMode(RELE_PIN, OUTPUT);
  pinMode(LED_AZUL_PIN, OUTPUT);

  apagarSistema();
  
  lcd.setCursor(0, 0);
  lcd.print("Aproxime tarjeta");
  Serial.println("Aproxime una tarjeta o llavero RFID...");
}

void loop() {
  if (sistemaEncendido) {
    moverServo();  
  }

  if (!sistemaEncendido) {
    parpadeoRojo();
  }

  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  Serial.print("UID de la tarjeta: ");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    lcd.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    lcd.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (compararLlave(rfid.uid.uidByte)) {
    Serial.println("Llave correcta detectada.");
    lcd.setCursor(0, 1);
    lcd.print("Llave correcta");
    tone(BUZZER_PIN, 2000);  
    delay(100);
    noTone(BUZZER_PIN);

    if (sistemaEncendido) {
      apagarSistema();
    } else {
      encenderSistema();
    }
    
  } else {
    Serial.println("Llave incorrecta.");
    lcd.setCursor(0, 1);
    lcd.print("Llave incorrecta");
    tone(BUZZER_PIN, 100);  
    delay(500);
    noTone(BUZZER_PIN);
  }

  delay(1000);
}

bool compararLlave(byte* uidLeido) {
  for (byte i = 0; i < 4; i++) {
    if (uidLeido[i] != llavePermitida[i]) {
      return false;
    }
  }
  return true;
}

void parpadeoRojo() {
  static unsigned long ultimoCambio = 0;
  static bool estadoRojo = true;
  unsigned long tiempoActual = millis();

  if (tiempoActual - ultimoCambio >= 100) {  
    estadoRojo = !estadoRojo;
    digitalWrite(LED_ROJO_PIN, estadoRojo ? HIGH : LOW);
    ultimoCambio = tiempoActual;
  }
}

void apagarSistema() {
  sistemaEncendido = false;
  digitalWrite(LED_ROJO_PIN, HIGH);     
  digitalWrite(LED_AMARILLO_PIN, LOW);  
  digitalWrite(RELE_PIN, LOW);          
  digitalWrite(LED_AZUL_PIN, LOW);
  Serial.println("Sistema apagado.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistema apagado");
}

void encenderSistema() {
  sistemaEncendido = true;
  digitalWrite(LED_ROJO_PIN, LOW);      
  digitalWrite(LED_AMARILLO_PIN, HIGH); 
  digitalWrite(RELE_PIN, HIGH);
  delay(500);    
  digitalWrite(LED_AZUL_PIN, HIGH);
  digitalWrite(LED_AMARILLO_PIN, LOW); 
  Serial.println("Sistema encendido.");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistema encendido");
}

void moverServo() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - ultimoMovimientoServo >= intervaloMovimientoServo) {
    int posicionAleatoria = random(0, 180); 
    servoMotor.write(posicionAleatoria);
    ultimoMovimientoServo = tiempoActual;  
  }
}
