#include "..\..\.\Lib\errorStates.h"
#include "..\..\.\Lib\stdTypes.h"

#include "DIO_priv.h"
#include "DIO_config.h"



ES DIO_enuInit(void)
{
	ES Local_enuErrorState = ES_NOK;

	//Initialize Direction Pins
	DDRA = CONC(PA_PIN7_DIR, PA_PIN6_DIR, PA_PIN5_DIR, PA_PIN4_DIR, PA_PIN3_DIR, PA_PIN2_DIR, PA_PIN1_DIR, PA_PIN0_DIR);
	DDRB = CONC(PB_PIN7_DIR, PB_PIN6_DIR, PB_PIN5_DIR, PB_PIN4_DIR, PB_PIN3_DIR, PB_PIN2_DIR, PB_PIN1_DIR, PB_PIN0_DIR);
	DDRC = CONC(PC_PIN7_DIR, PC_PIN6_DIR, PC_PIN5_DIR, PC_PIN4_DIR, PC_PIN3_DIR, PC_PIN2_DIR, PC_PIN1_DIR, PC_PIN0_DIR);
	DDRD = CONC(PD_PIN7_DIR, PD_PIN6_DIR, PD_PIN5_DIR, PD_PIN4_DIR, PD_PIN3_DIR, PD_PIN2_DIR, PD_PIN1_DIR, PD_PIN0_DIR);

	//Initialize Port Pins
	PORTA = CONC(PA_PIN7_Val, PA_PIN6_Val, PA_PIN5_Val, PA_PIN4_Val, PA_PIN3_Val, PA_PIN2_Val, PA_PIN1_Val, PA_PIN0_Val);
	PORTB = CONC(PB_PIN7_Val, PB_PIN6_Val, PB_PIN5_Val, PB_PIN4_Val, PB_PIN3_Val, PB_PIN2_Val, PB_PIN1_Val, PB_PIN0_Val);
	PORTC = CONC(PC_PIN7_Val, PC_PIN6_Val, PC_PIN5_Val, PC_PIN4_Val, PC_PIN3_Val, PC_PIN2_Val, PC_PIN1_Val, PC_PIN0_Val);
	PORTD = CONC(PD_PIN7_Val, PD_PIN6_Val, PD_PIN5_Val, PD_PIN4_Val, PD_PIN3_Val, PD_PIN2_Val, PD_PIN1_Val, PD_PIN0_Val);

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}


