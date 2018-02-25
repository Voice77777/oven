#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define DISPLAY_BL_ON  LOW
#define DISPLAY_BL_OFF HIGH

Adafruit_PCD8544* display_init();
void display_set_contrast(int contrast);
void display_backlight(int mode);

extern Adafruit_PCD8544* display;

#endif
