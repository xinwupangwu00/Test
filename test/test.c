#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void func(char low,char high)
{
	short a;
	a = (high << 8) | low;
	printf("new is :%hd\n",a);
	return;	
}

int main()
{
	char a[20];
	sprintf(a,"123%c",'4');
	printf("strlen(a) = %ld,a = %s\n",strlen(a),a);	
	sprintf(a,"55555678%c",'9');
	printf("strlen(a) = %ld,a = %s\n",strlen(a),a);	
	
	return 0;
}


