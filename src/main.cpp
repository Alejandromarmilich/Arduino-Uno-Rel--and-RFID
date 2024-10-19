#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER_PIN 8    
#define LED_ROJO_PIN 7  
#define LED_AMARILLO_PIN 6  
#define RELE_PIN 5      
#define LED_AZUL_PIN 4 

MFRC522 rfid(SS_PIN, RST_PIN);

byte llavePermitida[] = {0xAB, 0x31, 0xA6, 0x1B}; 

bool sistemaEncendido = false;

void apagarSistema();
void encenderSistema();
void parpadeoRojo();
bool compararLlave(byte* uidLeido);

void setup() {
  Serial.begin(9600);  
  SPI.begin();  
  rfid.PCD_Init();  
  
  pinMode(BUZZER_PIN, OUTPUT);  
  pinMode(LED_ROJO_PIN, OUTPUT);
  pinMode(LED_AMARILLO_PIN, OUTPUT);
  pinMode(RELE_PIN, OUTPUT);
  pinMode(LED_AZUL_PIN, OUTPUT);

  apagarSistema();
  
  Serial.println("Aproxime una tarjeta o llavero RFID...");
}

void loop() {
  if (!sistemaEncendido) {
    parpadeoRojo();
  }

  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  Serial.print("UID de la tarjeta: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (compararLlave(rfid.uid.uidByte)) {
    Serial.println("Llave correcta detectada.");
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
}
