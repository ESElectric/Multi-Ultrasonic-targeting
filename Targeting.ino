#include <NewPing.h>

int pos = 0;
int max_dist_cm = 15;

// Pin definitions for forward sensors
int TP1 = 8;
int EP1 = 9;

// Pin definitions for left sensors
int TP2 = 10;
int EP2 = 11;

// Pin definitions for right sensors
int TP3 = 12;
int EP3 = 13;

// Pin definitions for back sensors
int TP4 = 14;
int EP4 = 15;

NewPing sonar(TP1, EP1);
NewPing lonar(TP2, EP2);
NewPing ronar(TP3, EP3);
NewPing bonar(TP4, EP4);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int SR = sonar.ping_cm();
  int LR = lonar.ping_cm();
  int RR = ronar.ping_cm();
  int BR = bonar.ping_cm();

  int closestDist = max_dist_cm; // Initialize to maximum distance
  String closestDirection = "";

  if (SR < closestDist && SR <= LR && SR <= RR && SR <= BR) {
    closestDist = SR;
    closestDirection = "Forward";
  }
  if (LR < closestDist && LR < SR && LR <= RR && LR <= BR) {
    closestDist = LR;
    closestDirection = "Left";
  }
  if (RR < closestDist && RR < SR && RR < LR && RR <= BR) {
    closestDist = RR;
    closestDirection = "Right";
  }
  if (BR < closestDist && BR < SR && BR < LR && BR < RR) {
    closestDist = BR;
    closestDirection = "Backward";
  }

  if (closestDist < max_dist_cm) {
    Serial.print("Closest Object: ");
    Serial.print(closestDirection);
    Serial.print(" Distance: ");
    Serial.println(closestDist);
  }

  delay(200); // Adjust delay as needed for your application
}
