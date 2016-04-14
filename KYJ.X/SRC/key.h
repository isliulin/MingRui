/* 
 * File:   key.h
 * Author: tlan
 *
 * Created on 2015年12月31日, 上午9:13
 */

#ifndef KEY_H
#define	KEY_H
#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define KEY_START_PIN PORTDbits.RD4
#define KEY_STOP_PIN PORTDbits.RD5
#define KEY_RESET_PIN PORTDbits.RD6
#define KEY_DOWN_PIN PORTBbits.RB5
#define KEY_UP_PIN PORTBbits.RB1
#define KEY_MOVE_PIN PORTDbits.RD7
#define KEY_OK_PIN PORTBbits.RB2

#define KEY_START 1
#define KEY_STOP 2
#define KEY_RESET 3
#define KEY_DOWN 4
#define KEY_UP 5
#define KEY_MOVE 6
#define KEY_OK 7
    
bit Key_Press(unsigned char cKey);
bit Key_Release(unsigned char cKey);
bit Key_ReadKey(unsigned char cKey);

#ifdef	__cplusplus
}
#endif

#endif	/* KEY_H */

