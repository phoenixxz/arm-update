#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int fd;
unsigned char send_buf[50]="Hello,world";
int main()
{
    int sockfd;
    unsigned short port;
    in_addr_t addr_in;
    struct sockaddr_in server;
    int len = 0;
    char recv_buf[1024];
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == sockfd)
    {
	perror("Failed to sockfd");
	return -1;
    }
    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(9992);
    server.sin_addr.s_addr = inet_addr("210.77.19.95");
    if(-1 == connect(sockfd,(struct sockaddr *)&server,sizeof(server)))
    {
	perror("Failed to connect");
	return -1;
    }
    memset(send_buf,0,sizeof(send_buf));
    sprintf(send_buf,"Hello!Server terminal 发送测试");

    fd=open("/usr/sbin/pppd",O_RDONLY,0);
    printf("%d+++++++++\n",fd);
    int k;

    //k=read(fd,send_buf,50);
    //printf("%d===\n",k);
    len = send(sockfd,send_buf,50,0);
//    close(sockfd);

    return 0;
    while(1)

    {
	k=read(fd,send_buf,50);
	printf("%d===\n",k);
	len = send(sockfd,send_buf,50,0);
	if(k==0)
	    exit(0);
	if(-1 ==len)
	{
	    perror("Failed to send");
	    return -1;
	}
	memset(recv_buf,0,sizeof(recv_buf));
    }
    printf("Now recv...\n");
#if 0
    len = recv(sockfd,recv_buf,sizeof(recv_buf),0);
    if(-1 == len)
    {
	perror("Failed to recv");
	return -1;
    }
    printf("Receive message:%s\n",recv_buf);
    close(sockfd);
#endif
    return 0;
}
