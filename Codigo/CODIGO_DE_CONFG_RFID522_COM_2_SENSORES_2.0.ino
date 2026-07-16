#include <SPI.h>
#include <MFRC522.h>

//==============================
// Definição dos pinos
//==============================

// Primeiro leitor
#define SS_PIN1 10

// Segundo leitor
#define SS_PIN2 3

// Reset compartilhado
#define RST_PIN 9

//==============================
// Objetos RFID
//==============================

MFRC522 sensor1(SS_PIN1, RST_PIN);
MFRC522 sensor2(SS_PIN2, RST_PIN);

//==============================

void setup() {

  Serial.begin(9600);

  SPI.begin();

  sensor1.PCD_Init();
  sensor2.PCD_Init();

  Serial.println("=================================");
  Serial.println(" Dois leitores RFID iniciados ");
  Serial.println("=================================");
}

void loop() {

  // ---------- Sensor 1 ----------
  if (sensor1.PICC_IsNewCardPresent() &&
      sensor1.PICC_ReadCardSerial()) {

    Serial.print("Sensor 1 -> UID: ");

    for (byte i = 0; i < sensor1.uid.size; i++) {

      if (sensor1.uid.uidByte[i] < 0x10)
        Serial.print("0");

      Serial.print(sensor1.uid.uidByte[i], HEX);
      Serial.print(" ");
    }

    Serial.println();

    sensor1.PICC_HaltA();
    sensor1.PCD_StopCrypto1();
  }

  // ---------- Sensor 2 ----------
  if (sensor2.PICC_IsNewCardPresent() &&
      sensor2.PICC_ReadCardSerial()) {

    Serial.print("Sensor 2 -> UID: ");

    for (byte i = 0; i < sensor2.uid.size; i++) {

      if (sensor2.uid.uidByte[i] < 0x10)
        Serial.print("0");

      Serial.print(sensor2.uid.uidByte[i], HEX);
      Serial.print(" ");
    }

    Serial.println();

    sensor2.PICC_HaltA();
    sensor2.PCD_StopCrypto1();
  }
}