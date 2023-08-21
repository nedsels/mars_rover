int motorRight = 8;
int motorLeft = 9;
int sensorTrig = 2;
int sensorEcho = 3;
float lastDistance = 1000;
int turnMotor = motorRight;

void setup() {
  pinMode(motorRight, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(sensorTrig, OUTPUT);
  pinMode(sensorEcho, INPUT);
  Serial.begin(9600);
}

void loop() {
  delay(50);
  digitalWrite(sensorTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrig, LOW);

  float duration = pulseIn(sensorEcho, HIGH);
  float distanceInCm = duration / 29 / 2;

  Serial.print(distanceInCm);
  Serial.print("\n");

  // This is to change the direction in case the rover turns
  // and starts facing a wall:
  if (distanceInCm < lastDistance) {
    if (turnMotor == motorRight) {
      turnMotor = motorLeft;
    } else {
      turnMotor = motorRight;
    }
  }

  if (distanceInCm < 35) { // The distance could be adjusted
    digitalWrite(motorRight, LOW);
    digitalWrite(motorLeft, LOW);
    digitalWrite(turnMotor, HIGH);
    delay(250); // This gives short turns, in case the rover
                // starts to run into a wall
    digitalWrite(turnMotor, LOW);
  } else {
    digitalWrite(motorRight, HIGH);
    digitalWrite(motorLeft, HIGH);
  }

  lastDistance = distanceInCm;
}