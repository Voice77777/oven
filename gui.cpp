#include <gui.h>
#include <menu.h>

int menuitem = 0;
int page = 1;           /* page == 1: main menu, page == 2: submenu */

void gui_init()
{
    display_init();
    menu_init();
}

void gui_handle_event(gui_event_t event)
{
    switch(event) {
        case GUI_EVENT_INIT:
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu();
            break;

        case GUI_EVENT_UP:
            if (page == 1) {
                gui_update_selected_menu(-1);
            } else if (page == 2) {
                menu_handle_event(menuitem, GUI_EVENT_UP);
            }
            break;

        case GUI_EVENT_DOWN:
            if (page == 1) {
                gui_update_selected_menu(1);
            } else if (page == 2) {
                menu_handle_event(menuitem, GUI_EVENT_DOWN);
            }
            break;

        case GUI_EVENT_CLICK:
            if (page == 1) {
                page = menu_get_item_menu_level(menuitem);
                menu_handle_event(menuitem, GUI_EVENT_CLICK);
            } else if (page == 2) {
                page = 1;
            }
            break;
    }
}

void gui_show_menu()
{
    if (page == 1)
    {
        display->setTextSize(1);
        display->clearDisplay();
        display->setTextColor(BLACK, WHITE);
        display->setCursor(15, 0);
        display->print("МЕНЮ");
        display->drawFastHLine(0,10,83,BLACK);

        if (menuitem == 0) {
            gui_show_menu_item(menuitem + 0, 15, true);
            gui_show_menu_item(menuitem + 1, 25, false);
            gui_show_menu_item(menuitem + 2, 35, false);
        } else if (menuitem == menu_menuitem_number - 1) {
            gui_show_menu_item(menuitem - 2, 15, false);
            gui_show_menu_item(menuitem - 1, 25, false);
            gui_show_menu_item(menuitem - 0, 35, true);
        } else {
            gui_show_menu_item(menuitem - 1, 15, false);
            gui_show_menu_item(menuitem + 0, 25, true);
            gui_show_menu_item(menuitem + 1, 35, false);
        }

        display->display();
    }
    else if (page == 2) {
        menu_handle_event(menuitem, GUI_EVENT_SHOW);
    }

}

void gui_show_menu_item(int item, int position, boolean selected)
{
    if(selected)
        display->setTextColor(WHITE, BLACK);
    else
        display->setTextColor(BLACK, WHITE);

    display->setCursor(0, position);
    display->print(" * " + menu_get_item_string(item));
}

void gui_show_menu_page_int(String menuItem, int value)
{
    display->setTextSize(1);
    display->clearDisplay();
    display->setTextColor(BLACK, WHITE);
    display->setCursor(15, 0);
    display->print(menuItem);
    display->drawFastHLine(0,10,83,BLACK);
    display->setCursor(5, 15);
    display->print("Значение");
    display->setTextSize(2);
    display->setCursor(5, 25);
    display->print(value);
    display->setTextSize(2);
    display->display();
}

void gui_show_menu_page_string(String menuItem, String value)
{
    display->setTextSize(1);
    display->clearDisplay();
    display->setTextColor(BLACK, WHITE);
    display->setCursor(15, 0);
    display->print(menuItem);
    display->drawFastHLine(0,10,83,BLACK);
    display->setCursor(5, 15);
    display->print("Значение");
    display->setTextSize(2);
    display->setCursor(5, 25);
    display->print(value);
    display->setTextSize(2);
    display->display();
}

void gui_update_selected_menu(int step)
{
    menuitem += step;

    if (menuitem < 0)
        menuitem = 0;
    if (menuitem > menu_menuitem_number - 1)
        menuitem = menu_menuitem_number - 1;
}
