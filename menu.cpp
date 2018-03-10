#include <menu.h>
#include <servo.h>

#define POW_MIN 0
#define POW_MAX 10
#define POS_MIN 0
#define POS_MAX 180
#define POS_STEP 10
#define TEMPER_MIN 40
#define TEMPER_MAX 400

static int menu_handler_backlight (struct menu_item_t* p, gui_event_t event);
static int menu_handler_contrast  (struct menu_item_t* p, gui_event_t event);
static int menu_handler_power     (struct menu_item_t* p, gui_event_t event);
static int menu_handler_language  (struct menu_item_t* p, gui_event_t event);
static int menu_handler_temperatur(struct menu_item_t* p, gui_event_t event);
static int menu_handler_reset     (struct menu_item_t* p, gui_event_t event);
static int menu_handler_ctrl_servo(struct menu_item_t* p, gui_event_t event);

struct menu_item_t menu_items[] = {
    { "Контраст",       menu_handler_contrast,   2},
    { "Потужнысть",     menu_handler_power,      2},
    { "Температура",    menu_handler_temperatur, 2},
    { "Мова",           menu_handler_language,   2},
    { "Свытло: Вм",     menu_handler_backlight,  1},
    { "Сервопривод",    menu_handler_ctrl_servo, 2},
    { "Скидання",       menu_handler_reset,      1},
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
            p->name = "Свытло: Вм";
            display_backlight(DISPLAY_BL_ON);
            break;

        case GUI_EVENT_CLICK:
            if (backlight)
            {
                backlight = false;
                p->name = "Свытло: Вым";
                display_backlight(DISPLAY_BL_OFF);
            }
            else
            {
                backlight = true;
                p->name = "Свытло: Вм";
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

int menu_handler_power(struct menu_item_t* p, gui_event_t event)
{
    static int power = POS_MIN;

    switch (event) {
        case GUI_EVENT_INIT:
            power = POW_MIN;
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(p->name, power);
            break;

        case GUI_EVENT_UP:
            power--;
            if (power < POW_MIN)
                power = POW_MIN;
            break;

        case GUI_EVENT_DOWN:
            power++;
            if (power > POW_MAX)
                power = POW_MAX;
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

int menu_handler_temperatur(struct menu_item_t* p, gui_event_t event)
{
    static int temperatur = TEMPER_MIN;

    switch (event) {
        case GUI_EVENT_INIT:
            temperatur = TEMPER_MIN;
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(p->name, temperatur);
            break;

        case GUI_EVENT_UP:
            temperatur--;
            if (temperatur < TEMPER_MIN)
                temperatur = TEMPER_MIN;
            break;

        case GUI_EVENT_DOWN:
            temperatur++;
            if (temperatur > TEMPER_MAX)
                temperatur = TEMPER_MAX;
            break;

        default:
            break;
    }
    return 0;
}

static int menu_handler_ctrl_servo(struct menu_item_t* p, gui_event_t event)
{
    static int pos = POS_MIN;
    static bool initialized = 0;

    switch (event) {
        case GUI_EVENT_INIT:
            pos = POS_MIN;
            if (!initialized) {
                initialized = 1;
                servo_init();
            }
            break;

        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(p->name, pos);
            break;

        case GUI_EVENT_UP:
            pos -= POS_STEP;
            if (pos < POS_MIN)
                pos = POS_MIN;
            servo_set_pos(pos);
            break;

        case GUI_EVENT_DOWN:
            pos += POS_STEP;
            if (pos >= POS_MAX)
                pos = POS_MAX;
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
