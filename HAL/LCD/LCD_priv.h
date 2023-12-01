/*
 * LCD_priv.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

#define EIGHT_BIT	55
#define FOUR_BIT	56

static inline void LCD_inVoidSendCommand(u8 Copy_u8Command);

static void LCD_VoidLatch(u8 Copy_u8Data);

#endif /* LCD_PRIV_H_ */
