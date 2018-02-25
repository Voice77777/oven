#ifndef MENU_H
#define MENU_H

#include <gui.h>

void menu_reset_default();

/* FIXME: убрать? */
String menu_get_item_string(int menuitem);
int menu_get_item_menu_level(int menuitem);

int menu_handle_event(int menu_item, gui_event_t event);

extern const int menu_menuitem_number;
#endif

