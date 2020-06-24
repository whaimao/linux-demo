#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    /* 断开之前的socket文件 ,为服务器创建一个未命名得套接字*/
    unlink("server_socket");    
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
   
   // 命名套接字
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    /* 与本地文件进行绑定 */
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	// 创建一个连接队列，开始等待客户端得连接
    int ret = listen(server_sockfd, 5);
	printf("ret : %d\n", ret);
    
    while(1)
    {
    	char ch;
		printf("server waitting\n");
		// 接受一个连接
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        // 对client_sockfd 套接字上的客户端进行读写操作
		read(client_sockfd, &ch, 1);
		ch++;
		write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
    
}

