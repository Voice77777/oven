#ifndef ENCODER_H
#define ENCODER_H

#include <ClickEncoder.h>

void encoder_init();
void encoder_read();

/* must be called every 50 ms */
void encoder_isr();

extern ClickEncoder *encoder;

#endif

