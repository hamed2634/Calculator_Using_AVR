/*
 * Keypad_config.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */

#include "..\..\.\Lib\errorStates.h"
#include "..\..\.\Lib\stdTypes.h"

#include "..\..\.\MCAL\DIO\DIO_int.h"

#include "Keypad_config.h"
#include "Keypad_priv.h"

u8 Keypad_Au8Chars[] = {
		'A','7','8','9','*','/',
		'C','4','5','6','-','^',
		'<','1','2','3','+',')',
		'>','0','.','=','+','('
};

Line Keypad_AstrRows[ROWS_NUM] = {
		{DIO_u8PORTA, DIO_u8PIN0},
		{DIO_u8PORTA, DIO_u8PIN1},
		{DIO_u8PORTA, DIO_u8PIN2},
		{DIO_u8PORTA, DIO_u8PIN3}
};

Line Keypad_AstrCols[COLS_NUM] = {
		{DIO_u8PORTA, DIO_u8PIN4},
		{DIO_u8PORTA, DIO_u8PIN5},
		{DIO_u8PORTA, DIO_u8PIN6},
		{DIO_u8PORTA, DIO_u8PIN7},
		{DIO_u8PORTB, DIO_u8PIN0},
		{DIO_u8PORTB, DIO_u8PIN1}
};
