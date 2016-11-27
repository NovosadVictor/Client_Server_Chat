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
	char buf[MAXSIZE];
	memset(buf, 0, MAXSIZE);
	std::string name;
        std::cout << "   Your name: ";
        getline(std::cin, name);
        name += ": ";
	int My_Sock;
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
	if (connect(My_Sock, (sockaddr*)&myaddr, addrlen) == -1) {
		std::cout << "\nInCorrect connection\n" << std::endl;
		return -1;
	}
	send(My_Sock, &name[0], name.size() - 2, 0);
	int  otherNameLen;
	const std::string now = "Now online";
	if (recv(My_Sock, buf, MAXSIZE, 0) > 0) {
                        std::cout << buf << std::endl;
			otherNameLen = strlen(buf) - name.size() - now.size();
                        memset(buf, 0, MAXSIZE);
                }
	while(true) {
		std::string _name = name;
		std::string s;
		if (getline(std::cin, s)) {
			name += s;
			send(My_Sock, &name[0], name.size(), 0);
			name = _name;
		}
		if (recv(My_Sock, buf, MAXSIZE, 0) > otherNameLen) {
                	std::cout << buf << std::endl;
			memset(buf, 0, MAXSIZE);
		}
	}
	close(My_Sock);
	return 0;
} 
