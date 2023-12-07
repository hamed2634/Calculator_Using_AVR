/*
 * Calculator.c

 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */

#include "string.h"
#include "..\.\Lib\errorStates.h"
#include "..\.\Lib\stdTypes.h"
#include "..\.\Lib\Stack\stack.h"
#include "..\.\Lib\MyMath\MY_MATH.h"


#include "..\.\MCAL\DIO\DIO_int.h"

#include "..\.\HAL\Keypad\Keypad_int.h"
#include "..\.\HAL\LCD\LCD_int.h"

#include "Calculator.h"

double GlobalOperands[MAX_SIZE];
char GlobalShaddedExpression[MAX_SIZE];
char GlobalInputExpression[MAX_SIZE];
char GlobalPostfixExpression[MAX_SIZE];
char GlobalResultExpression[MAX_SIZE];


void Clear_Arrays(){
	for(int i = 0; i < MAX_SIZE; i++){
		GlobalShaddedExpression[i] = 0;
		GlobalInputExpression[i] = 0;
		GlobalPostfixExpression[i] = 0;
		GlobalResultExpression[i] = 0;
	}
}



void Run_Calculator(){
	u8 Local_u8CursorIdx = 0;
	u8 Local_u8ExpressionSize = 0;
	u8 LCD_DoneCalculating = 0;
	while(1){
		u8 Local_u8ButtonIsPressed;
		Keypad_enuGetPressedButton(&Local_u8ButtonIsPressed);
		if(Local_u8ButtonIsPressed == KEYPAD_STATE_NO_PRESSED) continue;

		if(LCD_DoneCalculating){
			if(Local_u8ButtonIsPressed == '=') continue;
			else if(Local_u8ButtonIsPressed == 'A' || Local_u8ButtonIsPressed == 'C'){
				Clear_Arrays();
				Local_u8CursorIdx = 0;
				LCD_enuClearDisplay();
			}
			else if(Is_Operator(Local_u8ButtonIsPressed)){
				LCD_enuClearDisplay();
				for(int i = 0; i < MAX_SIZE; i++){
					GlobalShaddedExpression[i] = 0;
					GlobalInputExpression[i] = 0;
					GlobalPostfixExpression[i] = 0;
				}
				for(Local_u8CursorIdx = 0; GlobalResultExpression[Local_u8CursorIdx]; Local_u8CursorIdx++){
					GlobalInputExpression[Local_u8CursorIdx] = GlobalResultExpression[Local_u8CursorIdx];
					LCD_enuDisplayChar(GlobalInputExpression[Local_u8CursorIdx]);
					Local_u8ExpressionSize++;
				}
				GlobalInputExpression[Local_u8CursorIdx++] = Local_u8ButtonIsPressed;
				LCD_enuDisplayChar(Local_u8ButtonIsPressed);
				Local_u8ExpressionSize++;
			}
			else if(Local_u8ButtonIsPressed != '<' && Local_u8ButtonIsPressed != '>'){
				Local_u8CursorIdx = 0;
				LCD_enuClearDisplay();
				Clear_Arrays();
				GlobalInputExpression[Local_u8CursorIdx++] = Local_u8ButtonIsPressed;
				LCD_enuDisplayChar(Local_u8ButtonIsPressed);
			}
			LCD_DoneCalculating = 0;

		}
		else{
			if(Local_u8ButtonIsPressed == 'A'){
				LCD_enuClearDisplay();
				Clear_Arrays();
				Local_u8CursorIdx = 0;
				Local_u8ExpressionSize = 0;
			}
			else if(Local_u8ButtonIsPressed == 'C'){
				if(Local_u8CursorIdx){
					GlobalInputExpression[--Local_u8CursorIdx] = '\0';
					LCD_enuClearDisplay();
					for(u8 i = 0; i < Local_u8ExpressionSize - 1; i++){
						if(!GlobalInputExpression[i]) {
							GlobalInputExpression[i] = GlobalInputExpression[i + 1];
							GlobalInputExpression[i + 1] = 0;
						}
						LCD_enuDisplayChar(GlobalInputExpression[i]);
					}
					Local_u8CursorIdx = max(0,Local_u8CursorIdx);
					LCD_enuGoto(1,Local_u8CursorIdx);
					Local_u8ExpressionSize--;
				}
			}
			else if(Local_u8ButtonIsPressed == '='){
				LCD_DoneCalculating = 1;
				Local_u8ExpressionSize = 0;
				ES Local_enuErrorState = Validate_Expression();
				if(Local_enuErrorState == ES_SYNTAX_ERROR){
					LCD_enuClearDisplay();
					LCD_enuGoto(1,2);
					LCD_enuDisplayChar('S');
					LCD_enuDisplayChar('Y');
					LCD_enuDisplayChar('N');
					LCD_enuDisplayChar('T');
					LCD_enuDisplayChar('A');
					LCD_enuDisplayChar('X');
					LCD_enuDisplayChar(' ');
					LCD_enuDisplayChar('E');
					LCD_enuDisplayChar('R');
					LCD_enuDisplayChar('R');
					LCD_enuDisplayChar('O');
					LCD_enuDisplayChar('R');
				}
				else if(Local_enuErrorState == ES_OK){
					LCD_enuGoto(2,0);
					Local_enuErrorState = Calc_Expression();
					if(Local_enuErrorState == ES_MATH_ERROR){
						LCD_enuClearDisplay();
						LCD_enuGoto(1,3);
						LCD_enuDisplayChar('M');
						LCD_enuDisplayChar('A');
						LCD_enuDisplayChar('T');
						LCD_enuDisplayChar('H');
						LCD_enuDisplayChar(' ');
						LCD_enuDisplayChar('E');
						LCD_enuDisplayChar('R');
						LCD_enuDisplayChar('R');
						LCD_enuDisplayChar('O');
						LCD_enuDisplayChar('R');
					}
					else if(Local_enuErrorState == ES_OVERFLOW){
						LCD_enuClearDisplay();
						LCD_enuGoto(1,4);
						LCD_enuDisplayChar('O');
						LCD_enuDisplayChar('V');
						LCD_enuDisplayChar('E');
						LCD_enuDisplayChar('R');
						LCD_enuDisplayChar('F');
						LCD_enuDisplayChar('L');
						LCD_enuDisplayChar('O');
						LCD_enuDisplayChar('W');
					}
					else{
						for(u8 i = 0; i < MAX_SIZE; i++){
							LCD_enuDisplayChar(GlobalResultExpression[i]);
						}
					}
				}
			}
			else if(Local_u8ButtonIsPressed == '>') {
				if(Local_u8CursorIdx + 1 < MAX_SIZE && GlobalInputExpression[Local_u8CursorIdx])Local_u8CursorIdx++;
				LCD_enuGoto(1,Local_u8CursorIdx);
			}
			else if(Local_u8ButtonIsPressed == '<'){
				Local_u8CursorIdx--;
				Local_u8CursorIdx = max(0,Local_u8CursorIdx);
				LCD_enuGoto(1,Local_u8CursorIdx);
			}
			else{
				Local_u8ExpressionSize++;
				LCD_enuDisplayChar(Local_u8ButtonIsPressed);
				GlobalInputExpression[Local_u8CursorIdx++] = Local_u8ButtonIsPressed;
			}
		}
	}
}


