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

        if (value / 3 > encode_pos) {
            encode_pos = value / 3;
            e = E_DOWN;
        } else if (value / 3 < encode_pos) {
            encode_pos = value / 3;
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
        gui_handle_event(GUI_EVENT_UP);
    }

    if (event == E_DOWN) {
        gui_handle_event(GUI_EVENT_DOWN);
    }

    if (event == E_CLICK) {
        gui_handle_event(GUI_EVENT_CLICK);
    }

    gui_handle_event(GUI_EVENT_SHOW);

    return 0;
}
