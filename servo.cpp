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
