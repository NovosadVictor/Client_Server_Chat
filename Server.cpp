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
	std::string buf;
	int MySock;// дискриптор сокета или как-то так
	MySock = socket(AF_INET, SOCK_STREAM, 0);// создание сокета
	if (MySock < 0) {
		std::cout << "Error Mysocket\n " << std::endl;
		return -1;
	}
	sockaddr_in my_addr;// структура с адрессом
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8000);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(MySock, (sockaddr*)&my_addr, sizeof(my_addr)) != 0) {// связываем сокт с нашим адресом
		std::cout << "\nError bind mysocket\n" << std::endl;	
		return -1;
	}
	if (listen(MySock, 2) != 0) {// готовим к входящим
		std::cout << "\nError listen mysocket\n" << std::endl;
		return -1;
	}
	std::cout << "Your name: ";// ну типа имя в чате и всякое такое
	getline(std::cin, buf);// само имя
	buf += ':';// так красивее
	int ClientSock;// сокет, который будет джать 
	ClientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (ClientSock < 0) {
		std::cout << "\nError clientsock\n" << std::endl;
		return -1;
	}
	sockaddr_in client_addr;
	unsigned int addrsize = sizeof(client_addr);
	ClientSock = accept(MySock, (sockaddr*)&client_addr, &addrsize);// жду подключения
	if (ClientSock < 0) {
		std::cout << "\nError accept clientsock\n" << std::endl;
		return -1;
	}
	while(true) {
		size_t length = buf.size();// дальше тут просто махинации со строками, чтобы в строке всегда оставалось имя клиента а дальше через двоеточие сообщение и осле отправки сообщения в нашей строке остается только имя
		std::string n = buf;
		std::string s;
		char buffer[MAXSIZE];
		std::cout << buf << ":::Please write your massege" << std::endl;
		getline(std::cin, s);
		if (s == "PAUSE") {
			std::cout << "Correct End connection" << std::endl;
			break;
		}
		buf += s;	
	//	if (recv(Client_Sock_r, buffer, sizeof(buffer), 0) > 0)
	//		std::cout << buffer << std::endl;
		send(ClientSock, &buf[0], buf.size(), 0);// отправка сообщения
		buf = n;
//		shutdown(ClientSock, 2);// с этим пока не особо разобрался , но единственное , что понял, что с этой штукой сайт 127.0.0.1:8000  как бы показывает сообщение, иначе можно бесконечно вводить и только при завершении программы покажется сообщение, но это тоже не важно
	}
	close(ClientSock);
	close(MySock);
	std::cout << "end Connecting" << std::endl; 
	return 0;
}
