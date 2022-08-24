#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int fd1 = open("./1.txt",O_RDONLY);
	int fd2 = open("./2.txt",O_WRONLY);
	int fd3 = open("./3.txt",O_WRONLY);

	int fd4 = open("./4.txt",O_CREAT,0744);	//打开文件，不存在就创建 0744设置文件的访问权限
	


	if(fd1 < 0 || fd2 < 0 || fd3 < 0 ||fd4 < 0)  
		perror("open failed!\n");
	char buff[1024] = "";
	size_t ret;
	ret = read(fd1,buff,sizeof(buff));
	if(ret < 0)
		perror("read failed!\n");

	ret = write(fd2,buff,sizeof(buff));
	if(ret < 0)
		perror("write failed!\n");

	off_t ret2 = lseek(fd1,0,SEEK_CUR);	//获取1.txt当前的文件指针偏移量
	if(ret2 < 0)
		perror("lseek failed!\n");
	printf("文件一当前指针偏移为：%ld \n",ret2);
	ret2 = lseek(fd1,0,SEEK_END);	//计算1.txt大小
	if(ret2 < 0)
		perror("lseek failed!\n");
	printf("文件一大小为：%ld bit\n",ret2);
	ret2 = lseek(fd1,0,SEEK_SET);	//
	if(ret2 < 0)
		perror("lseek failed!\n");
	int* str1 = (int*)malloc(sizeof(int)*1025);
	int* str2 = (int*)malloc(sizeof(int)*1025);
	
	memset(str1,0x00,1024);
	memset(str2,0xFF,1024);
	
	ret = write(fd3,str1,1024);
	if(ret < 0)
		perror("write failed!\n");
	printf("1\n");
	ret = write(fd3,str2,1024);
	if(ret < 0)
		perror("write failed!\n");
	ret2 = lseek(fd3,0,SEEK_END);	//计算1.txt大小
	if(ret2 < 0)
		perror("lseek failed!\n");
	printf("文件三大小为：%ld bit\n",ret2);
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return 0;
}
