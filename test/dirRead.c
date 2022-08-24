#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
int main()
{
    DIR *dirPtr = NULL;
    struct dirent *dirBuf;
   
    if((dirPtr = opendir("../../workspace")) == NULL)
    {
        perror("open dir failed!");
        exit(-1);
    }
    errno = 0;
    while(dirBuf = readdir(dirPtr))
        printf("%s\t%ld\n",dirBuf->d_name,dirBuf->d_ino);
    if(errno != 0)
    {
        printf("readdir failed!\n");
        exit(-1);
    }
    else
        printf("end of the directory\n");
    closedir(dirPtr);
    return 0;
}