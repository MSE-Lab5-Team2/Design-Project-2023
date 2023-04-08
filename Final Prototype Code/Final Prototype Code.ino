#include <MSE2202_Lib.h>

#define MEDIUM_TUBE_MOTOR_A   4
#define MEDIUM_TUBE_MOTOR_B   5

#define SMALL_TUBE_MOTOR_A    6
#define SMALL_TUBE_MOTOR_B    7

#define DRIVE_MOTOR_A         15
#define DRIVE_MOTOR_B         16

#define TUBE_ROLLER_MOTOR_A   17
#define TUBE_ROLLER_MOTOR_B   18

// ultrasonic pins
#define trigPin 2
#define echoPin 1

const int medium_tube_speed = 150;
const int small_tube_speed = 155;
const int drive_speed = 150;
const int tube_roll_speed = 255;

Motion Bot = Motion();

double getDistance() {
  double distance;
  long duration;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance in metres
  distance = duration * 0.034 / 2;
  
  return distance;
}

void setup() {
  Bot.driveBegin("D1", MEDIUM_TUBE_MOTOR_A, MEDIUM_TUBE_MOTOR_B, 0, 0); // setup motors for medium bridge
  Bot.driveBegin("D2", SMALL_TUBE_MOTOR_A, SMALL_TUBE_MOTOR_B, 0, 0);   // setup motors for small bridge
  Bot.driveBegin("D3", DRIVE_MOTOR_A, DRIVE_MOTOR_B, 0, 0); // setup motors for drive
  Bot.driveBegin("D4", TUBE_ROLLER_MOTOR_A, TUBE_ROLLER_MOTOR_B, 0, 0); // setup motor for locomotion over the bridge

  // initialize ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  delay(2000);
  Bot.Forward("D3", drive_speed, drive_speed);

  delay(2000);

  while (1){
    delay(1);
    double sensor_distance = getDistance();
    if(sensor_distance > 60) {
      break;
    }
  }

  Bot.Stop("D3");

  delay(2000);

  Bot.Forward("D1", medium_tube_speed, medium_tube_speed);
  Bot.Forward("D2", small_tube_speed, small_tube_speed);

  delay(10000);

  Bot.Stop("D1");
  Bot.Stop("D2");


  delay(100000);
}
