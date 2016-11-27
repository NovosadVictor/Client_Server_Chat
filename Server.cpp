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

//server

const int MAXSIZE = 1024;


int main() {
	char buf[MAXSIZE];
	std::string online = "   Now online: ";
	memset(buf, 0, MAXSIZE);
	int MySock;
	MySock = socket(AF_INET, SOCK_STREAM, 0);
	if (MySock < 0) {
		std::cout << "Error My_1sock\n " << std::endl;
		return -1;
	}
	sockaddr_in my_addr;
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8000);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(MySock, (sockaddr*)&my_addr, sizeof(my_addr)) != 0) {
		std::cout << "\nError bind my_1socket\n" << std::endl;	
		return -1;
	}
	if (listen(MySock, 2) != 0) {
		std::cout << "\nError listen mysocket\n" << std::endl;
		return -1;
	}
	int ClientSock_1;
	int ClientSock_2;
	ClientSock_1 = socket(AF_INET, SOCK_STREAM, 0);
	if (ClientSock_1 < 0) {
		std::cout << "\nError client_1_sock\n" << std::endl;
		return -1;
	}
	ClientSock_2 = socket(AF_INET, SOCK_STREAM, 0);
        if (ClientSock_2 < 0) {
                std::cout << "\nError client_2_sock\n" << std::endl;
                return -1;
        }
	sockaddr_in client_addr;
	unsigned int addrsize = sizeof(client_addr);
	ClientSock_1 = accept(MySock, (sockaddr*)&client_addr, &addrsize);
	if (ClientSock_1 < 0) {
		std::cout << "\nError accept client_1_sock\n" << std::endl;
		return -1;
	}
	recv(ClientSock_1, buf, MAXSIZE, 0);
	std::cout << "Client 1"
  		<< ":"
		<< buf
		<< " Connected\n" << std::endl;
	online += buf;
	online += " and ";
	memset(buf, 0, MAXSIZE);
	ClientSock_2 = accept(MySock, (sockaddr*)&client_addr, &addrsize);
	if (ClientSock_2 < 0) {
                std::cout << "\nError accept client_2_sock\n" << std::endl;
                return -1;
        }
	recv(ClientSock_2, buf, MAXSIZE, 0);
	std::cout << "Client 2"
  		<< ":"
		<< buf
		<< " Connected\n" << std::endl;
	online += buf;
	memset(buf, 0, MAXSIZE);
	char buf1[MAXSIZE];
	memset(buf1, 0, MAXSIZE);
	char buf2[MAXSIZE];
	memset(buf2, 0, MAXSIZE);
	send(ClientSock_1, &online[0], online.size(), 0);
	send(ClientSock_2, &online[0], online.size(), 0);
	while(true) {
		if (recv(ClientSock_1, buf1, MAXSIZE, 0) > 0) {
			send(ClientSock_2, buf1, strlen(buf1), 0);
			memset(buf1, 0, MAXSIZE);
		}
		if (recv(ClientSock_2, buf2, MAXSIZE, 0) > 0) {
			send(ClientSock_1, buf2, strlen(buf2), 0);
			memset(buf2, 0, MAXSIZE);
		}
	}
	close(ClientSock_1);
	close(ClientSock_2);
	close(MySock);
	std::cout << "End Connecting..." << std::endl; 
	return 0;
}
