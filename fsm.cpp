#include <fsm.h>
#include <gui.h>
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

    if (event == E_UP && page == 1 ) {
        if(menuitem==2 && frame ==2)
        {
            frame--;
        }

        if(menuitem==4 && frame ==4)
        {
            frame--;
        }
        if(menuitem==3 && frame ==3)
        {
            frame--;
        }
        lastMenuItem = menuitem;
        menuitem--;
        if (menuitem==0)
        {
            menuitem=1;
        }
    } else if (event == E_UP && page == 2 && menuitem==1) {
        contrast--;
        display_set_contrast();
    }
    else if (event == E_UP && page == 2 && menuitem==2 ) {
        volume--;
    }
    else if (event == E_UP && page == 2 && menuitem==3 ) {
        selectedLanguage--;
        if(selectedLanguage == -1)
        {
            selectedLanguage = 2;
        }
    }
    else if (event == E_UP && page == 2 && menuitem==4 ) {
        selectedDifficulty--;
        if(selectedDifficulty == -1)
        {
            selectedDifficulty = 1;
        }
    }

    if (event == E_DOWN && page == 1) //We have turned the Rotary Encoder Clockwise
    {
        if(menuitem==3 && lastMenuItem == 2)
        {
            frame ++;
        }else  if(menuitem==4 && lastMenuItem == 3)
        {
            frame ++;
        }
        else  if(menuitem==5 && lastMenuItem == 4 && frame!=4)
        {
            frame ++;
        }
        lastMenuItem = menuitem;
        menuitem++;
        if (menuitem==7)
        {
            menuitem--;
        }

    }else if (event == E_DOWN && page == 2 && menuitem==1) {
        contrast++;
        display_set_contrast();
    }
    else if (event == E_DOWN && page == 2 && menuitem==2) {
        volume++;
    }
    else if (event == E_DOWN && page == 2 && menuitem==3 ) {
        selectedLanguage++;
        if(selectedLanguage == 3)
        {
            selectedLanguage = 0;
        }
    }
    else if (event == E_DOWN && page == 2 && menuitem==4 ) {
        selectedDifficulty++;
        if(selectedDifficulty == 2)
        {
            selectedDifficulty = 0;
        }
    }

    if (event == E_CLICK) //Middle Button is Pressed
    {
        if (page == 1 && menuitem==5) // Backlight Control
        {
            if (backlight)
            {
                backlight = false;
                menuItem5 = "Light: OFF";
                display_backlight(DISPLAY_BL_OFF);
            }
            else
            {
                backlight = true;
                menuItem5 = "Light: ON";
                display_backlight(DISPLAY_BL_ON);
            }
        }

        if(page == 1 && menuitem ==6)// Reset
        {
            gui_reset_default();
        }
        else if (page == 1 && menuitem<=4) {
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
