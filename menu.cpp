#include <menu.h>
#include <servo.h>

static int menu_handler_backlight (struct menu_item_t* p, gui_event_t event);
static int menu_handler_contrast  (struct menu_item_t* p, gui_event_t event);
static int menu_handler_volume    (struct menu_item_t* p, gui_event_t event);
static int menu_handler_language  (struct menu_item_t* p, gui_event_t event);
static int menu_handler_difficulty(struct menu_item_t* p, gui_event_t event);
static int menu_handler_reset     (struct menu_item_t* p, gui_event_t event);
static int menu_handler_ctrl_servo(struct menu_item_t* p, gui_event_t event);

struct menu_item_t menu_items[] = {
    { "Контраст",       menu_handler_contrast,   2},
    { "Громкость",      menu_handler_volume,     2},
    { "Язык",           menu_handler_language,   2},
    { "Сложность",      menu_handler_difficulty, 2},
    { "Свет: Вкл",      menu_handler_backlight,  1},
    { "Сервопривод",    menu_handler_ctrl_servo, 2},
    { "Сброс",          menu_handler_reset,      1},
};
const int menu_menuitem_number = (sizeof(menu_items)/sizeof(menu_items[0]));

void menu_init()
{
    menu_set_defaults();
}

void menu_set_defaults()
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
            p->name = "Свет: Вкл";
            display_backlight(DISPLAY_BL_ON);
            break;

        case GUI_EVENT_CLICK:
            if (backlight)
            {
                backlight = false;
                p->name = "Свет: Выкл";
                display_backlight(DISPLAY_BL_OFF);
            }
            else
            {
                backlight = true;
                p->name = "Свет: Вкл";
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
    static int contrast = 50;

    switch (event) {
        case GUI_EVENT_INIT:
            contrast = 50;
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
    static int volume = 50;

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
    static int pos = 0;
    static bool initialized = 0;

    switch (event) {
        case GUI_EVENT_INIT:
            pos = 0;
            if (!initialized) {
                initialized = 1;
                servo_init();
            }
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(p->name, pos);
            break;

        case GUI_EVENT_UP:
            pos += 10;
            if (pos >= 180)
                pos = 180;
            servo_set_pos(pos);
            break;

        case GUI_EVENT_DOWN:
            pos -= 10;
            if (pos < 0)
                pos = 0;
            servo_set_pos(pos);
            break;

        default:
            break;
    }
    return 0;
}

int menu_handler_reset(struct menu_item_t* p, gui_event_t event)
{
    if (event == GUI_EVENT_CLICK)
        menu_set_defaults();
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
