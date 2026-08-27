#include <Servo.h>

Servo ser;
int TRIG_PIN = 9;
int ECHO_PIN = 8;
int MOTOR_PIN1L = 10; //motor 1
int MOTOR_PIN2L = 11; // motor 1
int MOTOR_PIN3R = 12; // motor 2
int MOTOR_PIN4R = 13; // motor 2
float SPEED_OF_SOUND = 0.0345;
int flag = 0;
unsigned long count = millis();


void setup() {
  pinMode(MOTOR_PIN1L, OUTPUT);
  pinMode(MOTOR_PIN2L, OUTPUT);
  pinMode(MOTOR_PIN3R, OUTPUT);
  pinMode(MOTOR_PIN4R, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  ser.attach(2);
  Serial.begin(9600);
}

void servotest() {
  ser.write(180);
  delay(100);
  ser.write(0);
}

void forward() {
  digitalWrite(MOTOR_PIN1L, HIGH);
  digitalWrite(MOTOR_PIN2L, LOW);
  digitalWrite(MOTOR_PIN3R, HIGH);
  digitalWrite(MOTOR_PIN4R, LOW);
}

void backward() {
  digitalWrite(MOTOR_PIN1L, LOW);
  digitalWrite(MOTOR_PIN2L, HIGH);
  digitalWrite(MOTOR_PIN3R, LOW);
  digitalWrite(MOTOR_PIN4R, HIGH);
}

void offall() {
  digitalWrite(MOTOR_PIN1L, LOW);
  digitalWrite(MOTOR_PIN2L, LOW);
  digitalWrite(MOTOR_PIN3R, LOW);
  digitalWrite(MOTOR_PIN4R, LOW);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float cms = microsecs * SPEED_OF_SOUND / 2;
  int interval = 4000;
  int dist = 7;
  Serial.println(cms);

  if (cms < dist) {
    flag = 1;
    offall();
    servotest();
  } 
  else if (flag != 1) {
    forward();
  }
  else if (flag == 1 && millis() - count > interval) {
    backward();
    count = millis();
  }

  delay(10);
}