#include <NewPing.h>

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

NewPing sonar(TP1, EP1);
NewPing lonar(TP2, EP2);
NewPing ronar(TP3, EP3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int SR = sonar.ping_cm();
  int LR = lonar.ping_cm();
  int RR = ronar.ping_cm();

  Serial.print("SR: ");
  Serial.print(SR);
  Serial.print(" LR: ");
  Serial.print(LR);
  Serial.print(" RR: ");
  Serial.println(RR);

  int closestDist = max_dist_cm; // Initialize to maximum distance
  String closestDirection = "";

  while (SR <= closestDist || LR <= closestDist || RR <= closestDist) {
    if (SR <= closestDist) {
      if (SR == closestDist && (LR == closestDist || RR == closestDist)) {
        // Print when SR is equal to LR or RR
        Serial.print("Forward distance is equal to ");
        if (LR == closestDist) Serial.print("Left");
        if (RR == closestDist) Serial.print("Right");
        Serial.print(" distance: ");
        Serial.print(SR);
        Serial.println(" cm");
      } else {
        closestDist = SR;
        closestDirection = "Forward";
      }
    }
    if (LR <= closestDist) {
      if (LR == closestDist && RR == closestDist) {
        // Print when LR is equal to RR
        Serial.print("Left distance is equal to Right distance: ");
        Serial.print(LR);
        Serial.println(" cm");
      } else {
        closestDist = LR;
        closestDirection = "Left";
      }
    }
    if (RR <= closestDist) {
      closestDist = RR;
      closestDirection = "Right";
    }
  }

  if (closestDist < max_dist_cm) {
    Serial.print("Closest Object: ");
    Serial.print(closestDirection);
    Serial.print(" Distance: ");
    Serial.println(closestDist);
  } else {
    Serial.println("No obstacles within range.");
  }

  delay(2000); // Adjust delay as needed for your application
}
