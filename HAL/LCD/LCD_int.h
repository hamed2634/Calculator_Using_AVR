/*
 * LCD_int.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

ES LCD_enuInit(void);

ES LCD_enuDisplayChar(u8 Copy_u8Data);

ES LCD_enuSendCommand(u8 Copy_u8Command);

ES LCD_enuClearDisplay();

ES LCD_enuGoto(u8 Copy_u8Line,u8 Copy_u8Block);

#endif /* LCD_INT_H_ */
