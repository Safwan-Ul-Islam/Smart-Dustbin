#include <Servo.h>

#define TRIG_PIN D1 // Define the TRIG pin for the ultrasonic sensor
#define ECHO_PIN D2 // Define the ECHO pin for the ultrasonic sensor
#define SERVO_PIN D3 // Define the servo pin

Servo trashLid; // Create a Servo object

const int openAngle = 160;   // Angle to open the trash can lid
const int closeAngle = 0;   // Angle to close the trash can lid
const int detectionDistance = 20; // Distance in cm to detect a person

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  trashLid.attach(SERVO_PIN);
  trashLid.write(closeAngle); // Start with the lid closed
  Serial.begin(9600);         // Start serial communication for debugging
}

void loop() {
  long duration, distance;

  // Send a 10us pulse to trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the time for the echo to return
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Open the lid if a person is detected within the detection distance
  if (distance > 0 && distance <= detectionDistance) {
    trashLid.write(openAngle);
  } else {
    trashLid.write(closeAngle);
  }

  delay(200); // Add a small delay to avoid rapid triggering
}
