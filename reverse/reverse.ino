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
unsigned long count = 0;
const unsigned long reverseDelay = 1400; // 1.4 seconds

void setup() {
  pinMode(MOTOR_PIN1L, OUTPUT);
  pinMode(MOTOR_PIN2L, OUTPUT);
  pinMode(MOTOR_PIN3R, OUTPUT);
  pinMode(MOTOR_PIN4R, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  ser.attach(3);
  ser.write(130);
  Serial.begin(115200);
}

void servotest() {
  ser.write(50);
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

double getDistance() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH, 20000);
  double cms_from_wall = microsecs * SPEED_OF_SOUND / 2;

  return cms_from_wall;
}

void loop() {
  double cms_from_wall = getDistance();
  int interval = 1000;
  int dist = 13;
  Serial.println(cms_from_wall);

  if (cms_from_wall != 0) {
    if (cms_from_wall < dist && flag == 0) {
    flag = 1;
    offall(&stop);
    servotest();
    count = millis();
    }
  }
 
  if (stop == 0) {
    forward();
  }
  
  if (stop == 1 &&
    flag == 1 &&
    millis() - count >= reverseDelay) {
    backward();
  }
}



