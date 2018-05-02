#include <Arduino.h>
#include <Wire.h>
#include "BMP180.h"


BMP180 pressure;


long loopTime = 0;
float runningAlt = 0;
float K = .8;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    //delay(5000);
    if(pressure.begin()){
      Serial.println("BMP INIT SUCCESS");
    }
    else{
      Serial.println("BMP INIT FAILURE! STOPPING");
      while(true);
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    Serial.println("Loop time: " + String(micros() - loopTime));
    loopTime = micros();
    double a, P;

    // Get a new pressure reading:

    P = pressure.getPressureAsync();

    // Show the relative altitude difference between
    // the new reading and the baseline reading:

    a = pressure.altitude(P);
    runningAlt = runningAlt*K + (1.0 - K)*a;
    Serial.println(runningAlt);
    Serial.println(P);
    delay(30);
}
