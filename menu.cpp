#include <gui.h>
#include <menu.h>

String menu_items[] = {
    "Contrast",
    "Volume",
    "Language",
    "Difficulty",
    "Light: ON",
    "Reset"
};
const int menu_menuitem_number = (sizeof(menu_items)/sizeof(menu_items[0]));

String language[3] = { "EN", "ES", "EL" };
int selectedLanguage = 0;

String difficulty[2] = { "EASY", "HARD" };
int selectedDifficulty = 0;

void menu_reset_default()
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

void menu_backlight_toggle()
{
    if (backlight)
    {
        backlight = false;
        menu_items[4] = "Light: OFF";
        display_backlight(DISPLAY_BL_OFF);
    }
    else
    {
        backlight = true;
        menu_items[4] = "Light: ON";
        display_backlight(DISPLAY_BL_ON);
    }
}

void menu_show_submenu(int menuitem)
{
    switch (menuitem) {
        case 0: gui_show_menu_page_int(menu_items[menuitem], contrast);                          break;
        case 1: gui_show_menu_page_int(menu_items[menuitem], volume);                            break;
        case 2: gui_show_menu_page_string(menu_items[menuitem], language[selectedLanguage]);     break;
        case 3: gui_show_menu_page_string(menu_items[menuitem], difficulty[selectedDifficulty]); break;
    }
}

void menu_update_up_event(int menuitem)
{
    if (menuitem==0) {
        contrast--;
        display_set_contrast();
    }
    else if (menuitem==1 ) {
        volume--;
    }
    else if (menuitem==2 ) {
        selectedLanguage--;
        if(selectedLanguage == -1)
        {
            selectedLanguage = 2;
        }
    }
    else if (menuitem==3 ) {
        selectedDifficulty--;
        if(selectedDifficulty == -1)
        {
            selectedDifficulty = 1;
        }
    }
}

void menu_update_down_event(int menuitem)
{
    if (menuitem==0) {
        contrast++;
        display_set_contrast();
    }
    else if (menuitem==1) {
        volume++;
    }
    else if (menuitem==2) {
        selectedLanguage++;
        if(selectedLanguage == 3)
        {
            selectedLanguage = 0;
        }
    }
    else if (menuitem==3) {
        selectedDifficulty++;
        if(selectedDifficulty == 2)
        {
            selectedDifficulty = 0;
        }
    }
}

void menu_update_click_event(int menuitem)
{
    if (menuitem==4) {
        menu_backlight_toggle();
    }
    else if (menuitem==5) {
        menu_reset_default();
    }
    else if (menuitem<=3) {
        page = 2;
    }
}

String menu_get_item_string(int menuitem)
{
    return menu_items[menuitem];
}
