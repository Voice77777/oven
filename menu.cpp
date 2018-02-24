#include <menu.h>

/* 
 * идея в том что сейчас у нас будет два массива menu_items
 * старый menu_items, что бы не менять старый код пока
 * и menu_items_ что бы имплементировать новые функции.
 * это позвоить релизовать, для начала, только обработку
 * одного пункта меню, компилировать и проверять как работает
 * и постепенно переносить фунционал из menu_items в menu_items_.
 * */
#if 1
String menu_items[] = {
    "Contrast",
    "Volume",
    "Language",
    "Difficulty",
    "Light: ON",
    "Reset"
};
const int menu_menuitem_number = (sizeof(menu_items)/sizeof(menu_items[0]));
#endif

static int menu_handler_backlight (struct menu_item_t* p, gui_event_t event);
static int menu_handler_contrast  (struct menu_item_t* p, gui_event_t event);
static int menu_handler_volume    (struct menu_item_t* p, gui_event_t event);
static int menu_handler_language  (struct menu_item_t* p, gui_event_t event);
static int menu_handler_difficulty(struct menu_item_t* p, gui_event_t event);


/* это массив из структур. мы сразу же его инифиализируем нужными значениями. NULL обозначает что мы пока еще
 * не сделали обработчик. и по мере имплементации будем его добавлять
 */
struct menu_item_t menu_items_[] = {
    { "Contrast",       menu_handler_contrast},
    { "Volume",         menu_handler_volume},
    { "Language",       menu_handler_language},
    { "Difficulty",     menu_handler_difficulty},
    { "Light: ON",      menu_handler_backlight},
    { "Reset",          NULL},
};
const int menu_menuitem_number_ = (sizeof(menu_items_)/sizeof(menu_items_[0]));


String language[3] = { "EN", "ES", "EL" };
const int menu_language_number = (sizeof(language)/sizeof(language[0]));
int selectedLanguage = 0;

String difficulty[2] = { "EASY", "HARD" };
const int menu_difficulty_number = (sizeof(difficulty)/sizeof(difficulty[0]));
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

int menu_handler_backlight(struct menu_item_t* p, gui_event_t event)
{
    printf ("callback handler backlight event: %d\n", event);
    if (event == GUI_EVENT_CLICK)
        menu_backlight_toggle();
    return 0;
}

int menu_handler_contrast(struct menu_item_t* p, gui_event_t event)
{
    printf ("callback handler contrast event: %d\n", event);
    switch (event) {
        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(menu_items[menuitem], contrast);
            break;
        case GUI_EVENT_UP:
            contrast--;
            display_set_contrast();
            break;
        case GUI_EVENT_DOWN:
            contrast++;
            display_set_contrast();
            break;
        default:
            break;
    }
    return 0;
}

int menu_handler_volume(struct menu_item_t* p, gui_event_t event)
{
    printf ("callback handler volume event: %d\n", event);
    switch (event) {
        case GUI_EVENT_SHOW:
            gui_show_menu_page_int(menu_items[menuitem], volume);
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
    printf ("callback handler language event: %d\n", event);
    switch (event) {
        case GUI_EVENT_SHOW:
            gui_show_menu_page_string(menu_items[menuitem], language[selectedLanguage]);
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
    printf ("callback handler difficulty event: %d\n", event);
    switch (event) {
        case GUI_EVENT_SHOW:
            gui_show_menu_page_string(menu_items[menuitem], difficulty[selectedDifficulty]);
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
    ;
}

void menu_update_up_event(int menuitem)
{
    ;
}

int menu_handle_event(int menu_item, gui_event_t event)
{
    if(menu_items_[menu_item].handler != NULL) {
        return menu_items_[menu_item].handler(&menu_items_[menu_item], event);
    }
    return 0;
}

void menu_update_down_event(int menuitem)
{
    ;
}

void menu_update_click_event(int menuitem)
{
    if (menuitem==5) {
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