ES Calc_Expression(){
    ES Local_enuErrorState;
    Infix_To_Postfix();
    double Local_DoubleResult;
    Local_enuErrorState = Calc_Postfix(&Local_DoubleResult);

    if(Local_enuErrorState != ES_OK) return Local_enuErrorState;
    if(Local_DoubleResult > MAXNUMBER) return ES_OVERFLOW;

    u8 Local_Idx = 0;

    //printing Sign
    if(Local_DoubleResult < 0) {
    	GlobalResultExpression[Local_Idx++] = '-';
        Local_DoubleResult *= -1;
    }


    long Local_longValue = Local_DoubleResult;
    long Local_tmp = Local_longValue;

    if(!Local_longValue){
        GlobalResultExpression[Local_Idx++] = '0';
    }

    Local_DoubleResult -= Local_longValue;
    int Local_Size = 0;
    while(Local_tmp){
        Local_Size++;
        Local_tmp/=10;
    }
    for (int i = Local_Size + Local_Idx - 1; i >= Local_Idx; --i) {
        GlobalResultExpression[i] = (Local_longValue %10) + '0';
        Local_longValue/=10;
    }
    Local_Idx += Local_Size ;

    //printing Fraction
    if(Float_Abs(Local_DoubleResult - (long)Local_DoubleResult) > EPS){
    	GlobalResultExpression[Local_Idx++] = '.';
    	for(u8 i = 0; i < PRECISION_DIGITS; i++){
    		Local_DoubleResult *= 10;
    		GlobalResultExpression[Local_Idx++] = ((long)Local_DoubleResult %10 + '0');
    	}
    }

    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}


