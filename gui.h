#ifndef GUI_H
#define GUI_H

#include <display.h>

void gui_init();

void gui_show_menu();
void gui_show_menu_item(int item, int position, boolean selected);

void gui_show_menu_page_int(String menuItem, int value);
void gui_show_menu_page_string(String menuItem, String value);

void gui_update_selected_menu(int step);

void gui_toggle_backlight();

void gui_reset_default();

/* FIXME: need to remove? */
extern int page;
extern int menuitem;

struct menu_item_t;

#if 0
нам нужно создать GUI события. они отличаются от событий fsm. тут будет пока только три события
#endif
typedef enum {
     GUI_EVENT_SHOW        = 1
   , GUI_EVENT_CLICK       = 2
   , GUI_EVENT_UP          = 3
   , GUI_EVENT_DOWN        = 4
} gui_event_t;

#if 0
это структура описывающая пункт меню. тут пока есть только имя
и ссылка на обработчик события
когда пользователь что либо будет делать с пунктом меню (например заходить в него, нажимать в нём up/down,
будет вызываться фунция которую мы укажем.
#endif
struct menu_item_t {
    String name;
    int (*handler)(struct menu_item_t*, gui_event_t event);
};

#endif

