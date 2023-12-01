/*
 * Calculator.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */


#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#define MAX_SIZE 20
#define EPS 0.00001
#define PRECISION_DIGITS 4
#define MAXNUMBER (double)(2000000000)


void Clear_Arrays();
u8 priority(char key);
u8 Is_Operator(char character);
u8 Is_Open_Brackets(char character);
u8 Is_Close_Brackets(char character);
u8 Is_Number(char character);
void Run_Calculator(void);
ES Calc_Expression();
ES Infix_To_Postfix();
ES Calc_Postfix(double * value);
ES Validate_Expression();

#endif /* CALCULATOR_H_ */
