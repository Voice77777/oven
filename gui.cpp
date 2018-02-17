#include <gui.h>

int menuitem = 1;
int frame = 1;
int page = 1;
int lastMenuItem = 1;

String menuItem1 = "Contrast";
String menuItem2 = "Volume";
String menuItem3 = "Language";
String menuItem4 = "Difficulty";
String menuItem5 = "Light: ON";
String menuItem6 = "Reset";

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

        if(menuitem==1 && frame ==1)
        {
            gui_show_menu_item(menuItem1, 15,true);
            gui_show_menu_item(menuItem2, 25,false);
            gui_show_menu_item(menuItem3, 35,false);
        }
        else if(menuitem == 2 && frame == 1)
        {
            gui_show_menu_item(menuItem1, 15,false);
            gui_show_menu_item(menuItem2, 25,true);
            gui_show_menu_item(menuItem3, 35,false);
        }
        else if(menuitem == 3 && frame == 1)
        {
            gui_show_menu_item(menuItem1, 15,false);
            gui_show_menu_item(menuItem2, 25,false);
            gui_show_menu_item(menuItem3, 35,true);
        }
        else if(menuitem == 4 && frame == 2)
        {
            gui_show_menu_item(menuItem2, 15,false);
            gui_show_menu_item(menuItem3, 25,false);
            gui_show_menu_item(menuItem4, 35,true);
        }

        else if(menuitem == 3 && frame == 2)
        {
            gui_show_menu_item(menuItem2, 15,false);
            gui_show_menu_item(menuItem3, 25,true);
            gui_show_menu_item(menuItem4, 35,false);
        }
        else if(menuitem == 2 && frame == 2)
        {
            gui_show_menu_item(menuItem2, 15,true);
            gui_show_menu_item(menuItem3, 25,false);
            gui_show_menu_item(menuItem4, 35,false);
        }

        else if(menuitem == 5 && frame == 3)
        {
            gui_show_menu_item(menuItem3, 15,false);
            gui_show_menu_item(menuItem4, 25,false);
            gui_show_menu_item(menuItem5, 35,true);
        }

        else if(menuitem == 6 && frame == 4)
        {
            gui_show_menu_item(menuItem4, 15,false);
            gui_show_menu_item(menuItem5, 25,false);
            gui_show_menu_item(menuItem6, 35,true);
        }

        else if(menuitem == 5 && frame == 4)
        {
            gui_show_menu_item(menuItem4, 15,false);
            gui_show_menu_item(menuItem5, 25,true);
            gui_show_menu_item(menuItem6, 35,false);
        }
        else if(menuitem == 4 && frame == 4)
        {
            gui_show_menu_item(menuItem4, 15,true);
            gui_show_menu_item(menuItem5, 25,false);
            gui_show_menu_item(menuItem6, 35,false);
        }
        else if(menuitem == 3 && frame == 3)
        {
            gui_show_menu_item(menuItem3, 15,true);
            gui_show_menu_item(menuItem4, 25,false);
            gui_show_menu_item(menuItem5, 35,false);
        }
        else if(menuitem == 2 && frame == 2)
        {
            gui_show_menu_item(menuItem2, 15,true);
            gui_show_menu_item(menuItem3, 25,false);
            gui_show_menu_item(menuItem4, 35,false);
        }
        else if(menuitem == 4 && frame == 3)
        {
            gui_show_menu_item(menuItem3, 15,false);
            gui_show_menu_item(menuItem4, 25,true);
            gui_show_menu_item(menuItem5, 35,false);
        }
        display->display();
    }
    else if (page==2 && menuitem == 1)
    {
        gui_show_menu_page_int(menuItem1, contrast);
    }

    else if (page==2 && menuitem == 2)
    {
        gui_show_menu_page_int(menuItem2, volume);
    }
    else if (page==2 && menuitem == 3)
    {
        gui_show_menu_page_string(menuItem3, language[selectedLanguage]);
    }
    else if (page==2 && menuitem == 4)
    {
        gui_show_menu_page_string(menuItem4, difficulty[selectedDifficulty]);
    }
    else if (page==2 && menuitem == 4)
    {
        gui_show_menu_page_string(menuItem4, difficulty[selectedDifficulty]);
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
    menuItem5 = "Light: ON";
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

