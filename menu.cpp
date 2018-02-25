#include <menu.h>

static int menu_handler_backlight (struct menu_item_t* p, gui_event_t event);
static int menu_handler_contrast  (struct menu_item_t* p, gui_event_t event);
static int menu_handler_volume    (struct menu_item_t* p, gui_event_t event);
static int menu_handler_language  (struct menu_item_t* p, gui_event_t event);
static int menu_handler_difficulty(struct menu_item_t* p, gui_event_t event);
static int menu_handler_reset     (struct menu_item_t* p, gui_event_t event);
static int menu_handler_ctrl_servo(struct menu_item_t* p, gui_event_t event);

struct menu_item_t menu_items[] = {
    { "Contrast",       menu_handler_contrast,   2},
    { "Volume",         menu_handler_volume,     2},
    { "Language",       menu_handler_language,   2},
    { "Difficulty",     menu_handler_difficulty, 2},
    { "Light: ON",      menu_handler_backlight,  1},
    { "Ctrl Servo",     menu_handler_ctrl_servo, 2},
    { "Reset",          menu_handler_reset,      1},
};
const int menu_menuitem_number = (sizeof(menu_items)/sizeof(menu_items[0]));

void menu_reset_default()
{
    int i;
    for (i = 0; i < menu_menuitem_number; i++)
        menu_handle_event(i, GUI_EVENT_INIT);
}

int menu_handler_backlight(struct menu_item_t* p, gui_event_t event)
{
    static boolean backlight = true;

    switch (event) {
        case GUI_EVENT_INIT:
            backlight = true;
            p->name = "Light: ON";
            display_backlight(DISPLAY_BL_ON);
            break;

        case GUI_EVENT_CLICK:
            if (backlight)
            {
                backlight = false;
                p->name = "Light: OFF";
                display_backlight(DISPLAY_BL_OFF);
            }
            else
            {
                backlight = true;
                p->name = "Light: ON";
                display_backlight(DISPLAY_BL_ON);
            }
            break;

        default:
            break;
    }
    return 0;
}

int menu_handler_contrast(struct menu_item_t* p, gui_event_t event)
{
    static int contrast = 60;

    switch (event) {
        case GUI_EVENT_INIT:
            contrast = 60;
            display_set_contrast(contrast);
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(p->name, contrast);
            break;

        case GUI_EVENT_UP:
            contrast--;
            display_set_contrast(contrast);
            break;

        case GUI_EVENT_DOWN:
            contrast++;
            display_set_contrast(contrast);
            break;

        default:
            break;
    }
    return 0;
}

int menu_handler_volume(struct menu_item_t* p, gui_event_t event)
{
    static int volume        = 50;
    switch (event) {
        case GUI_EVENT_INIT:
            volume = 50;
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(p->name, volume);
            break;

        case GUI_EVENT_UP:
            volume--;
            break;

        case GUI_EVENT_DOWN:
            volume++;
            break;

        default:
            break;
    }
    return 0;
}

int menu_handler_language(struct menu_item_t* p, gui_event_t event)
{
    String language[3] = {"EN", "ES", "EL"};
    const int menu_language_number = (sizeof(language)/sizeof(language[0]));
    static int selectedLanguage = 0;

    switch (event) {
        case GUI_EVENT_INIT:
            selectedLanguage = 0;
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu_page_string(p->name, language[selectedLanguage]);
            break;

        case GUI_EVENT_UP:
            selectedLanguage--;
            if(selectedLanguage == -1)
                selectedLanguage = menu_language_number - 1;
            break;

        case GUI_EVENT_DOWN:
            selectedLanguage++;
            if(selectedLanguage == menu_language_number)
                selectedLanguage = 0;
            break;

        default:
            break;
    }

    return 0;
}

int menu_handler_difficulty(struct menu_item_t* p, gui_event_t event)
{
    String difficulty[2] = { "EASY", "HARD" };
    const int menu_difficulty_number = (sizeof(difficulty)/sizeof(difficulty[0]));
    static int selectedDifficulty = 0;

    switch (event) {
        case GUI_EVENT_INIT:
            selectedDifficulty = 0;
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu_page_string(p->name, difficulty[selectedDifficulty]);
            break;

        case GUI_EVENT_UP:
            selectedDifficulty--;
            if(selectedDifficulty == -1)
                selectedDifficulty = menu_difficulty_number - 1;
            break;

        case GUI_EVENT_DOWN:
            selectedDifficulty++;
            if(selectedDifficulty == menu_difficulty_number)
                selectedDifficulty = 0;
            break;

        default:
            break;
    }

    return 0;
}

static int menu_handler_ctrl_servo(struct menu_item_t* p, gui_event_t event)
{
    static int servo_speed = 0;

    switch (event) {
        case GUI_EVENT_INIT:
            servo_speed = 0;
            break;
        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(p->name, servo_speed);
            break;
        case GUI_EVENT_UP:
            servo_speed++;
            //servo_set_speed(servo_speed);
            break;
        case GUI_EVENT_DOWN:
            servo_speed--;
            //servo_set_speed(servo_speed);
            break;
        default:
            break;
    }
    return 0;
}

int menu_handler_reset(struct menu_item_t* p, gui_event_t event)
{
    if (event == GUI_EVENT_CLICK)
        menu_reset_default();
    return 0;
}

/****** helpers ********/
int menu_handle_event(int menu_item, gui_event_t event)
{
    if (menu_items[menu_item].handler != NULL) {
        return menu_items[menu_item].handler(&menu_items[menu_item], event);
    }
    return 0;
}

String menu_get_item_string(int menuitem)
{
    return menu_items[menuitem].name;
}

int menu_get_item_menu_level(int menuitem)
{
    return menu_items[menuitem].menu_level;
}
