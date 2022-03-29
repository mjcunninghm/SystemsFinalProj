#include <time.h>

int leftLight = 8;
int rightLight = 9;

int leftSensor;
int rightSensor;
int leftValue;
int rightValue;

int ap_threshold;

clock_t t;
double duration;

unsigned long baud = 250000;

void setup() {
  Serial.begin(baud);
  pinMode(leftLight, OUTPUT);
  pinMode(rightLight, OUTPUT);
}

void loop() {
  int wait = random(1,5);
  delay(wait);
  
  int light = random(1,3);
  if (light == 1) {
    digitalWrite(leftLight, HIGH);
    t = clock();
    // while leftSensor < ap_threshold
      // continue;
      
    t = clock() - t;
    digitalWrite(leftLight, LOW);
    duration = ((double)t)/CLOCKS_PER_SEC;

    Serial.printf("LEFT %d", duration);
  }
  else if (light == 2) {
    digitalWrite(rightLight, HIGH);
    t = clock();
    // while rightSensor < ap_threshold
      // continue;

    t = clock() - t;
    digitalWrite(rightLight, LOW);
    duration = ((double)t)/CLOCKS_PER_SEC;

    Serial.printf("RIGHT %d", duration);
  }
  else {
    digitalWrite(leftLight, HIGH);
    digitalWrite(rightLight, HIGH);
    t = clock();
    // while leftSensor < ap_threshold || rightSensor < ap_threshold
      // if leftSensor < ap_threshold && rightSensor >= ap_threshold
        // digitalWrite(leftLight, HIGH);
        // digitalWrite(rightLight, LOW);
      // else if leftSensor >= ap_threshold
        // digitalWrite(rightLight, HIGH);
        // digitalWrite(leftLight, LOW);
      // else
        // digitalWrite(leftLight, HIGH);
        // digitalWrite(rightLight, HIGH);
      // continue;

    t = clock() - t;
    digitalWrite(leftLight, LOW);
    digitalWrite(rightLight, LOW);
    duration = ((double)t)/CLOCKS_PER_SEC;

    Serial.printf("LEFT/RIGHT %d", duration);
  }
}
