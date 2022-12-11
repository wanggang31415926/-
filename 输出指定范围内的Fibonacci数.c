#include <stdio.h>

int fib( int n );
void PrintFN( int m, int n );
    
int main()
{
    int m, n, t;

    scanf("%d %d %d", &m, &n, &t);
    printf("fib(%d) = %d\n", t, fib(t));
    PrintFN(m, n);

    return 0;
}
int fib( int n )
{
	int k = 1; 
	int a = 0 , b = 1 , c = 1 ;
	while (k < n)
	{
		c = a + b ;
		a = b ;
		b = c ;
		k++;
	}
	return c ;
}
void PrintFN( int m, int n )
{
	int i = 0 ;
	int ok = 1 ;
	int flag = 0 ;
	for (i = 1 ; ok ; i++)
	{
		ok = fib(i) <= n ;
		if( fib (i) >= m && ok)
		{
			if (flag == 0)
			{
				printf("%d",fib(i));
				flag = 1;
			}
			else
			{
				printf(" %d",fib(i));
			}
		}		
	}
	if (flag == 0)
	{
		printf("No Fibonacci number");
	}
}


