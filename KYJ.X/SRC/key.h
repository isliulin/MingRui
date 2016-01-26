/* 
 * File:   key.h
 * Author: tlan
 *
 * Created on 2015年12月31日, 上午9:13
 */

#ifndef KEY_H
#define	KEY_H

#ifdef	__cplusplus
extern "C" {
#endif

#define KEY_START_PIN RD4
#define KEY_STOP_PIN RD5
#define KEY_RESET_PIN RD6
#define KEY_DOWN_PIN RB3
#define KEY_UP_PIN RB1
#define KEY_MOVE_PIN RD7
#define KEY_OK_PIN RB2

#define KEY_START 1
#define KEY_STOP 2
#define KEY_RESET 3
#define KEY_DOWN 4
#define KEY_UP 5
#define KEY_MOVE 6
#define KEY_OK 7
    
unsigned char Key_Press(unsigned char cKey);
unsigned char Key_Release(unsigned char cKey);
unsigned char Key_ReadKey(unsigned char cKey);

#ifdef	__cplusplus
}
#endif

#endif	/* KEY_H */

