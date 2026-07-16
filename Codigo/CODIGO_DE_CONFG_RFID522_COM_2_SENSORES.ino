#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

// Primeiro sensor RFID
#define SS_PIN1 10
#define RST_PIN1 9
#define MOSI_PIN1 11
#define MISO_PIN1 12
#define SCK_PIN1 13

// Segundo sensor RFID
#define SS_PIN2 10
#define RST_PIN12 9
#define MOSI_PIN2 11
#define MISO_PIN2 12
#define SCK_PIN12 13


}

void setup() {

  PinMode(SS_PIN2, IMPUT);
  PinMode(RST_PIN12, IMPUT);
  PinMode(MOSI_PIN2, IMPUT);
  PinMode(MISO_PIN2, IMPUT);
  PinMode(SCK_PIN12, IMPUT);

 
  PinMode(SS_PIN1, IMPUT);
  PinMode(RST_PIN11, IMPUT);
  PinMode(MOSI_PIN1, IMPUT);
  PinMode(MISO_PIN1, IMPUT);
  PinMode(SCK_PIN1, IMPUT);
}
