#include <MSE2202_Lib.h>

#define MEDIUM_TUBE_MOTOR_A   4
#define MEDIUM_TUBE_MOTOR_B   5

#define SMALL_TUBE_MOTOR_A    6
#define SMALL_TUBE_MOTOR_B    7

#define DRIVE_MOTOR_A         15
#define DRIVE_MOTOR_B         16

#define TUBE_ROLLER_MOTOR_A   17
#define TUBE_ROLLER_MOTOR_B   18

const int medium_tube_speed = 150;
const int small_tube_speed = 255;
const int drive_speed = 200;
const int tube_roll_speed = 255;

Motion Bot = Motion();

void setup() {
  Bot.driveBegin("D1", MEDIUM_TUBE_MOTOR_A, MEDIUM_TUBE_MOTOR_B, 0, 0); // setup motors for medium bridge
  Bot.driveBegin("D2", SMALL_TUBE_MOTOR_A, SMALL_TUBE_MOTOR_B, 0, 0);   // setup motors for small bridge
  Bot.driveBegin("D3", DRIVE_MOTOR_A, DRIVE_MOTOR_B, 0, 0); // setup motors for drive
  Bot.driveBegin("D4", TUBE_ROLLER_MOTOR_A, TUBE_ROLLER_MOTOR_B, 0, 0); // setup motor for locomotion over the bridge
}

void loop() {
  Bot.Forward("D1", drive_speed, drive_speed);
  Bot.Forward("D2", drive_speed, drive_speed);
  delay(7000);

  Bot.Stop("D1");
  Bot.Stop("D2");
  Bot.Stop("D3");
  Bot.Stop("D4");
  delay(2000);

  Bot.Reverse("D1", drive_speed, drive_speed);
  Bot.Reverse("D2", drive_speed, drive_speed);
  delay(4000);

  Bot.Stop("D1");
  Bot.Stop("D2");
  Bot.Stop("D3");
  Bot.Stop("D4");
  delay(4000);
}
