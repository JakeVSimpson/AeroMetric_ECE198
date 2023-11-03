#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial pmsSerial(2, 3); // RX, TX
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8
#define CS_PIN 10
const int buzzerPin = 8;
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
void setup() {
  // our debugging output
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < 20; i++){
    digitalWrite(buzzerPin, HIGH);  // This should turn the buzzer ON
    delay(50);
    digitalWrite(buzzerPin, LOW);
    delay(50);
  }
    // This should turn the buzzer OFF
  Serial.begin(115200);
  myDisplay.begin();
  myDisplay.setIntensity(4);
  myDisplay.displayClear();
  // sensor baud rate is 9600
  pmsSerial.begin(9600);
}
struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, 
particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};

bool safe = true;
char* message = "Air is Safe";
 
struct pms5003data data;