ES DIO_enuSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8Value)
{
	ES Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID < DIO_PORTA || Copy_u8PortID > DIO_PORTD) Local_enuErrorState = ES_OUT_OF_RANGE;
	else{
		switch(Copy_u8PortID){
			case DIO_PORTA:
				DDRA = Copy_u8Value;
				break;
			case DIO_PORTB:
				DDRB = Copy_u8Value;
				break;
			case DIO_PORTC:
				DDRC = Copy_u8Value;
				break;
			case DIO_PORTD:
				DDRD = Copy_u8Value;
				break;
		}
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES DIO_enuSetPortValue(u8 Copy_u8PortID, u8 Copy_u8Value)
{
	ES Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID < DIO_PORTA || Copy_u8PortID > DIO_PORTD) Local_enuErrorState = ES_OUT_OF_RANGE;
	else{
		switch(Copy_u8PortID){
			case DIO_PORTA:
				PORTA = Copy_u8Value;
				break;
			case DIO_PORTB:
				PORTB = Copy_u8Value;
				break;
			case DIO_PORTC:
				PORTC = Copy_u8Value;
				break;
			case DIO_PORTD:
				PORTD = Copy_u8Value;
				break;
		}
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES DIO_enuTogPort(u8 Copy_u8PortID)
{
	ES Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID < DIO_PORTA || Copy_u8PortID > DIO_PORTD) Local_enuErrorState = ES_OUT_OF_RANGE;
	else{
		switch(Copy_u8PortID){
			case DIO_PORTA:
				PORTA = ~PORTA;
				break;
			case DIO_PORTB:
				PORTB = ~PORTB;
				break;
			case DIO_PORTC:
				PORTC = ~PORTC;
				break;
			case DIO_PORTD:
				PORTD = ~PORTD;
				break;
		}
		Local_enuErrorState = ES_OK;
	}


	return Local_enuErrorState;
}

ES DIO_enuGetPort(u8 Copy_u8PortID, u8* Copy_pu8Value)
{
	ES Local_enuErrorState = ES_NOK;

	if(Copy_pu8Value == NULL) Local_enuErrorState = ES_NULL_POINTER;
	else if (Copy_u8PortID < DIO_PORTA || Copy_u8PortID > DIO_PORTD) Local_enuErrorState = ES_OUT_OF_RANGE;
	else{
		switch(Copy_u8PortID){
			case DIO_PORTA:
				*Copy_pu8Value = PINA;
				break;
			case DIO_PORTB:
				*Copy_pu8Value = PINB;
				break;
			case DIO_PORTC:
				*Copy_pu8Value = PINC;
				break;
			case DIO_PORTD:
				*Copy_pu8Value = PIND;
				break;
		}
		Local_enuErrorState = ES_OK;
	}


	return Local_enuErrorState;
}






ES DIO_enuSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinID, u8 Copy_u8Value)
{
	ES Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID < DIO_PORTA || Copy_u8PortID > DIO_PORTD || Copy_u8Value > OUTPUT) Local_enuErrorState = ES_OUT_OF_RANGE;
	else if (Copy_u8PinID < DIO_PIN0 || Copy_u8PinID > DIO_PIN7 ) Local_enuErrorState = ES_OUT_OF_RANGE;
	else {
		switch(Copy_u8PortID){
			case DIO_PORTA:
				DDRA &= ~(1 << Copy_u8PinID);
				DDRA |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTB:
				DDRB &= ~(1 << Copy_u8PinID);
				DDRB |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTC:
				DDRC &= ~(1 << Copy_u8PinID);
				DDRC |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTD:
				DDRD &= ~(1 << Copy_u8PinID);
				DDRD |= (Copy_u8Value << Copy_u8PinID);
				break;
		}
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES DIO_enuSetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinID, u8 Copy_u8Value)
{
	ES Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID < DIO_PORTA || Copy_u8PortID > DIO_PORTD || Copy_u8Value > OUTPUT) Local_enuErrorState = ES_OUT_OF_RANGE;
	else if (Copy_u8PinID < DIO_PIN0 || Copy_u8PinID > DIO_PIN7 ) Local_enuErrorState = ES_OUT_OF_RANGE;
	else{
		switch(Copy_u8PortID){
			case DIO_PORTA:
				PORTA &= ~(1 << Copy_u8PinID);
				PORTA |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTB:
				PORTB &= ~(1 << Copy_u8PinID);
				PORTB |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTC:
				PORTC &= ~(1 << Copy_u8PinID);
				PORTC |= (Copy_u8Value << Copy_u8PinID);
				break;
			case DIO_PORTD:
				PORTD &= ~(1 << Copy_u8PinID);
				PORTD |= (Copy_u8Value << Copy_u8PinID);
				break;
		}
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

ES DIO_enuGetpin(u8 Copy_u8PortID,u8 Copy_u8PinID, u8* Copy_pu8Value)
{
	ES Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID < DIO_PORTA || Copy_u8PortID > DIO_PORTD) Local_enuErrorState = ES_OUT_OF_RANGE;
	else if (Copy_u8PinID < DIO_PIN0 || Copy_u8PinID > DIO_PIN7 ) Local_enuErrorState = ES_OUT_OF_RANGE;
	else if(Copy_pu8Value == NULL)Local_enuErrorState = ES_NULL_POINTER;
	else{
		switch(Copy_u8PortID){
			case DIO_PORTA:
				*Copy_pu8Value = getBit(PINA,Copy_u8PinID);
				break;
			case DIO_PORTB:
				*Copy_pu8Value = getBit(PINB,Copy_u8PinID);
				break;
			case DIO_PORTC:
				*Copy_pu8Value = getBit(PINC,Copy_u8PinID);
				break;
			case DIO_PORTD:
				*Copy_pu8Value = getBit(PIND,Copy_u8PinID);
				break;
		}
		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}

ES DIO_enuTogPin(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
	ES Local_enuErrorState = ES_NOK;

	if(Copy_u8PortID < DIO_PORTA || Copy_u8PortID > DIO_PORTD) Local_enuErrorState = ES_OUT_OF_RANGE;
	else if (Copy_u8PinID < DIO_PIN0 || Copy_u8PinID > DIO_PIN7 ) Local_enuErrorState = ES_OUT_OF_RANGE;
	else{
		switch(Copy_u8PortID){
			case DIO_PORTA:
				PORTA ^= (1 << Copy_u8PinID);
				break;
			case DIO_PORTB:
				PORTB ^= (1 << Copy_u8PinID);
				break;
			case DIO_PORTC:
				PORTC ^= (1 << Copy_u8PinID);
				break;
			case DIO_PORTD:
				PORTD ^= (1 << Copy_u8PinID);
				break;
		}
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;

}
