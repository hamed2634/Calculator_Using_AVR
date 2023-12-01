/*
 * LCD_prog.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */

#include "..\..\.\Lib\errorStates.h"
#include "..\..\.\Lib\stdTypes.h"

#include "..\..\.\MCAL\DIO\DIO_int.h"

#include "LCD_config.h"
#include "LCD_priv.h"

#include "util/delay.h"

ES LCD_enuInit(void){
	ES Local_enuErrorState = ES_NOK;

	DIO_enuSetPinDirection(RS_PORT, RS_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(RW_PORT, RW_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(EN_PORT, EN_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D7_PORT, D7_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D6_PORT, D6_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D5_PORT, D5_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D4_PORT, D4_PIN, DIO_u8OUTPUT);
	_delay_ms(35);

#if LCD_MODE == EIGHT_BIT
	DIO_enuSetPinDirection(D3_PORT, D3_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D2_PORT, D2_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D1_PORT, D1_PIN, DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D0_PORT, D0_PIN, DIO_u8OUTPUT);
	LCD_inVoidSendCommand(0x3B);
#elif LCD_MODE == FOUR_BIT
	LCD_invidSendCommand(0x2B);
#endif
	_delay_ms(1);
	LCD_inVoidSendCommand(0x0f);
	_delay_ms(1);
	LCD_inVoidSendCommand(0x01);
	_delay_ms(2);
	LCD_inVoidSendCommand(0x06);

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}

ES LCD_enuDisplayChar(u8 Copy_u8Data){
	ES Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8HIGH);
	LCD_VoidLatch(Copy_u8Data);

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}

ES LCD_enuSendCommand(u8 Copy_u8Command){
	ES Local_enuErrorState = ES_NOK;

	DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8LOW);
	LCD_VoidLatch(Copy_u8Command);

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}

ES LCD_enuClearDisplay(){
	ES Local_enuErrorState = ES_NOK;

	LCD_inVoidSendCommand(0x01);

	Local_enuErrorState = ES_OK;
	return Local_enuErrorState;
}

static void LCD_VoidLatch(u8 Copy_u8Data)
{
	DIO_enuSetPinValue(RW_PORT , RW_PIN , DIO_u8LOW);
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);

	DIO_enuSetPinValue(D7_PORT , D7_PIN , ((Copy_u8Data>>7)&1));
	DIO_enuSetPinValue(D6_PORT , D6_PIN , ((Copy_u8Data>>6)&1));
	DIO_enuSetPinValue(D5_PORT , D5_PIN , ((Copy_u8Data>>5)&1));
	DIO_enuSetPinValue(D4_PORT , D4_PIN , ((Copy_u8Data>>4)&1));

#if LCD_MODE == EIGHT_BIT
	DIO_enuSetPinValue(D3_PORT , D3_PIN , ((Copy_u8Data>>3)&1));
	DIO_enuSetPinValue(D2_PORT , D2_PIN , ((Copy_u8Data>>2)&1));
	DIO_enuSetPinValue(D1_PORT , D1_PIN , ((Copy_u8Data>>1)&1));
	DIO_enuSetPinValue(D0_PORT , D0_PIN , ((Copy_u8Data>>0)&1));
#endif

	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8HIGH);
	_delay_ms(10);
	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);
	_delay_ms(10);

}


static inline void LCD_inVoidSendCommand(u8 Copy_u8Command){

	DIO_enuSetPinValue(RS_PORT, RS_PIN, DIO_u8LOW);
	DIO_enuSetPinValue(RW_PORT, RW_PIN, DIO_u8LOW);
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8LOW);

	DIO_enuSetPinValue(D7_PORT, D7_PIN, (Copy_u8Command >> 7)&1);
	DIO_enuSetPinValue(D6_PORT, D6_PIN, (Copy_u8Command >> 6)&1);
	DIO_enuSetPinValue(D5_PORT, D5_PIN, (Copy_u8Command >> 5)&1);
	DIO_enuSetPinValue(D4_PORT, D4_PIN, (Copy_u8Command >> 4)&1);
	DIO_enuSetPinValue(D3_PORT, D3_PIN, (Copy_u8Command >> 3)&1);
	DIO_enuSetPinValue(D2_PORT, D2_PIN, (Copy_u8Command >> 2)&1);
	DIO_enuSetPinValue(D1_PORT, D1_PIN, (Copy_u8Command >> 1)&1);
	DIO_enuSetPinValue(D0_PORT, D0_PIN, (Copy_u8Command >> 0)&1);

	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8HIGH);
	_delay_ms(10);
	DIO_enuSetPinValue(EN_PORT, EN_PIN, DIO_u8LOW);


}



ES LCD_enuGoto(u8 Copy_u8Line,u8 Copy_u8Block)
{
	ES Local_ErrorState = ES_NOK;
	if (Copy_u8Line == 1)
	{
		Local_ErrorState = LCD_enuSendCommand(0x80 + Copy_u8Block);
	}
	else if(Copy_u8Line == 2)
	{
		Local_ErrorState = LCD_enuSendCommand(0x80+0x40+Copy_u8Block);
	}
	else
	{
		return ES_OUT_OF_RANGE;
	}
	return Local_ErrorState;
}

