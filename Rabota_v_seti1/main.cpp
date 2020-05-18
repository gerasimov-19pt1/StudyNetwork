// Алгоритм работы сетевого клиента
//  Шаг                     Действия                                Функции/тип
//  1   Подготовить адресные структуры (свою и удаленного сервера)  stuct sockaddr_in
//      формата IPv4                                                htons(),htonl()
//  2   Создать сокет для IPv4                                      socket()
//  3   Привязать сокет к своему адресу                             bind()
//  4   Установить сосединение с сервером                           connect()
//  5   Выполнить информационный обмен                              send(),recv()
//  6   Закрыть сокет                                               close()
//
//  Создание клиента для доступа к службе daytime (порт 13, адрес 82.179.90.12)-
//      возврат времени на присланный пакет данных (запрос) по протоколу TCP
//
//  Отладка с помощью утилиты nc -kl 44214

#include <iostream>
#include <cstdlib> // exit() - стандартные функции Си
#include <cstring> // strcpy(), strlen() - строки Си
#include <unistd.h> // close() - стандартные функции Unix
#include <netinet/in.h> //sockaddr_in и include <sys/socket/h>
#include <arpa/inet.h> // inet_addr()



void errHandler(const char * why, const int exitCode = 1)
{
	std::cerr << why << std::endl;
	exit(exitCode);
}

int main(int argc,char **argv)
{
	// подготовить структуру с адресом нашей программы (клиента)
	sockaddr_in * selfAddr = new (sockaddr_in);
	selfAddr->sin_family = AF_INET; // интернет протокол IPv4
	selfAddr->sin_port = 0;         // любой порт на усмотрение ОС
	selfAddr->sin_addr.s_addr = 0;  //все адреса нашего компа

	// подготовить структуру с адресом "на той стороне" (сервера)
	sockaddr_in * remoteAddr = new (sockaddr_in);
	remoteAddr->sin_family = AF_INET; // интернет протокола IPv4
	remoteAddr->sin_port = htons(13); // порт 13
	remoteAddr->sin_addr.s_addr = inet_addr("82.179.90.12"); //локальный адрес 82.179.90.12


	// подготовить буфер для передачи и приема данных
	char *buf = new char[256];
	strcpy(buf,"Привет, Геркулес! Сколько сейчас времени?\n");   //копируем строку
	int msgLen = strlen(buf);           //вычисляем длину строки

	// создать сокет
	int mySocket =socket(AF_INET, SOCK_STREAM, 0); // TCP
	if (mySocket == -1) {
		errHandler("Error open socket", 11);
	}

	// связать сокет с адресом
	int rc = bind(mySocket, (const sockaddr*) selfAddr, sizeof (sockaddr_in));
	if (rc == -1) {
		close(mySocket);
		errHandler("Error bind socket with local address",12);
	}

	// установить соединение
	rc = connect(mySocket, (const sockaddr*) remoteAddr, sizeof(sockaddr_in));
	if (rc == -1) {
		close(mySocket);
		errHandler("Error connect socket with remote server",13);
	}

	// передать данные
	rc = send(mySocket, buf,msgLen, 0);
	if (rc == -1) {
		close(mySocket);
		errHandler("Error send message", 14);
	}
	std::cout << "We send: " << buf << std::endl;

	// принять ответ
	rc = recv(mySocket, buf, 256, 0);
	if (rc == -1) {
		close(mySocket);
		errHandler("Error recevie answer", 15);
	}
	buf[rc] = '\0';
	std::cout<< "We receive from Gerkyles: " << buf << std::endl;

	// закрыть сокет
	close(mySocket);

	delete selfAddr;
	delete remoteAddr;
	delete[] buf;
	return 0;
}
