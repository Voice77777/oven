#include <fsm.h>
#include <gui.h>
#include <encoder.h>

void fsm_init()
{
    encoder_init();
}

int fsm_get_event()
{
    encoder_read();

    ClickEncoder::Button b = encoder->getButton();
    if (b != ClickEncoder::Open) {
        switch (b) {
            case ClickEncoder::Clicked:
                middle = true;
                break;
        }
    }
}

int fsm_step()
{
    fsm_get_event();

    if (up && page == 1 ) {
        up = false;
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
    } else if (up && page == 2 && menuitem==1) {
        up = false;
        contrast--;
        display_set_contrast();
    }
    else if (up && page == 2 && menuitem==2 ) {
        up = false;
        volume--;
    }
    else if (up && page == 2 && menuitem==3 ) {
        up = false;
        selectedLanguage--;
        if(selectedLanguage == -1)
        {
            selectedLanguage = 2;
        }
    }
    else if (up && page == 2 && menuitem==4 ) {
        up = false;
        selectedDifficulty--;
        if(selectedDifficulty == -1)
        {
            selectedDifficulty = 1;
        }
    }

    if (down && page == 1) //We have turned the Rotary Encoder Clockwise
    {

        down = false;
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

    }else if (down && page == 2 && menuitem==1) {
        down = false;
        contrast++;
        display_set_contrast();
    }
    else if (down && page == 2 && menuitem==2) {
        down = false;
        volume++;
    }
    else if (down && page == 2 && menuitem==3 ) {
        down = false;
        selectedLanguage++;
        if(selectedLanguage == 3)
        {
            selectedLanguage = 0;
        }
    }
    else if (down && page == 2 && menuitem==4 ) {
        down = false;
        selectedDifficulty++;
        if(selectedDifficulty == 2)
        {
            selectedDifficulty = 0;
        }
    }

    if (middle) //Middle Button is Pressed
    {
        middle = false;

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
}
