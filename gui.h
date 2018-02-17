#ifndef GUI_H
#define GUI_H

#include <display.h>

void gui_init();

void gui_show_menu();
void gui_show_menu_item(String item, int position, boolean selected);

void gui_show_menu_page_int(String menuItem, int value);
void gui_show_menu_page_string(String menuItem, String value);

void gui_reset_default();

extern int page;
extern int menuitem;
extern int frame;
extern int lastMenuItem;
extern int selectedLanguage;
extern int selectedDifficulty;
extern String menuItem5;

#endif

