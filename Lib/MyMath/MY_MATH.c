/*
 * MY_MATH.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: LENOVO
 */


double factorial[100];

int max(int a, int b){
	if(a > b) return a;
	return b;
}
double Float_Abs(double a){
	if(a > 0) return a;
	return -1 * a;
}

void Math_voidInit(){
	set_factorial();
}

void set_factorial(){
    factorial[0] = 1;
    for(int i = 1; i < 100; i++){
        factorial[i] = factorial[i - 1] * i;
    }
}

double LN(double x) {

    if (x >= 2) {
        return LN(x/2.0) + (double)0.6931471806;
    }

    x = x-1;

    double total = 0.0;
    double xToTheIPower = x;

    for (int i = 1; i < 100; i++) {
        if (i&1) total += xToTheIPower / (i);
        else total -= xToTheIPower / (i);
        xToTheIPower *= x;
    }
    return total;
}

double e(double x){
    double sum = 0, xToTheIPower = 1;
    for (int i = 0; i < 38; i++){
        sum += xToTheIPower/factorial[i] ;
        xToTheIPower *= x;
    }
    return sum;
}

double power(double a,double b){
	if(b < 0){
		a = 1/a;
		b *= -1;
	}
	long IntegerVal = b;
	double ans = 1;
	for(int i = 0; i < IntegerVal; i++){
		ans *= a;
	}
	b -= IntegerVal;
	ans *= e(b * LN(a));
    return ans;
}
