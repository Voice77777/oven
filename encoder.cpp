#include <encoder.h>
#include <TimerOne.h>

boolean up = false;
boolean down = false;
boolean middle = false;

ClickEncoder *encoder;
int16_t last, value;

void timerIsr() {
    encoder->service();
}

void encoder_init()
{
    encoder = new ClickEncoder(A1, A0, A2);
    encoder->setAccelerationEnabled(false);

    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerIsr);

    last = encoder->getValue();
}

void encoder_read()
{
    value += encoder->getValue();

    if (value/2 > last) {
        last = value/2;
        down = true;
        delay(150);
    }else   if (value/2 < last) {
        last = value/2;
        up = true;
        delay(150);
    }
}


