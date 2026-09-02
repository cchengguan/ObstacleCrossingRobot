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
int stop = 0;
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
  ser.write(130);
  Serial.begin(9600);
}

void servotest() {
  ser.write(20);
  delay(1000);
  ser.write(130);
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

void offall(int* stop) {
  digitalWrite(MOTOR_PIN1L, LOW);
  digitalWrite(MOTOR_PIN2L, LOW);
  digitalWrite(MOTOR_PIN3R, LOW);
  digitalWrite(MOTOR_PIN4R, LOW);
  *stop = 1;
}

float getDistance() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float cms_from_wall = microsecs * SPEED_OF_SOUND / 2;

  return cms_from_wall;
}

void loop() {
  double cms_from_wall = getDistance();
  int interval = 4000;
  int dist = 7;
  Serial.println(cms_from_wall);
  
  if (cms_from_wall < dist && flag != 1) {
    count = millis();
    flag = 1;
    offall(&stop);
    servotest();
  } 
  if (stop == 0) {
    forward();
  }
  else if (stop == 1 && millis() - count > interval && flag == 1) {
    backward();
    count = millis();
  }

  delay(50);
}