#include <fsm.h>
#include <gui.h>
#include <menu.h>
#include <encoder.h>

typedef enum {
     E_NONE        = 1
   , E_INIT        = 2
   , E_FAIL        = 3
   , E_CLICK       = 4
   , E_UP          = 5
   , E_DOWN        = 6
} event_t;

static int16_t encode_pos;

void fsm_init()
{
    encoder_init();
    encode_pos = encoder->getValue();
}

event_t encoder_event()
{
    static int16_t value = 0;
    event_t e = E_NONE;

    if (encoder->getButton() == ClickEncoder::Clicked)
        e = E_CLICK;
    else {
        value += encoder->getValue();

        if (value/2 > encode_pos) {
            encode_pos = value/2;
            e = E_DOWN;
        } else if (value/2 < encode_pos) {
            encode_pos = value/2;
            e = E_UP;
        }
    }

    return e;
}

event_t fsm_get_event()
{
    event_t e = E_NONE;

    if ((e = encoder_event()) != E_NONE)
        return e;

    return e;
}

int fsm_step()
{
    event_t event = E_NONE;

    event = fsm_get_event();

    if (event == E_NONE)
        return 0;

    if (event == E_UP) {
        if (page == 1) {
            gui_update_selected_menu(-1);
        } else if (page == 2) {
            menu_update_up_event(menuitem);
        }
    }

    if (event == E_DOWN) {
       if (page == 1) {
           gui_update_selected_menu(1);
       } else if (page == 2) {
           menu_update_down_event(menuitem);
       }
    }

    if (event == E_CLICK) //Middle Button is Pressed
    {
        if (page == 1 && menuitem==4) // Backlight Control
        {
            menu_backlight_toggle();
        }

        if(page == 1 && menuitem ==5)// Reset
        {
            menu_reset_default();
        }
        else if (page == 1 && menuitem<=3) {
            page=2;
        }
        else if (page == 2)
        {
            page=1;
        }
    }

    gui_show_menu();

    return 0;
}
