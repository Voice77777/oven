#include <arduino.h>

#include <gui.h>
#include <fsm.h>

#include <ClickEncoder.h>
#include <TimerOne.h>

#include <stdio.h>
#include <util/delay.h>

#include <uart.h>
#include <logger.h>

#include <config.h>

#define SERIAL_SPEED 57600

int main()
{
    init();
    uart_init(SERIAL_SPEED);
    //logger_init(LOG_FATAL|LOG_ERROR|LOG_WARNING|LOG_INFO);
    //logger(LOG_INFO, "Oven Control by Voice Arniman (c) 2018\n");

    gui_init();
    fsm_init();

    gui_show_menu();
    for (;;)
    {
        fsm_step();
    }

    return 0;
}

