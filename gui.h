#ifndef GUI_H
#define GUI_H

#include <display.h>

typedef enum {
     GUI_EVENT_INIT        = 1
   , GUI_EVENT_SHOW        = 2
   , GUI_EVENT_CLICK       = 3
   , GUI_EVENT_UP          = 4
   , GUI_EVENT_DOWN        = 5
} gui_event_t;

void gui_init();
void gui_handle_event(gui_event_t event);

void gui_show_menu();
void gui_show_menu_item(int item, int position, boolean selected);

void gui_show_menu_page_int(String menuItem, int value);
void gui_show_menu_page_string(String menuItem, String value);

void gui_update_selected_menu(int step);

void gui_reset_default();

/* FIXME: need to remove? */
extern int page;
extern int menuitem;

struct menu_item_t;

struct menu_item_t {
    String name;
    int (*handler)(struct menu_item_t*, gui_event_t event);
    int menu_level;
};

#endif

