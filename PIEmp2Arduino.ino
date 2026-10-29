#include <Servo.h>
#include <math.h>
// servo
const int PAN_Pin = 9;
const int TILT_Pin = 10;

Servo panServo;
Servo tiltServo;

// sensor
const int IR_PIN = A0;

// Exponential equation parameters from graph
const float A_PARAM = 3.95;
const float B_PARAM = -0.0211;

float readDistanceCM() {
  int rawADC = analogRead(IR_PIN);
  float voltage = rawADC * (5.0 / 1023.0);  // converts ADC to volts (5V / 1,024 levels)

  float distanceCM = log(voltage / A_PARAM) / B_PARAM;
  if (distanceCM < 0) return 0.0;
  return distanceCM;
}

void setup() {
  Serial.begin(9600);

  panServo.attach(PAN_Pin);
  tiltServo.attach(TILT_Pin);

  panServo.write(0);
  tiltServo.write(60);

  delay(1000);
}

void loop() {

  float a, b, c, d;

  a = 0;
  b = 0;
  c = 0;
  d = 0;

  static int currentPan = 0;
  int PanstepSize = 2;
  static int panDirection = 1;  // 1 = turn left? (0 -> 180)
  int panMin = 0;
  int panMax = 90;

  static int currentTilt = 60;
  int tiltMin = 60;
  int tiltMax = 150;

  int TiltstepSize = 2;
  static int tiltDirection = 1;

  static bool isScanning = true;

  if (!isScanning) {
    return;
  }
  panServo.write(currentPan);
  tiltServo.write(currentTilt);


  delay(100);  // allow time for servo to move before scanning

  float dist = readDistanceCM();
  // if (dist > 0.0 && dist <= 150.0) {
  if (dist > 0.0) {

    float panRad = currentPan;
    float tiltRad = currentTilt;

    a = dist;
    b = dist;
    c = panRad;
    d = tiltRad;

  currentTilt += (TiltstepSize * tiltDirection);
  if (currentTilt >= tiltMax) {  // if servo is turned to the left, turn right
    currentTilt = tiltMax;
    tiltDirection = -1;  // -1 = turn right (180 -> 0)

    currentPan += (PanstepSize * panDirection);
  } else if (currentTilt < tiltMin) {
    currentTilt = tiltMin;
    tiltDirection = 1;
    currentPan += (PanstepSize * panDirection);
  }

  if (currentPan > panMax) {
    isScanning = false;
  } else if (currentPan < panMin) {
    currentPan = panMin;
    panDirection = 1;
  }



  //
  // transmit one line of text to phython with 4 numeric values
  // NOTE: commas are sent between values, after the last value a Newline is sent
  //
  Serial.print(a);
  Serial.print(",");
  Serial.print(b);
  Serial.print(",");
  Serial.print(c);
  Serial.print(",");
  Serial.println(d);

  //
  // delay after sending data so the serial connection is not over run
  //
  delay(400);
}
}