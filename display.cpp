#include <display.h>

boolean backlight = true;
int contrast      = 60;
int volume        = 50;

Adafruit_PCD8544 display_static = Adafruit_PCD8544(9, 8, 7, 6, 5);
Adafruit_PCD8544* display;

Adafruit_PCD8544* display_init()
{
    // Download the latest Adafruit Library in order to use this constructor
    //display = new Adafruit_PCD8544(9, 8, 7, 6, 5);
    display = &display_static;

    // For backlight control
    pinMode(7, OUTPUT);
    display_backlight(DISPLAY_BL_ON);

    display->begin();
    display->clearDisplay();
    display_set_contrast();

    return display;
}

void display_set_contrast()
{
    display->setContrast(contrast);
    display->display();
}

void display_backlight(int mode)
{
    digitalWrite(7, mode);
}

