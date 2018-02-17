#ifndef ENCODER_H
#define ENCODER_H

#include <ClickEncoder.h>

void encoder_init();
void encoder_read();

extern boolean up;
extern boolean down;
extern boolean middle;
extern ClickEncoder *encoder;

#endif