u8 priority(char key){
	if(key == '+' || key == '-') return 0;
	if(key == '*' || key == '/') return 1;
	if(key == '^') return 2;
	return -1;
}

ES Infix_To_Postfix(){
    ES Local_enuErrorState = ES_NOK;
    char* LocalInfixExpression = GlobalShaddedExpression;
    Stack st;
    Initialize_Stack(&st);
    u8 postfix_ind = 0;
    for(int i = 0; LocalInfixExpression[i]; ++i){
        if(LocalInfixExpression[i] == ')'){
            char c;
            while(!Stack_Empty(&st) && Top(&st) != '('){
                Pop(&c,&st);
                GlobalPostfixExpression[postfix_ind] = c;
                postfix_ind++;
            }
            Pop(&c,&st);
        }
        else{
            if(LocalInfixExpression[i] == '('){
                Push(&st, LocalInfixExpression[i]);
            }
            else if(LocalInfixExpression[i] == '+' || LocalInfixExpression[i] == '-' || LocalInfixExpression[i] == '*' || LocalInfixExpression[i] == '/' || LocalInfixExpression[i] == '^'){
                while(!Stack_Empty(&st) && Top(&st) != '(' && priority(LocalInfixExpression[i]) <= priority(Top(&st))){
                    char c;
                    Pop(&c,&st);
                    GlobalPostfixExpression[postfix_ind] = (char)c;
                    postfix_ind++;
                }
                Push(&st, LocalInfixExpression[i]);
            }
            else {
            	GlobalPostfixExpression[postfix_ind] = LocalInfixExpression[i];
                postfix_ind++;
            }
        }
    }
    while(!Stack_Empty(&st)){
        char c;
        Pop(&c,&st);
        GlobalPostfixExpression[postfix_ind] = (char)c;
        postfix_ind++;
    }
    GlobalPostfixExpression[postfix_ind] = '\0';
    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}

ES Calc_Postfix(double * Copy_pDoubleResult){
    ES Local_enuErrorState = ES_NOK;
    Stack st;
    Initialize_Stack(&st);
    for (int i = 0; GlobalPostfixExpression[i]; ++i) {
        if(GlobalPostfixExpression[i] >= 'A' && GlobalPostfixExpression[i] <= 'Z'){
            Push(&st,GlobalPostfixExpression[i]);
        }
        else{
            if(Stack_Size(&st) >= 2){
                char op1,op2;
                Pop(&op2,&st);
                Pop(&op1,&st);
                switch (GlobalPostfixExpression[i]) {
                    case '+':
                        GlobalOperands[op1 - 'A'] = GlobalOperands[op1 - 'A'] + GlobalOperands[op2 - 'A'];
                        Push(&st, op1);
                        break;
                    case '-':
                        GlobalOperands[op1 - 'A'] = GlobalOperands[op1 - 'A'] - GlobalOperands[op2 - 'A'];
                        Push(&st, op1);
                        break;
                    case '*':
                        GlobalOperands[op1 - 'A'] = GlobalOperands[op1 - 'A'] * GlobalOperands[op2 - 'A'];
                        Push(&st, op1);
                        break;
                    case '/':
                    	if(Float_Abs(GlobalOperands[op2 - 'A']) < EPS) return ES_MATH_ERROR;
                        GlobalOperands[op1 - 'A'] = GlobalOperands[op1 - 'A'] / GlobalOperands[op2 - 'A'];
                        Push(&st, op1);
                        break;
                    case '^':
                    	if(GlobalOperands[op2 - 'A'] > 40) return ES_OVERFLOW;
                        GlobalOperands[op1 - 'A'] =  power(GlobalOperands[op1 - 'A'],GlobalOperands[op2 - 'A']) ;
                        Push(&st, op1);
                        break;
                    default:
                        break;
                }
            }
            else{
                return ES_NOK;
            }
        }
    }
    *Copy_pDoubleResult = GlobalOperands[Top(&st) - 'A'];

    Local_enuErrorState = ES_OK;
    return Local_enuErrorState;
}
u8 Is_Operator(char character){
	return (character == '+' || character == '-' || character == '*' || character == '/' || character == '^');
}

u8 Is_Open_Brackets(char character){
	return character == '(';
}

u8 Is_Close_Brackets(char character){
	return character == ')';
}

u8 Is_Number(char character){
	return character >= '0' && character <= '9';
}

