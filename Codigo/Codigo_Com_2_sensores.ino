#include <SPI.h>
#include <MFRC522.h>

// Primeiro sensor RFID
#define SS_PIN1 10
#define RST_PIN1 9

// Segundo sensor RFID
#define SS_PIN2 11
#define RST_PIN2 12

MFRC522 sensor1(SS_PIN1, RST_PIN1);
MFRC522 sensor2(SS_PIN2, RST_PIN2);

// Pinos dos motores
const int motorA1 = 5;
const int motorA2 = 6;
const int motorB1 = 7;
const int motorB2 = 8;

// Outros componentes
const int buzzer = 4;
const int led1 = 2;

void setup() {
  Serial.begin(9600);

  // Inicializa a comunicação SPI
  SPI.begin();

  // Inicializa os dois sensores RFID
  sensor1.PCD_Init();
  sensor2.PCD_Init();

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(buzzer, OUTPUT);

  parar();

  Serial.println("Sistema pronto!");
  Serial.println("Aproxime um cartao de um dos sensores.");
}

void loop() {
  // Verifica o primeiro sensor
  verificarSensor(sensor1, 1);

  // Verifica o segundo sensor
  verificarSensor(sensor2, 2);
}

// Função responsável por verificar um sensor RFID
void verificarSensor(MFRC522 &sensor, int numeroSensor) {

  // Verifica se existe um cartão próximo
  if (!sensor.PICC_IsNewCardPresent()) {
    return;
  }

  // Tenta ler o cartão
  if (!sensor.PICC_ReadCardSerial()) {
    return;
  }

  String conteudo = "";

  // Monta o código UID do cartão
  for (byte i = 0; i < sensor.uid.size; i++) {
    if (sensor.uid.uidByte[i] < 0x10) {
      conteudo += "0";
    }

    conteudo += String(sensor.uid.uidByte[i], HEX);

    if (i < sensor.uid.size - 1) {
      conteudo += " ";
    }
  }

  conteudo.toUpperCase();
  conteudo.trim();

  Serial.print("Sensor ");
  Serial.print(numeroSensor);
  Serial.print(" - ID lido: ");
  Serial.println(conteudo);

  /*
    A ação realizada depende do sensor utilizado
    e do cartão aproximado.
  */

  if (numeroSensor == 1) {

    // Cartão lido pelo primeiro sensor
    if (conteudo == "A1 B2 C3 D4") {
      Serial.println("Comando: mover para frente");
      moverFrente();
    }
    else {
      Serial.println("Cartao nao autorizado no sensor 1.");
      emitirErro();
    }
  }

  else if (numeroSensor == 2) {

    // Cartão lido pelo segundo sensor
    if (conteudo == "E5 F6 A7 B8") {
      Serial.println("Comando: mover para a direita");
      moverDireita();
    }
    else {
      Serial.println("Cartao nao autorizado no sensor 2.");
      emitirErro();
    }
  }

  // Finaliza a comunicação com o cartão
  sensor.PICC_HaltA();
  sensor.PCD_StopCrypto1();

  delay(1000);
}

void moverFrente() {
  digitalWrite(led1, HIGH);

  // Os dois motores giram para frente
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);

  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);

  delay(5000);

  parar();
}

void moverDireita() {
  digitalWrite(buzzer, HIGH);

  // Motor A gira para frente
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);

  // Motor B gira para trás
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);

  delay(5000);

  parar();
}

void emitirErro() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzer, HIGH);
    delay(200);

    digitalWrite(buzzer, LOW);
    delay(200);
  }
}

void parar() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);

  digitalWrite(led1, LOW);
  digitalWrite(buzzer, LOW);
}