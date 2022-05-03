// Analog variables
int leftLight = 7;
int rightLight = 8;
int leftSensor = A1;
int rightSensor = A2;

// Filter variables
int const order = 3;
unsigned int val_l[order];
unsigned int val_r[order];
unsigned long sum_l = 0;
unsigned long sum_r = 0;
float filt_val_l = 0;
float filt_val_r = 0;
int i, j;

float threshold = .15/5*1023;

// Timing variables
unsigned long left_t, right_t, t, t1;

// Serial communication
unsigned long baud = 250000;

void setup() {
  Serial.begin(baud);

  delay(1000);

  Serial.print(threshold);
  Serial.print("\n");

  for (i = 0; i < order - 1; i++) {
    val_l[i] = 0;
    val_r[i] = 0;
  }
  sum_l = 0;
  sum_r = 0;

  pinMode(leftLight, OUTPUT);
  pinMode(rightLight, OUTPUT);
}

void loop() {
  int wait = random(1000,5000);
  delay(wait);

  //int light = random(1,3);
  int light = 1;
  
  if (light == 1) {
    sum_l = 0;
    
    for (i = 0; i < order - 1; i++) {
      val_l[i] = analogRead(leftSensor);
      delayMicroseconds(1000);
      sum_l += val_l[i];
    }
    
    digitalWrite(leftLight, HIGH);
    t = micros();
    filt_val_l = 0;
    
    while (filt_val_l < threshold) {
      t1 = micros();

      val_l[i] = analogRead(leftSensor);
      
      sum_l += val_l[i++];
      filt_val_l = (float)sum_l / order;
      i = i%order;
      sum_l -= val_l[i];

      //Serial.print(filt_val_l);
      //Serial.print("\n");

      /*if (filt_val_l > threshold) {
        float aoc = 0;
        float prev_filt_val_l;
        float count = 0;
        
        for (int n = 1; n < 2000; n++) {
          if (val_l[i] == 0) {
            continue;
          }
          
          prev_filt_val_l = filt_val_l;
          
          val_l[i] = analogRead(leftSensor);
          sum_l += val_l[i++];
          filt_val_l = (float)sum_l / order;

          aoc += (filt_val_l + prev_filt_val_l)*(.001/2);
          
          i = order - i;
          sum_l -= val_l[i];

          count++;
        }

        aoc = aoc/count;

        if (aoc > .01) {
          filt_val_l > threshold;
        }
        else {
          filt_val_l < threshold;
        }
      }*/

      delayMicroseconds(1000 - (micros() - t1));
    }
      
    t = micros() - t;
    t = (float) t/1000;
    digitalWrite(leftLight, LOW);

    Serial.print("LEFT Reaction Time: ");
    Serial.print(t);
    Serial.print("ms");
    Serial.print("\n");
  }
  else if (light == 2) {
    for (i = 0; i < order - 1; i++) {
      val_r[i] = analogRead(rightSensor);
      delayMicroseconds(1000);
      sum_r += val_r[i];
    }
    
    digitalWrite(rightLight, HIGH);
    t = micros();
    filt_val_r = 0;
    
    while (filt_val_r < threshold) {
      t1 = micros();

      val_r[i] = analogRead(rightSensor);
      sum_r += val_r[i++];
      filt_val_r = (float)sum_r / order;
      i = order - i;
      sum_r -= val_r[i];

      Serial.print(filt_val_r);
      Serial.print("\n");

      delayMicroseconds(1000 - (micros() - t1));
    }

    t = micros() - t;
    digitalWrite(rightLight, LOW);

    Serial.print("RIGHT Reaction Time: ");
    Serial.print(t);
    Serial.print("s");
    Serial.print("\n");
  }
}
