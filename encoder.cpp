#include <encoder.h>
#include <TimerOne.h>

ClickEncoder *encoder;

void encoder_isr() {
    encoder->service();
}

void encoder_init()
{
    encoder = new ClickEncoder(A1, A0, A2);
    encoder->setAccelerationEnabled(false);
}
