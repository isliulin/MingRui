#include "key.h"
#include "delay.h"
#include<pic16f1939.h>
unsigned char Key_Press(unsigned char cKey)
{
    if(Key_ReadKey(cKey) == 0)
    {
        DelayUs(100);
        if(Key_ReadKey(cKey) == 0)
            return 1;
    }
    return 0;
}

unsigned char Key_Release(unsigned char cKey)
{
    if(Key_ReadKey(cKey) == 0)
    {
        DelayUs(100);
        if(Key_ReadKey(cKey) == 0)
        {
            while(Key_ReadKey(cKey) == 0){;}
            return 1;
        }
    }
    return 0;
}

unsigned char Key_ReadKey(unsigned char cKey)
{
    unsigned char keyPressed;
    switch(cKey)
    {
        case KEY_START:
            keyPressed = KEY_START_PIN;
            break;
        case KEY_STOP:
            keyPressed = KEY_STOP_PIN;
            break;
        case KEY_RESET:
            keyPressed = KEY_RESET_PIN;
            break;
        case KEY_DOWN:
            keyPressed = KEY_DOWN_PIN;
            break;
        case KEY_UP:
            keyPressed = KEY_UP_PIN;
            break;
        case KEY_MOVE:
            keyPressed = KEY_MOVE_PIN;
            break;
        case KEY_OK:
            keyPressed = KEY_OK_PIN;
            break;
        default:
            keyPressed = 1;
            break;
    }
    return keyPressed;
    
}