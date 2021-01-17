#include<stdio.h>

int Fibonacci(int n)
{
	if(n == 1 || n == 2)return 1;

	return Fibonacci(n-1)+Fibonacci(n-2);
}

int Fibonacci2(int n)
{
	if(n == 1 || n == 2)return 1;

	int fn;
	int fn1 = 1;
	int fn2 = 1;
	int i;
	for(i = 3;i<=n;i++)
	{
		fn = fn1+fn2;
		fn2 = fn1;
		fn1 = fn;
	}

	return fn;
}

int main()
{
	int n = Fibonacci2(50);
	printf("%d\n",n);
	return 0;
}
