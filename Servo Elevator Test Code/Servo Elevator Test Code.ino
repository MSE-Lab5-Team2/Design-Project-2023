#include <MSE2202_Lib.h>

Motion Bot = Motion();

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
int servo1_raise = 1741;
int servo2_raise = 1743;
int servo3_raise = 1774;
int servo4_raise = 1775;

// lowering bot values
int servo1_lower = 1780;
int servo2_lower = 1782;
int servo3_lower = 1736;
int servo4_lower = 1742;

// function to rotate all servos
void elevate_bot(int speed1, int speed2, int speed3, int speed4) {
  Bot.ToPosition("S1", speed1);
  Bot.ToPosition("S2", speed2);
  Bot.ToPosition("S3", speed3);
  Bot.ToPosition("S4", speed4);
}

void setup() {
  //initialize servos
  Bot.servoBegin("S1", SERVO_1);
  Bot.servoBegin("S2", SERVO_2);
  Bot.servoBegin("S3", SERVO_3);
  Bot.servoBegin("S4", SERVO_4);

}

void loop() {
  delay(2000);

// raise
  elevate_bot(servo1_raise, servo2_raise, servo3_raise, servo4_raise);
  delay(7000);

// stop
  elevate_bot(servo_neutral, servo_neutral, servo_neutral, servo_neutral);
  delay(2000);

// lower
  elevate_bot(servo1_lower, servo2_lower, servo3_lower, servo4_lower);
  delay(7000);

// stop
  elevate_bot(servo_neutral, servo_neutral, servo_neutral, servo_neutral);

}
