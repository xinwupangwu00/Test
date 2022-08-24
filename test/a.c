#include <stdio.h>

int main()
{
	int a = 10;
	void *p;
	p = &a;
	printf("p = %p\n",p);
	printf("*p = %ld\n",(long)p);
//	printf("(int)p = %d\n",(int)p);
	return 0;
}
