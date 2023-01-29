#define BLYNK_TEMPLATE_ID "TMPLnzcQKdaH"
#define BLYNK_DEVICE_NAME "finder"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG

#include "BlynkEdgent.h"

const int pingPin1 = 14;//D5
const int echoPin1 = 12;//D6
const int pingPin2 = 13;//D7
const int echoPin2 = 15;//D8
const int pingPin3 = 4;//D2
const int echoPin3 = 5;//D1

long duration1, cm1,duration2, cm2,duration3, cm3;
int ldr = 0;
int ldrprv = 0;

#define buzzL 0
#define buzzR 2
#define light 16

  BLYNK_WRITE(V0) {
  int lost = param.asInt();
  if (lost == 1) {
    Serial.println("lost");
    digitalWrite(buzzL,HIGH);
    delay(500);
    digitalWrite(buzzR,HIGH);
    delay(500);
    digitalWrite(buzzL,LOW);
    digitalWrite(buzzR,LOW);
  }
}

void setup() {
      Serial.begin(9600);
      BlynkEdgent.begin();
      pinMode(pingPin1, OUTPUT);
      pinMode(echoPin1, INPUT);
      pinMode(pingPin2, OUTPUT);
      pinMode(echoPin2, INPUT);
      pinMode(pingPin3, OUTPUT);
      pinMode(echoPin3, INPUT);
      pinMode(buzzL, OUTPUT);
      pinMode(buzzR, OUTPUT);
      pinMode(light, INPUT);
}

void loop() {
  BlynkEdgent.run();
   sens();
   if (cm1<100){
    digitalWrite(buzzL,HIGH);
    delay(1000);
    digitalWrite(buzzL,LOW);
    delay(500);
   }
   if (cm2<100){
    digitalWrite(buzzR,HIGH);
    delay(1000);
    digitalWrite(buzzR,LOW);
    delay(500);
   }
   if (cm3<100){
    digitalWrite(buzzL,HIGH);
    digitalWrite(buzzR,HIGH);
    delay(1000);
    digitalWrite(buzzL,LOW);
    digitalWrite(buzzR,LOW);
    delay(500);
   }
   while (ldrprv != ldr){
    Serial.println("changed");
    digitalWrite(buzzL,HIGH);
    delay(500);
    digitalWrite(buzzR,HIGH);
    delay(500);
    digitalWrite(buzzL,LOW);
    digitalWrite(buzzR,LOW);
    break;
   }
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void sens(){
   digitalWrite(pingPin1, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin1, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin1, LOW);
   duration1 = pulseIn(echoPin1, HIGH);
   cm1 = microsecondsToCentimeters(duration1);
   Serial.print(cm1);
   Serial.print("cm   -");

   digitalWrite(pingPin2, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin2, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin2, LOW);
   duration2 = pulseIn(echoPin2, HIGH);
   cm2 = microsecondsToCentimeters(duration2);
   Serial.print(cm2);
   Serial.print("cm   -");

   digitalWrite(pingPin3, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin3, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin3, LOW);
   duration3 = pulseIn(echoPin3, HIGH);
   cm3 = microsecondsToCentimeters(duration3);
   Serial.print(cm3);
   Serial.print("cm");
   Serial.println();
   Serial.println();
   ldrprv = digitalRead(light);
   delay(1000);
   ldr = digitalRead(light);
   Serial.println(ldrprv);
   Serial.println(ldr);
}
