#include <arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
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
    logger_init(LOG_FATAL|LOG_ERROR|LOG_WARNING|LOG_INFO);

    for (;;)
    {
#ifdef UART_INPUT
        uart_handle();
#endif
        printf("alive\n");
        delay(500);
    }

    return 0;
}

