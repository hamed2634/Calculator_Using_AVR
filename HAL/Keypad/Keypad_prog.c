/*
 * Keypad_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */
#include "..\..\.\Lib\errorStates.h"
#include "..\..\.\Lib\stdTypes.h"

#include "..\..\.\MCAL\DIO\DIO_int.h"

#include "Keypad_config.h"
#include "Keypad_priv.h"

#include "util/delay.h"

extern Line Keypad_AstrRows[ROWS_NUM];
extern Line Keypad_AstrCols[COLS_NUM];
extern u8 Keypad_Au8Chars[];

ES Keypad_enuInit(void){
	ES Local_u8ErrorState = ES_NOK;

	//Set Rows As Input Pulled Up
	for(u8 Local_u8RowsIt = 0; Local_u8RowsIt < ROWS_NUM; Local_u8RowsIt++){
		DIO_enuSetPinDirection(Keypad_AstrRows[Local_u8RowsIt].u8_LinePortID, Keypad_AstrRows[Local_u8RowsIt].u8_LinePinID, DIO_u8INPUT);
		DIO_enuSetPinValue(Keypad_AstrRows[Local_u8RowsIt].u8_LinePortID, Keypad_AstrRows[Local_u8RowsIt].u8_LinePinID, DIO_u8HIGH);
	}

	//Set Cols As Output and High
	for(u8 Local_u8ColsIt = 0; Local_u8ColsIt < COLS_NUM; Local_u8ColsIt++){
		DIO_enuSetPinDirection(Keypad_AstrCols[Local_u8ColsIt].u8_LinePortID, Keypad_AstrCols[Local_u8ColsIt].u8_LinePinID, DIO_u8OUTPUT);
		DIO_enuSetPinValue(Keypad_AstrCols[Local_u8ColsIt].u8_LinePortID, Keypad_AstrCols[Local_u8ColsIt].u8_LinePinID, DIO_u8HIGH);
	}

	Local_u8ErrorState = ES_OK;
	return Local_u8ErrorState;
}

ES Keypad_enuGetPressedButton(u8* copy_pu8KeypadState){
	ES Local_u8ErrorState = ES_NOK;

	//Loop Over all cols
	for(u8 Local_u8ColsIt = 0; Local_u8ColsIt < COLS_NUM; Local_u8ColsIt++){
		//Set Col Low
		DIO_enuSetPinValue(Keypad_AstrCols[Local_u8ColsIt].u8_LinePortID, Keypad_AstrCols[Local_u8ColsIt].u8_LinePinID, DIO_u8LOW);

		//Loop Over all Rows
		for(u8 Local_u8RowsIt = 0; Local_u8RowsIt < ROWS_NUM; Local_u8RowsIt++){

			//Check for low Row
			u8 Local_u8RowState;
			DIO_enuGetpin(Keypad_AstrRows[Local_u8RowsIt].u8_LinePortID, Keypad_AstrRows[Local_u8RowsIt].u8_LinePinID, &Local_u8RowState);
			if(!Local_u8RowState){

				//prevent bouncing
				while(!Local_u8RowState)
					DIO_enuGetpin(Keypad_AstrRows[Local_u8RowsIt].u8_LinePortID, Keypad_AstrRows[Local_u8RowsIt].u8_LinePinID, &Local_u8RowState);

				//assign value
				*copy_pu8KeypadState = Keypad_Au8Chars[Local_u8RowsIt * COLS_NUM + Local_u8ColsIt];

				Local_u8ErrorState = ES_OK;
				return Local_u8ErrorState;
			}

		}
		DIO_enuSetPinValue(Keypad_AstrCols[Local_u8ColsIt].u8_LinePortID, Keypad_AstrCols[Local_u8ColsIt].u8_LinePinID, DIO_u8HIGH);
	}
	*copy_pu8KeypadState = KEYPAD_NO_PRESSED;
	Local_u8ErrorState = ES_OK;
	return Local_u8ErrorState;
}
