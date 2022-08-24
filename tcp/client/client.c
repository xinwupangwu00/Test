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

#define SERVER_PORT (8000)
#define SERVER_IP ("192.168.92.129")
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
    int ret = 0; 
    struct sockaddr_in server_addr;
    char recvBuf[20] = {0};
    memset(&server_addr,0,sizeof(server_addr));

    server_addr.sin_family = AF_INET;      //ipv4协议族
    server_addr.sin_port = htons(SERVER_PORT);     //端口号转装换为网络字节序
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);   //将字符串转装换为网络字节序
    bzero(&server_addr.sin_zero,8);

   
    
    if( (sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0 )   //ipv4，字节流的方式创建socket套接字
    {
        perror("client socket failed\n");
        exit(-1);
    }
    
    if( (ret = connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))) < 0)
    {
        perror("client connect failed\n");
        exit(-1);
    }
    printf("client connect successfully!\n");
    if ((ret = read(sockfd,recvBuf,sizeof(recvBuf))) < 0)
        perror("read failed");
    printf("receve :%s\n",recvBuf);
    //sleep(2);

    close(sockfd);
    return 0;
}