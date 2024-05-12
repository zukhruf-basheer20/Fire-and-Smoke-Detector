
/*Fire alarm security system with Nodemcu
   https://srituhobby.com
*/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include "BlynkSimpleEsp8266.h"

char auth[] = "authkey";
char ssid[] = "wifi key";
char pass[] = "wifi password";

BlynkTimer timer;
int pinValue = 0;
int Sensor = D0;

void setup() {
  Serial.begin(9600);
  pinMode(Sensor, INPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, notifiaction);
}

void notifiaction() {
  int sensor = digitalRead(Sensor);
  int sens =  analogRead(A0);
  Serial.println(sens);
  if (sensor == 1) {
    Serial.println("no fire");
  }
  else {
    Serial.println("fire");
  }
  if (sensor == 0 ) {
    Blynk.notify("Fire Alert! A fire was detected");
  }
  else if ( sens > 700) {
    if (sens > 1800) {
      Blynk.notify("High Alert! Smoke was detected");
    } else if (sens > 1200) {
      Blynk.notify("Alert! Smoke was detected");
    } else {
      Blynk.notify("Mild Alert! Smoke was detected");
    }

  }
}

void loop() {

  Blynk.run();
  timer.run();
}
