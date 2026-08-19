int TRIG_PIN = 13;
int ECHO_PIN = 12;
int MOTOR_PIN1 = 6; //motor 1
int MOTOR_PIN2 = 5; // motor 2
int MOTOR_PIN3 = 3; // motor 1
int MOTOR_PIN4 = 4; // motor 2

float SPEED_OF_SOUND = 0.0345;
int flag = 0;


void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}


void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float cms = microsecs*SPEED_OF_SOUND/2;
  Serial.println(cms);
  if (cms < 7) {
    flag = 1;
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
    digitalWrite(MOTOR_PIN3, LOW);
    digitalWrite(MOTOR_PIN4, LOW);

    delay(100);
  } 
  else {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN3, LOW);
    digitalWrite(MOTOR_PIN2, HIGH);
    digitalWrite(MOTOR_PIN4, LOW);
  }
  if (flag == 1) {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN3, LOW);
    digitalWrite(MOTOR_PIN4, HIGH);
    digitalWrite(MOTOR_PIN2, LOW);
  }
  delay(10);
}