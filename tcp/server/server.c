#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>


#define MYPORT (8000)
#define IP ("192.168.92.129")
// struct sockaddr{
//    sa_family_t sa_family;
//    char        sa_data[14]; 
// };
// struct sockaddr_in {
//                sa_family_t    sin_family; /* address family: AF_INET */
//                in_port_t      sin_port;   /* port in network byte order */
//                struct in_addr sin_addr;   /* internet address */
//            };
int main()
{
    int sockfd = 0;
    int clientfd = 0;
    int ret = 0; 
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));

    addr.sin_family = AF_INET;      //ipv4协议族
    addr.sin_port = htons(MYPORT);     //端口号转装换为网络字节序
    addr.sin_addr.s_addr = inet_addr(IP);   //将字符串转装换为网络字节序
    //bzero(&addr.sin_zero,8);

   
    //close(sockfd);
    //return 0;
    if( (sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0 )   //ipv4，字节流的方式创建socket套接字
    {
        perror("server socket failed!");
        exit(-1);

    }
    if( (ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr))) < 0)
    {
        perror("bind failed!");
        exit(-1);
    }    
    if( (ret = listen(sockfd,5)) < 0)
    {
        perror("listen failed!");
        exit(-1);
    }
    printf("waiting for connecting...\n");

    struct sockaddr_in clientaddr;  //创建一个储存客户端信息的结构体
    memset(&clientaddr,0,sizeof(clientaddr));

    socklen_t addrlen = sizeof(clientaddr);

    if( (clientfd = accept(sockfd,(struct sockaddr *)&clientaddr,&addrlen)) < 0)
    {
        perror("accept failed!");
        //fprintf(stderr,"accept error:%s\n",strerror(errno));
        exit(-1);
    }
    printf("accept successfully!\n");
    
    printf("connecting with:%s\n",inet_ntoa(clientaddr.sin_addr));
    //sleep(2);
    if( (ret = write(clientfd,"hello client!",14)) < 0 )
        perror("wirte failed");
    //sleep(2);

    // int fd = open("./a.txt",O_RDONLY);
    // if (fd < 0)
    // {
    //     perror("open failed!");
    // }
    
    close(sockfd);
    return 0;
}