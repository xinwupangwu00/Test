#include <stdio.h>
#include <string.h>
int main()
{
    char *str = "believe phx dhx hope!";
    char str1[] = "believe phx dhx hope!";
    printf("%ld\n",sizeof(str));
    printf("%ld\n", strlen(str));
    printf("%ld\n",sizeof(str1));
    printf("%ld\n", strlen(str1));
    char *newstr = NULL;

    newstr = strstr(str, "dhx");
    printf("%s\n", newstr);

    return 0;
}