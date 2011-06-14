#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include<time.h>

#define SERVER_PORT 9999
#define MAX_BUF_SIZE 1024 

void udpc_requ(int sockfd,const struct sockaddr_in *addr,int len) 
{ 
    char buffer[MAX_BUF_SIZE]="hello,this is a test"; 
    char buffer1[MAX_BUF_SIZE]="world,......................."; 
    int n=1; 
    
    while(1) 
    {   
	n++;
	//printf("Please input char:\n");
	//fgets(buffer,MAX_BUF_SIZE,stdin); 
	if(n%2==0)
	sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)addr,len); 
	else
	sendto(sockfd,buffer1,strlen(buffer1),0,(struct sockaddr *)addr,len); 

	printf("have send ......\n");
	//bzero(buffer,MAX_BUF_SIZE); 
	sleep(1);
    } 
} 

int main(int argc,char **argv) 
{ 
    int sockfd; 
    int so_broadcast=1;
    struct sockaddr_in addr; 

    if(argc!=2) 
    { 
	fprintf(stderr,"Usage:%s server_ip\n",argv[0]); 
	//exit(1); 
    }

    sockfd=socket(AF_INET,SOCK_DGRAM,0); 
    if(sockfd<0) 
    { 
	fprintf(stderr,"Socket Error:%s\n",strerror(errno)); 
	exit(1); 
    } 
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &so_broadcast,
		sizeof(so_broadcast)) < 0)
    {
	perror("Broadcast UDP set socket error");
	close(sockfd);
    }

    bzero(&addr,sizeof(struct sockaddr_in)); 
    addr.sin_family=AF_INET; 
    addr.sin_port=htons(SERVER_PORT);
    //addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);
    addr.sin_addr.s_addr=inet_addr("210.77.19.95");
#if 0
    if(inet_aton(argv[1],&addr.sin_addr)<0){ 
	fprintf(stderr,"Ip error:%s\n",strerror(errno)); 
	exit(1); 
    } 
#endif
    udpc_requ(sockfd,&addr,sizeof(struct sockaddr_in));     
    close(sockfd); 
} 
