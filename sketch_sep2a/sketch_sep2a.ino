#include <Servo.h>

// ============================================================
// PIN DEFINITIONS
// ============================================================

// L293D motor driver input pins
// These correspond to 1A, 2A, 3A and 4A on the L293D.
const int MOTOR_1A = 13;
const int MOTOR_2A = 12;
const int MOTOR_3A = 11;
const int MOTOR_4A = 10;

// Ultrasonic sensor pins
// CHANGE THESE TWO if TRIG/ECHO are connected to different pins.
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;

// Servo signal pin
// CHANGE THIS if your servo signal wire is connected elsewhere.
const int SERVO_PIN = 9;


// ============================================================
// SETTINGS
// ============================================================

// Robot stops when an object is 5 cm or less away.
const float STOP_DISTANCE = 5.0;

// Create the Servo object.
Servo releaseServo;


// ============================================================
// SETUP
// Runs ONCE when the Arduino is powered/reset.
// ============================================================

void setup() {

  // ---------------- MOTOR SETUP ----------------
  // Tell the Arduino that the four L293D control pins are outputs.
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_2A, OUTPUT);
  pinMode(MOTOR_3A, OUTPUT);
  pinMode(MOTOR_4A, OUTPUT);


  // ---------------- ULTRASONIC SENSOR SETUP ----------------
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  // ---------------- SERVO SETUP ----------------
  releaseServo.attach(SERVO_PIN);

  // Set servo to its initial position.
  releaseServo.write(0);

  // Give the servo a short time to reach 0 degrees
  // before the robot begins moving.
  delay(1000);
}


// ============================================================
// MAIN PROGRAM
// ============================================================

void loop() {

  // ==========================================================
  // STEP 1:
  // DRIVE FORWARD TOWARDS THE WALL
  // ==========================================================

  moveForward();


  // ==========================================================
  // STEP 2:
  // KEEP MOVING UNTIL THE ULTRASONIC SENSOR DETECTS
  // THE WALL AT 5 cm OR LESS
  // ==========================================================

  while (getDistance() > STOP_DISTANCE) {

    // No additional command is needed here.
    // The motors continue running because moveForward()
    // has already switched them on.

  }


  // ==========================================================
  // STEP 3:
  // WALL IS WITHIN 5 cm -> STOP ALL FOUR MOTORS
  // ==========================================================

  stopMotors();


  // ==========================================================
  // STEP 4:
  // WHILE THE ROBOT IS STATIONARY,
  // ROTATE THE SERVO FROM 0 degrees TO 180 degrees
  // ==========================================================

  releaseServo.write(180);

  // Give the servo time to physically reach 180 degrees.
  // Adjust this if your servo needs more/less time.
  delay(1000);


  // ==========================================================
  // STEP 5:
  // SERVO HAS FINISHED MOVING.
  // WAIT 5 SECONDS BEFORE REVERSING.
  // ==========================================================

  delay(5000);


  // ==========================================================
  // STEP 6:
  // REVERSE ALL FOUR MOTORS.
  //
  // The robot will continue travelling backwards.
  // There is intentionally NO stopping condition because
  // you said the robot does not need to stop after crossing
  // back over the bump.
  // ==========================================================

  moveBackward();


  // ==========================================================
  // IMPORTANT:
  // Prevent loop() from restarting the entire sequence.
  //
  // Without this, the Arduino would eventually repeat the
  // forward -> stop -> servo -> reverse sequence.
  // ==========================================================

  while (true) {
    // Robot continues reversing because the L293D outputs
    // remain in the state set by moveBackward().
  }
}


// ============================================================
// FUNCTION: moveForward()
//
// Makes all four motors drive the robot towards the wall.
//
// Your circuit uses two L293D H-bridges:
//   MOTOR_1A / MOTOR_2A -> one pair of motors
//   MOTOR_3A / MOTOR_4A -> other pair of motors
// ============================================================

void moveForward() {

  // Motor pair 1
  digitalWrite(MOTOR_1A, HIGH);
  digitalWrite(MOTOR_2A, LOW);

  // Motor pair 2
  digitalWrite(MOTOR_3A, HIGH);
  digitalWrite(MOTOR_4A, LOW);
}


// ============================================================
// FUNCTION: moveBackward()
//
// Reverses the polarity applied to both motor pairs.
// This causes all four motors to rotate in the opposite
// direction and the robot to travel backwards.
// ============================================================

void moveBackward() {

  // Reverse motor pair 1
  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_2A, HIGH);

  // Reverse motor pair 2
  digitalWrite(MOTOR_3A, LOW);
  digitalWrite(MOTOR_4A, HIGH);
}


// ============================================================
// FUNCTION: stopMotors()
//
// Both inputs of each H-bridge are set LOW.
// Therefore, the motors are no longer commanded to rotate.
// ============================================================

void stopMotors() {

  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_2A, LOW);

  digitalWrite(MOTOR_3A, LOW);
  digitalWrite(MOTOR_4A, LOW);
}


// ============================================================
// FUNCTION: getDistance()
//
// Uses the ultrasonic sensor to measure the distance
// between the robot and the wall.
//
// Returns distance in centimetres.
// ============================================================

float getDistance() {

  // Make sure TRIG starts LOW.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);


  // Send a 10 microsecond ultrasonic trigger pulse.
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  // Measure how long the echo pulse takes to return.
  long duration = pulseIn(ECHO_PIN, HIGH);


  // Convert echo travel time into distance.
  //
  // Speed of sound is approximately 0.0343 cm/us.
  //
  // Divide by 2 because the sound travels:
  //
  // sensor -> wall -> sensor
  //
  float distance = duration * 0.0343 / 2.0;


  return distance;
}