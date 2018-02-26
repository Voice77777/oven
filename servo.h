#ifndef SERVO_H
#define SERVO_H

void servo_init();
void servo_set_pos(int pos);

/* must be called every 50 ms */
void servo_isr();

#endif

