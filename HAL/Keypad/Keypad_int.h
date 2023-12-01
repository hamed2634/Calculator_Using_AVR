/*
 * Keypad_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */

#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_

#define KEYPAD_STATE_NO_PRESSED 255

ES Keypad_enuInit(void);
ES Keypad_enuGetPressedButton(u8* copy_pu8KeypadState);

#endif /* KEYPAD_INT_H_ */
