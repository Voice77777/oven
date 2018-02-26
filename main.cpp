#include <arduino.h>

#include <gui.h>
#include <fsm.h>

#include <encoder.h>
#include <servo.h>

#include <TimerOne.h>

#include <stdio.h>
#include <util/delay.h>

#include <uart.h>
#include <logger.h>

#include <config.h>

#define SERIAL_SPEED 57600

void main_isr()
{
    static char servo_cnt = 0;

    /* must be called every 50 ms */
    if (servo_cnt++ > 50) {
        servo_cnt = 0;
        servo_isr();
    }

    /* must be called every 50 ms */
    encoder_isr();
}

int main()
{
    init();
    uart_init(SERIAL_SPEED);
    //logger_init(LOG_FATAL|LOG_ERROR|LOG_WARNING|LOG_INFO);
    //logger(LOG_INFO, "Oven Control by Voice Arniman (c) 2018\n");

    /* 0.001 s === 1 ms == 1000 mcs */
    Timer1.initialize(1000);
    Timer1.attachInterrupt(main_isr);

    gui_init();
    fsm_init();

    gui_show_menu();

    for (;;)
    {
        fsm_step();
    }

    return 0;
}

