#include <stdio.h>
#include <math.h>


int main()
{
	int n = 1;
	double x, eps, sum=0.0, a = 1.0;
	printf("Vvedite eps = ");
	scanf("%lf", &eps);
	printf("Vvedite x = ");
	scanf("%lf", &x);
	do {
		a *= pow(x-1, n)/(n*pow(x, n));
		sum += a;
		n++;
		printf("%lf\n", sum);
	}	
	while(fabs(a) > eps);
	printf("Summa ryada vicheslena c zadanoi tochnostiy = %lf", sum);

return 0;
}
