#include <SoftwareSerial.h>

int sensorPin = 2;
int relayPin = 3;
int ledPin = 13;
int SENSOR_DI = 1;
long lastSwitch = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  pinMode(relayPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  //  SENSOR_DI = digitalRead(sensorPin);
  Serial.begin(9600);
}
bool isCanSwitch = false;
long secDebounce = 60;
void loop() {
//  Serial.print("mils: ");
//  Serial.println(millis() / 1000);
//  Serial.print("last: ");
//  Serial.println(lastSwitch / 1000);
//  Serial.println(millis() - lastSwitch);
//  Serial.println(secDebounce * 1000);
  
  if ((millis() - lastSwitch) > (secDebounce * 1000 ) || lastSwitch == 0) {
    isCanSwitch = true;
    digitalWrite(ledPin, HIGH);
  } else {
    isCanSwitch = false;
    digitalWrite(ledPin, LOW);
  }

  if (SENSOR_DI != digitalRead(sensorPin) && isCanSwitch) {
    lastSwitch = millis();
    if (SENSOR_DI == 0) {
      digitalWrite(relayPin, HIGH);
    } else {
      digitalWrite(relayPin, LOW);
    }
    SENSOR_DI = digitalRead(sensorPin);
  }
  delay(500);
}