ES Validate_Expression(){
	double Local_s64Operand = 0, floatweight = 0.1;
	u8 IsFloat = 0, IsNegative = 0, ShadedExpressionIdx = 0, OperandsArrIdx = 0;
    u8 Local_ExpIt;
	for(Local_ExpIt = 0;GlobalInputExpression[Local_ExpIt];Local_ExpIt++){
		if(GlobalInputExpression[Local_ExpIt] == '-' || GlobalInputExpression[Local_ExpIt] == '+' ){
			if(!Local_ExpIt || Is_Operator(GlobalInputExpression[Local_ExpIt - 1]) || Is_Open_Brackets(GlobalInputExpression[Local_ExpIt - 1])){
				if(GlobalInputExpression[Local_ExpIt] == '-') IsNegative ^= 1;
			}
			else {
                if(!Is_Close_Brackets(GlobalInputExpression[Local_ExpIt - 1])){
                    GlobalShaddedExpression[ShadedExpressionIdx++] = 'A' + OperandsArrIdx;
                    if(IsNegative){
                        GlobalOperands[OperandsArrIdx++] = -1 * Local_s64Operand;
                    }
                    else {
                        GlobalOperands[OperandsArrIdx++] = Local_s64Operand;
                    }

                    //For New Number
                    IsFloat = 0, IsNegative = 0;
                    Local_s64Operand = 0,floatweight = 0.1;
                }
                GlobalShaddedExpression[ShadedExpressionIdx++] = GlobalInputExpression[Local_ExpIt];
            }
		}
		else if(GlobalInputExpression[Local_ExpIt] == '*' || GlobalInputExpression[Local_ExpIt] == '/'){
			if(!Local_ExpIt || Is_Operator(GlobalInputExpression[Local_ExpIt - 1]) ||  Is_Open_Brackets(GlobalInputExpression[Local_ExpIt - 1])){
				return ES_SYNTAX_ERROR;
			}
            else{
                if(!Is_Close_Brackets(GlobalInputExpression[Local_ExpIt - 1])){
                    GlobalShaddedExpression[ShadedExpressionIdx++] = 'A' + OperandsArrIdx;
                    if(IsNegative){
                        GlobalOperands[OperandsArrIdx++] = -1 * Local_s64Operand;
                    }
                    else {
                        GlobalOperands[OperandsArrIdx++] = Local_s64Operand;
                    }

                    //For New Number
                    IsFloat = 0, IsNegative = 0;
                    Local_s64Operand = 0,floatweight = 0.1;
                }
                GlobalShaddedExpression[ShadedExpressionIdx++] = GlobalInputExpression[Local_ExpIt];

            }

		}
		else if(Is_Operator(GlobalInputExpression[Local_ExpIt])){
			if(!Local_ExpIt || Is_Operator(GlobalInputExpression[Local_ExpIt - 1])){
				return ES_SYNTAX_ERROR;
			}
			else{
                if(!Is_Close_Brackets(GlobalInputExpression[Local_ExpIt - 1])){
                    GlobalShaddedExpression[ShadedExpressionIdx++] = 'A' + OperandsArrIdx;
                    if(IsNegative){
                        GlobalOperands[OperandsArrIdx++] = -1 * Local_s64Operand;
                    }
                    else {
                        GlobalOperands[OperandsArrIdx++] = Local_s64Operand;
                    }

                    //For New Number
                    IsFloat = 0, IsNegative = 0;
                    Local_s64Operand = 0,floatweight = 0.1;
                }
                GlobalShaddedExpression[ShadedExpressionIdx++] = GlobalInputExpression[Local_ExpIt];
			}
		}
		else if(GlobalInputExpression[Local_ExpIt] == '.'){
			if(IsFloat || (Local_ExpIt > 0 && Is_Close_Brackets(GlobalInputExpression[Local_ExpIt - 1]))){
				return ES_SYNTAX_ERROR;
			}
			if(!Local_ExpIt || Is_Number(GlobalInputExpression[Local_ExpIt - 1]) ||Is_Open_Brackets(GlobalInputExpression[Local_ExpIt - 1]) || Is_Operator(GlobalInputExpression[Local_ExpIt - 1])){
				IsFloat = 1;
			}
		}
		else if(Is_Number(GlobalInputExpression[Local_ExpIt])){
			if(Is_Close_Brackets(GlobalInputExpression[Local_ExpIt - 1])){
				return ES_SYNTAX_ERROR;
			}
			else if(IsFloat){
				Local_s64Operand += floatweight * (GlobalInputExpression[Local_ExpIt] - '0');
				floatweight/=10;
			}
			else{
				Local_s64Operand *= 10;
				Local_s64Operand += (GlobalInputExpression[Local_ExpIt] - '0');
			}
		}
        else if(Is_Close_Brackets(GlobalInputExpression[Local_ExpIt])){
            if(!Local_ExpIt || Is_Operator(GlobalInputExpression[Local_ExpIt - 1]) || Is_Open_Brackets(GlobalInputExpression[Local_ExpIt - 1])){
                return ES_SYNTAX_ERROR;
            }
            else if(Is_Number(GlobalInputExpression[Local_ExpIt - 1]) || IsFloat){
                GlobalShaddedExpression[ShadedExpressionIdx++] = 'A' + OperandsArrIdx;
                GlobalShaddedExpression[ShadedExpressionIdx++] = ')';
                if(IsNegative){
                    GlobalOperands[OperandsArrIdx++] = -1 * Local_s64Operand;
                }
                else {
                    GlobalOperands[OperandsArrIdx++] = Local_s64Operand;
                }
                //For New Number
                IsFloat = 0, IsNegative = 0;
                Local_s64Operand = 0,floatweight = 0.1;
            }
            else{
                GlobalShaddedExpression[ShadedExpressionIdx++] = ')';
            }
        }
		else if(Is_Open_Brackets(GlobalInputExpression[Local_ExpIt])){
			if(Local_ExpIt && Is_Close_Brackets(GlobalInputExpression[Local_ExpIt - 1])){
				GlobalShaddedExpression[ShadedExpressionIdx++] = '*';
                GlobalShaddedExpression[ShadedExpressionIdx++] = '(';
                if(IsNegative){
					GlobalOperands[OperandsArrIdx++] = -1 * Local_s64Operand;
				}
				else {
					GlobalOperands[OperandsArrIdx++] = Local_s64Operand;
				}
				//For New Number
				IsFloat = 0, IsNegative = 0;
				Local_s64Operand = 0,floatweight = 0.1;
			}
			else if(Local_ExpIt && (Is_Number(GlobalInputExpression[Local_ExpIt - 1])|| IsFloat)){
				GlobalShaddedExpression[ShadedExpressionIdx++] = 'A' + OperandsArrIdx;
				GlobalShaddedExpression[ShadedExpressionIdx++] = '*';
                GlobalShaddedExpression[ShadedExpressionIdx++] = '(';
                if(IsNegative){
					GlobalOperands[OperandsArrIdx++] = -1 * Local_s64Operand;
				}
				else {
					GlobalOperands[OperandsArrIdx++] = Local_s64Operand;
				}
				//For New Number
				IsFloat = 0, IsNegative = 0;
				Local_s64Operand = 0,floatweight = 0.1;
			}
			else{
				GlobalShaddedExpression[ShadedExpressionIdx++] = '(';
			}
		}
	}
    if(GlobalShaddedExpression[ShadedExpressionIdx - 1] != ')'){
        GlobalShaddedExpression[ShadedExpressionIdx++] = 'A' + OperandsArrIdx;
        if(IsNegative){
            GlobalOperands[OperandsArrIdx++] = -1 * Local_s64Operand;
        }
        else {
            GlobalOperands[OperandsArrIdx++] = Local_s64Operand;
        }
    }
    if(OperandsArrIdx == 0 && Local_ExpIt) return ES_SYNTAX_ERROR;

    Stack Local_stBrackets;
    char Local_chTmp;
    Initialize_Stack(&Local_stBrackets);
    for(Local_ExpIt = 0;GlobalInputExpression[Local_ExpIt];Local_ExpIt++) {
        if (GlobalInputExpression[Local_ExpIt] == '(') Push(&Local_stBrackets, ')');
        else if (GlobalInputExpression[Local_ExpIt] == ')'){
        	if(!Stack_Empty(&Local_stBrackets)) {
        		Pop(&Local_chTmp, &Local_stBrackets);
        	}
        	else{
                return ES_SYNTAX_ERROR;
        	}
        }
    }
	if(!Stack_Empty(&Local_stBrackets)) {
		return ES_SYNTAX_ERROR;
	}

	if(Local_ExpIt && Is_Operator(GlobalInputExpression[Local_ExpIt - 1])){
		return ES_SYNTAX_ERROR;
	}

	return ES_OK;
}
