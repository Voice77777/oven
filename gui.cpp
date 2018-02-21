#include <gui.h>

int menuitem = 0;
int page = 1;           /* page == 1: main menu, page == 2: submenu */
int lastMenuItem = 1;

String menu_items[] = {
    "Contrast",
    "Volume",
    "Language",
    "Difficulty",
    "Light: ON",
    "Reset"
};
#define GUI_MENUITEM_NUMBER (sizeof(menu_items)/sizeof(menu_items[0]))

String language[3] = { "EN", "ES", "EL" };
int selectedLanguage = 0;

String difficulty[2] = { "EASY", "HARD" };
int selectedDifficulty = 0;

void gui_init()
{
    display_init();
}

void gui_show_menu()
{
    if (page==1)
    {
        display->setTextSize(1);
        display->clearDisplay();
        display->setTextColor(BLACK, WHITE);
        display->setCursor(15, 0);
        display->print("MAIN MENU");
        display->drawFastHLine(0,10,83,BLACK);

        if (menuitem == 0) {
            gui_show_menu_item(menu_items[menuitem + 0], 15, true);
            gui_show_menu_item(menu_items[menuitem + 1], 25, false);
            gui_show_menu_item(menu_items[menuitem + 2], 35, false);
        } else if (menuitem == GUI_MENUITEM_NUMBER - 1) {
            gui_show_menu_item(menu_items[menuitem - 2], 15, false);
            gui_show_menu_item(menu_items[menuitem - 1], 25, false);
            gui_show_menu_item(menu_items[menuitem - 0], 35, true);
        } else {
            gui_show_menu_item(menu_items[menuitem - 1], 15, false);
            gui_show_menu_item(menu_items[menuitem + 0], 25, true);
            gui_show_menu_item(menu_items[menuitem + 1], 35, false);
        }

        display->display();
    }
    else if (page == 2 && menuitem == 0)
    {
        gui_show_menu_page_int(menu_items[menuitem], contrast);
    }
    else if (page == 2 && menuitem == 1)
    {
        gui_show_menu_page_int(menu_items[menuitem], volume);
    }
    else if (page == 2 && menuitem == 2)
    {
        gui_show_menu_page_string(menu_items[menuitem], language[selectedLanguage]);
    }
    else if (page == 2 && menuitem == 3)
    {
        gui_show_menu_page_string(menu_items[menuitem], difficulty[selectedDifficulty]);
    }

}

void gui_reset_default()
{
    contrast = 60;
    volume = 50;
    selectedLanguage = 0;
    selectedDifficulty = 0;
    display_set_contrast();
    backlight = true;
    menu_items[4] = "Light: ON";
    display_backlight(DISPLAY_BL_ON);
}

void gui_show_menu_item(String item, int position, boolean selected)
{
    if(selected)
        display->setTextColor(WHITE, BLACK);
    else
        display->setTextColor(BLACK, WHITE);

    display->setCursor(0, position);
    display->print(" * " + item);
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
    display->print("Value");
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
    display->print("Value");
    display->setTextSize(2);
    display->setCursor(5, 25);
    display->print(value);
    display->setTextSize(2);
    display->display();
}

void gui_toggle_backlight()
{
    if (backlight)
    {
        backlight = false;
        menu_items[4] = "Light: OFF";       // FIXME: move this to gui.cpp
        display_backlight(DISPLAY_BL_OFF);
    }
    else
    {
        backlight = true;
        menu_items[4] = "Light: ON";        // FIXME: move this to gui.cpp
        display_backlight(DISPLAY_BL_ON);
    }
}

void gui_update_selected_menu(int step)
{
    menuitem += step;

    if (menuitem < 0)
        menuitem = 0;
    if (menuitem > GUI_MENUITEM_NUMBER - 1)
        menuitem = GUI_MENUITEM_NUMBER - 1;
}
