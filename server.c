#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<pthread.h>

#define PORTUDP 9999
#define PORT 9992
#define BACKLOG 1
unsigned char file_buff[50000];
int fd,fd1;
pthread_t id_udp_send,id_tcp_recv;
void *thread_udp_send();
void *thread_tcp_recv(void *arg);
void *ret_pthread;

int i=0;
int k=0;
int test;
int accept_fds[100];
char recv_buff[50];
int main()
{
    
    int listenfd,connectfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sin_size;
    int c;
   // char recv_buff[50];
    int recv_cnt;
    
    /*******init fds[]***************************************/
    int j;
    for(j=0;j<100;j++);
    *(accept_fds+j)=1;
    
    /**********************************************/
    
    if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
	perror("creat socket erro\n");
    printf("listenfd is %d\n",listenfd);

    bzero(&server,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);

    //int b=bind(listenfd,(struct sockaddr *)&server,sizeof(struct sockaddr));
    int b=bind(listenfd,(struct sockaddr *)&server,sizeof(struct sockaddr));
    printf("bind %d\n",b);
    if((c=listen(listenfd,10))<0)
	perror("listen error\n");
    printf(" listen %d\n",c);
    pthread_create(&id_udp_send,NULL,(void *)thread_udp_send,NULL);
    sleep(1);
   // return 0;
    

    sin_size=sizeof(struct sockaddr);
   // while(1)
    //{

//	if((connectfd=accept(listenfd,(struct sockaddr *)&client,(socklen_t *)&sin_size))==-1)
	//perror("accept error\n");
	/*****************start to send file**********************/
	fd=open("/home/xxz/",O_RDONLY,0);
	fd1=open("/home/xxz/pppd",O_RDWR|O_CREAT|O_APPEND,0);

	//int k;	
//	k=read(fd,file_buff,50000);
	//printf("%d\n",write(fd1,file_buff,k));


/*TCP*/
    while(1)
    {
	
	//if((connectfd=accept(listenfd,(struct sockaddr *)&client,(socklen_t *)&sin_size))==-1)
//	printf("now accepting................................\n");
	if((accept_fds[i]=accept(listenfd,(struct sockaddr *)&client,(socklen_t *)&sin_size))==-1)
	{
	    perror("accept error\n");
	    exit(0);
	}
//	printf("have acceptted ,accept_fds[%d] is %d\n\n",i,accept_fds[i]);
	//if((recv_cnt=read(connectfd,recv_buff,50,0))>0)

	    //pthread_create(&id_tcp_recv,NULL,(void *)thread_tcp_recv,NULL);
	k=i;
	    pthread_create(&id_tcp_recv,NULL,(void *)thread_tcp_recv,(void *)&k);
	i++;
	
//	printf("Main:have creat thread++++++++++++++++++++++++++++++++\n");
	//write(fd1,recv_buff,recv_cnt);
	//if(recv_cnt==0)
	//    exit(0);
    }
	//recv_cnt=recv(connectfd,recv_buff,sizeof(recv_buff),0);
	printf("receive %d \n",recv_cnt);
	printf("receive %s \n",recv_buff);
	bzero(recv_buff,sizeof(recv_buff));
	recv_cnt=0;
   // }
}
void *thread_udp_send()
{
    struct sockaddr_in udp_to_addr;
    int udp_sock;
    char udp_send_buff[6]="hello";
    int so_broadcast=1;

    printf("this is thread_udp_send\n");
    bzero(&udp_to_addr,sizeof(struct sockaddr_in));
    udp_to_addr.sin_family=AF_INET;
    udp_to_addr.sin_port=htons(PORTUDP);
    //udp_to_addr.sin_addr.s_addr=inet_addr("210.77.19.99");
    udp_to_addr.sin_addr.s_addr=inet_addr("210.77.19.255");
    //addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);
    udp_sock=socket(AF_INET,SOCK_DGRAM,0);

    if (setsockopt(udp_sock,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast))<0)
    {
	perror("Broadcast UDP set socket error");
	close(udp_sock);
    }


    while(1)
    {
	int t;
	t=sendto(udp_sock,udp_send_buff,strlen(udp_send_buff),0,(struct sockaddr *)&udp_to_addr,sizeof(struct sockaddr_in));
	printf("t is %d\n",t);
	sleep(3);
    }
}
void *thread_tcp_recv(void *arg)
{
    int temp=*(int *)arg;
    pthread_detach(pthread_self());
    static int a=0;
    char recv_buff[100];
    int count=0;
    //    printf("Thread{%d}:this is thread,begin reading acceptfds[%d].......................\n",temp,temp);
    count=read(accept_fds[(*(int *)arg)],recv_buff,50);
    printf("Thread{%d}:have read %d ,%s\n",temp,count,recv_buff);
    //printf("this is %d ,%d end\n",accept_fds[k],k);
    // close(accept_fds[k]);
    pthread_exit(ret_pthread);
}

