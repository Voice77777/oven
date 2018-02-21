#ifndef MENU_H
#define MENU_H

void menu_reset_default();
void menu_show_submenu(int menuitem);
void menu_backlight_toggle();
void menu_update_up_event(int menuitem);
String menu_get_item_string(int menuitem);

extern const int menu_menuitem_number;
#endif

