#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h> 
// struct stat{
// ino_t st_ino;   //文件的inode节点
// mode_t st_mode; //文件的类型
// off_t st_size;  //文件的大小
// struct timespec st_atim;    //最后被访问的时间
// struct timespec st_mtim;    //文件内容最后被修改的时间
// struct timespec st_ctim;    //文件状态最后被改变的时间

// }*statStruct;

int main()
{
    // // int fd = open("./1.txt",O_RDONLY);
    // if(fd < 0)
    //     perror("open failed!");
    struct stat statBuf;
    {
        /* data */
    };
    
    int ret = stat("./1.txt",&statBuf);
    if(ret<0)
    {
        perror("stat failed!\n");
        _exit(0);
    }
    
    printf("1.txt的inode节点为：%lu\t文件大小为：%ld\n",statBuf.st_ino,statBuf.st_size);
    printf("该文件的文件类型为： %o\n",statBuf.st_mode);
    if(statBuf.st_mode & 04 )
        printf("其它组的成员具有读功能\n");
    else
        printf("其它组的成员不具有读功能\n");
    if(statBuf.st_mode & 02)
        printf("其它组的成员具有写功能\n");
    else
        printf("其它组的成员不具有写功能\n");
    
    printf("最后访问该文件的时间为：%s\n",ctime(&statBuf.st_atime));  
    printf("该文件内容最后被修改的时间为：%s\n",ctime(&statBuf.st_mtime));  
    printf("该文件状态最后被改动的时间为：%s\n",ctime(&statBuf.st_ctime));  
    

    return 0;
}