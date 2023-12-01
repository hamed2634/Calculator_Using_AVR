/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */

#include "..\.\Lib\errorStates.h"
#include "..\.\Lib\stdTypes.h"
#include "..\.\Lib\MyMath\MY_MATH.h"


#include "..\.\MCAL\DIO\DIO_int.h"

#include "..\.\HAL\Keypad\Keypad_int.h"
#include "..\.\HAL\LCD\LCD_int.h"

#include "Calculator.h"


int main(void){

	//Initialization
	Math_voidInit();
	DIO_enuInit();
	Keypad_enuInit();
	LCD_enuInit();

	//APP
	Run_Calculator();
}
