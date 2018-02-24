#ifndef MENU_H
#define MENU_H

/* нам нужно сюда перенести gui.h из .cpp так как в gui.h
 * есть описание что такое gui_event_t, и оно используется
 * в описании фунции menu_handle_event()
 * */
#include <gui.h>

void menu_reset_default();
void menu_show_submenu(int menuitem);
void menu_backlight_toggle();
void menu_update_up_event(int menuitem);
void menu_update_down_event(int menuitem);
void menu_update_click_event(int menuitem);
String menu_get_item_string(int menuitem);

int menu_handle_event(int menu_item, gui_event_t event);

extern const int menu_menuitem_number;
#endif

