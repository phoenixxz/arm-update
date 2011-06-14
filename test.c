#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int fd;
unsigned char send_buf[50];
int main()
{
    fd=open("/home/xxz/111.tar.gz",O_RDONLY,0);
	printf("%d+++++++++\n",fd);
    int k;
    read(fd,send_buf,50);

    
	printf("%d===\n",k);
   
}
