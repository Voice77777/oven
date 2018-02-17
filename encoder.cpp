#include <encoder.h>
#include <TimerOne.h>

ClickEncoder *encoder;

void timerIsr() {
    encoder->service();
}

void encoder_init()
{
    encoder = new ClickEncoder(A1, A0, A2);
    encoder->setAccelerationEnabled(false);

    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerIsr);
}
