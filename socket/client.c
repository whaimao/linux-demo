#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>

int main()
{
	char ch = 'A';
    /* 创建一个socket */
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    
    /* 链接至服务端 */
    int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    if(result == -1)
    {
        perror("connect failed: ");
        exit(1);
    }
    
    /* 数据处理 */
    write(sockfd, &ch, 1);//一个int 4个字节
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
	/* 关闭socket */
    close(sockfd);
	exit(0);    
}  
