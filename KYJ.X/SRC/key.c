#include "key.h"
#include "delay.h"
bit Key_Press(unsigned char cKey)
{
    if(Key_ReadKey(cKey) == 0)
    {
        DelayUs(100);
        if(Key_ReadKey(cKey) == 0)
            return 1;
    }
    return 0;
}

bit Key_Release(unsigned char cKey)
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

bit Key_ReadKey(unsigned char cKey)
{
    switch(cKey)
    {
        case KEY_START:
            return KEY_START_PIN;
        case KEY_STOP:
            return KEY_STOP_PIN;
        case KEY_RESET:
            return KEY_RESET_PIN;
        case KEY_DOWN:
            return KEY_DOWN_PIN;
        case KEY_UP:
            return KEY_UP_PIN;
        case KEY_MOVE:
            return KEY_MOVE_PIN;
        case KEY_OK:
            return KEY_OK_PIN;
        case KEY_EMERGY_STOP:
            return KEY_EMERGY_STOP_PIN;
        default:
            return 1;
    }
}