#include "Timer.h"

const int LED1 = 13;
const unsigned long PERIOD1 = 1000;    //one second

Timer t;                               //instantiate the timer object
Timer led;                            //timer for analogRead function.

void setup(void)

{
    Serial.begin(9600);
    pinMode(LED1, OUTPUT);
    t.oscillate(LED1, PERIOD1, HIGH);
    led.every(100,readData);
}


void loop()
{
    t.update();
    led.update();
}

void readData(){
  Serial.println(analogRead(A0));
  return 0;
}
