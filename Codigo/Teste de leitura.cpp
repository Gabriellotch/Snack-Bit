#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int motorA1 = 5; 
const int motorA2 = 6;
const int motorB1 = 7;
const int motorB2 = 8;
const int buzzer  = 4;
const int led1    = 2;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.println("Sistema Pronto!");
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;

  String conteudo = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  conteudo.toUpperCase();
  conteudo.trim();

  Serial.print("ID lido: ");
  Serial.println(conteudo);

  if (conteudo == "A1 B2 C3 D4") { 
    moverFrente();
  }
  
  if (conteudo == "E5 F6 G7 H8") { 
    moverDireita();
  }
}

void moverFrente() {
  digitalWrite(led1, HIGH);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  delay(5000);
  parar(); 
}

void moverDireita() {
  digitalWrite(buzzer, HIGH);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  delay(5000);
  parar();
}

void parar() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(buzzer, LOW);
}


