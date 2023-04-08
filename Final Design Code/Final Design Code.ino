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

// pin numbers for servos
#define SERVO_1 39
#define SERVO_2 40
#define SERVO_3 41
#define SERVO_4 42

// servo value to not move
const int servo_neutral = 1757; // depends on how you calibrated servos
/*
  lower than neutral will cause clockwise rotation (when looking at the servo from above), higher than neutral --> counter-clockwise rotation
  the further away from the neutral value the set value is, the faster the servo will turn (ex. 1700 will run very quickly compared to 1740)
  rotation is quite sensitive, there is a noticeable difference between 1740 and 1742.
*/

// raising bot values
const int servo1_raise = 1741;
const int servo2_raise = 1743;
const int servo3_raise = 1774;
const int servo4_raise = 1775;

// lowering bot values
const int servo1_lower = 1780;
const int servo2_lower = 1782;
const int servo3_lower = 1736;
const int servo4_lower = 1742;

const int medium_tube_speed = 150;
const int small_tube_speed = 155;
const int drive_speed = 150;
const int tube_roll_speed = 255;

Motion Bot = Motion();

// function to get the distance detected by the ultrasonic sensor
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

// function to rotate all servos
void elevate_bot(int speed1, int speed2, int speed3, int speed4) {
  Bot.ToPosition("S1", speed1);
  Bot.ToPosition("S2", speed2);
  Bot.ToPosition("S3", speed3);
  Bot.ToPosition("S4", speed4);
}

void setup() {
  Bot.driveBegin("D1", MEDIUM_TUBE_MOTOR_A, MEDIUM_TUBE_MOTOR_B, 0, 0); // setup motors for medium bridge
  Bot.driveBegin("D2", SMALL_TUBE_MOTOR_A, SMALL_TUBE_MOTOR_B, 0, 0);   // setup motors for small bridge
  Bot.driveBegin("D3", DRIVE_MOTOR_A, DRIVE_MOTOR_B, 0, 0); // setup motors for drive
  Bot.driveBegin("D4", TUBE_ROLLER_MOTOR_A, TUBE_ROLLER_MOTOR_B, 0, 0); // setup motor for locomotion over the bridge

  // initialize ultrasonic sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  //initialize servos
  Bot.servoBegin("S1", SERVO_1);
  Bot.servoBegin("S2", SERVO_2);
  Bot.servoBegin("S3", SERVO_3);
  Bot.servoBegin("S4", SERVO_4);
}

void loop() {
  delay(2000);
  Bot.Forward("D3", drive_speed, drive_speed);

// stop if detected distance is greater than 60 centimetres
  while (1){
    delay(1);
    double sensor_distance = getDistance();
    if(sensor_distance > 60) {
      break;
    }
  }

// stop driving
  Bot.Stop("D3");

  delay(2000);

  elevate_bot(servo1_raise, servo2_raise, servo3_raise, servo4_raise);

  delay(7000);

  elevate_bot(servo_neutral, servo_neutral, servo_neutral, servo_neutral);

  delay(2000);

  // extend bridge
  Bot.Forward("D1", medium_tube_speed, medium_tube_speed);
  Bot.Forward("D2", small_tube_speed, small_tube_speed);
  
  delay(2000);

// variables to record the length of time to extend
unsigned long extend_start = millis();
unsigned long extend_end = millis();
// extend bridge until detected distance is less than 50 centimetres
  while (1){
    delay(1);
    double sensor_distance = getDistance();
    if(sensor_distance < 50) {
      extend_end = millis();
      break;
    }
  }

  Bot.Stop("D1");
  Bot.Stop("D2");

elevate_bot(servo1_lower, servo2_lower, servo3_lower, servo4_lower);

// lower bot until detected distance is less than 7 centimetres (or greater than 50, the distance will shoot up when actual distance is less than 2 centimetres)
while (1){
    delay(1);
    double sensor_distance = getDistance();
    if(sensor_distance < 7 || sensor_distance > 50) {
      break;
    }
  }
  
elevate_bot(servo_neutral, servo_neutral, servo_neutral, servo_neutral);

// drive across the briddge while also activating drive motors
Bot.Forward("D3", drive_speed, drive_speed);
Bot.Forward("D4", tube_roll_speed, tube_roll_speed);

// variables to record bridge crossing time
unsigned long cross_start = millis();
unsigned long cross_end = millis();
// stay in loop until detected distance changes (wheels will hit the table and lift the bot up slightly) effectively will stay in loop until bot reaches the other side
dowhile (1){
    delay(1);
    double sensor_distance = getDistance();
    if(sensor_distance != ) {
      break;
    }
    double distance_before = sensor_distance;
  }

// allows the bot to fully get on the table
delay(1500);

Bot.Stop("D3");
Bot.Stop("D4");

delay(2000);

// retract servos
elevate_bot(servo1_lower, servo2_lower, servo3_lower, servo4_lower);
delay(5000);
elevate_bot(servo_neutral, servo_neutral, servo_neutral, servo_neutral);

// bring the bridge and servos across the gap
Bot.Reverse("D4", tube_roll_speed, tube_roll_speed);
delay(cross_end - cross_start);
Bot.Stop("D4");

// retract the bridge
Bot.Reverse("D1", medium_tube_speed, medium_tube_speed);
Bot.Reverse("D2", small_tube_speed, small_tube_speed);
delay(extend_end - extend_start);
Bot.Stop("D1");
Bot.Stop("D2");

delay(2000);

// drive bot forward to edge
Bot.Forward("D3", drive_speed, drive_speed);

// stop if detected distance is greater than 60 centimetres
  while (1){
    delay(1);
    double sensor_distance = getDistance();
    if(sensor_distance > 60) {
      break;
    }
  }

// reverse until desired distance
Bot.Reverse("D3", drive_speed, drive_speed);
delay(5000);
}