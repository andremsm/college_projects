#include <stdio.h>
#include <stdlib.h>
#include <matheval.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

void *funcF, *funcDF;

void init(char *sf){
	int l = strlen(sf);
	
	if (l > 0 && sf[l-1] == '\n')
		sf[l-1] = '\0';
	funcF = evaluator_create(sf);
	
	funcDF = evaluator_derivative_x(funcF);
}

double f(double x){
	return evaluator_evaluate_x(funcF,x);
}

double df(double x){
	return evaluator_evaluate_x(funcDF,x);
}

double encontraRaiz(double x0, double eps, int max_it, int *it){
	
	void     *ptr1, *ptr2;
	double   *g,    *e;
	double    k,     j;
	long int *a,    *b;
	long int  c,     d;
	
	double xn, xs, x1, xs1;
	unsigned long int ulp = 0;
	printf("%d, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %ld\n", *it, x0, f(x0), x0, f(x0), 0.0, 0.0, ulp);
	xn = x0 - f(x0)/df(x0);
	xs = xn - (f(xn)*(xn-x0)/(f(xn)-f(x0)));
	x1 = xn;
	++(*it);
	printf("%d, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %ld\n", *it, xn, f(xn), xn, f(xn), 0.0, 0.0, ulp);
	while ((fabs(x0-xn) > eps && *it < max_it) || (fabs(x1-xs) > eps && *it < max_it)){
		if ((fabs(x0-xn) > eps)){
			x0 =  xn;
			xn =  x0 - f(x0)/df(x0);
		}
		xs1 = xs;
		++(*it);
		g = &xn;
		e = &xs;
		ptr1 = g;
		ptr2 = e;
		a = ptr1;
		b = ptr2;
		c = *a;
		d = *b;
		ulp = abs((c-d))-1;
		printf("%d, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %ld\n", *it, xn, f(xn), xs, f(xs), xn-xs, fabs((xn-xs)/xn), ulp);
		//if ((fabs(x1-xs) < eps))
			xs = xs - (f(xs)*(xs-x1)/(f(xs)-f(x1)));
		x1 = xs1;
		
		
	}
	return xn;
}

int main(){
	
	char sf[100];
	
	double x0;
	double eps;
	int max_iter;
	int iteracoes = 0;
	
	scanf("%s",  sf);
	scanf("%lf", &x0);
	scanf("%lf", &eps);
	scanf("%d",  &max_iter);
	
	init (sf);
	
	double raiz = encontraRaiz(x0, eps, max_iter, &iteracoes);
	
	return 0;
}