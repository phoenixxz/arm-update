/*该文件为hosten.c*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netdb.h>
#include<sys/socket.h>
int main(int argc,char *argv[])
{
    struct hostent *h;
    if(argc!=2){
	fprintf(stderr,"用法:.o文件 域名\n");
	exit(1);
    }
    if((h=gethostbyname(argv[1]))==NULL){
	herror("请输入用户域名！\n");
	exit(1);
    }
    //printf("规范名：%s\n",h->h_name);
    printf("IP地址：%s\n",inet_ntoa(*((struct in_addr*)(h->h_addr))) );
    return 0;
}


