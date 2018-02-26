#include <SoftwareServo.h>

SoftwareServo servo;

void servo_init()
{
    servo.attach(3);
}

void servo_isr()
{
    SoftwareServo::refresh();
}

void servo_set_pos(int pos)
{
    servo.write(pos);
}

#if 0
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
#endif
