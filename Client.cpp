#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>

//Client

const int MAXSIZE = 1024;


int main() {
	int My_Sock;
	int Serv_Sock;
	My_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (My_Sock < 0) {
		std::cout << "Error in create my_sock\n" << std::endl;
		return -1;
	}
	sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8000);
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//91.218.85.246");
	unsigned int addrlen = sizeof(myaddr);
	if (connect(My_Sock, (sockaddr*)&myaddr, addrlen) == -1) {// пытаюсь подключиться, к верхнему ip не подключается(это ip сейчас моего компа)
		std::cout << "\nINCorrect connection\n" << std::endl;
		return -1;
	}
	char buf[MAXSIZE];
	while(true) {// тут даже без цикла не работает, поидее я там пытаюсь отправить одно сообщение но тут в консоле оно не пишет его
		recv(My_Sock, buf, sizeof(buf), 0);// поидее принимаю данные от соккета, пробовал read, тоже самое
		std::cout << buf << std::endl;
//		send(Serv_Sock, &name[0], name.size(), 0);
		memset(buf, 0, strlen(buf));
	}
	close(My_Sock);
	close(Serv_Sock);
	return 0;
} 
