#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

int main()
{
	// 1.winsock 초기화
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "WinSock Error : " << GetLastError() << endl;
		exit(-1);
	}
	
	//2. 리슨소켓 생성
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}
	
	//3.IP, PORT 를 생성한 소켓에 할당
	SOCKADDR_IN ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(5001);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "Bind Error : " << GetLastError() << endl;
		exit(-1);
	}
		
	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "Listen Error : " << GetLastError() << endl;
		exit(-1);
	}

	//4. 수락해서 클라이언트와 연결을 완성
	SOCKADDR_IN ClientAddr;

	int ClientAddrSize = sizeof(ClientAddr);
	SOCKET ClientSocket = 0;
	ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize);
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "Accept Error : " << GetLastError() << endl;
		exit(-1);
	}

	cout << "connect ip : " << inet_ntoa(ClientAddr.sin_addr) << endl;
	cout << "connect port : " << ntohs(ClientAddr.sin_port) << endl;

	//5. Send
	char Message[] = "show me the money.";
	send(ClientSocket, Message, strlen(Message) + 1, 0);
	
	cout << "Server send : " << Message << endl;

	char Recv[1024] = { 0, };
	recv(ClientSocket, Recv, 1024 - 1, 0);

	cout << "client sended : " << Recv << endl;
	//소켓 닫기
	closesocket(ClientSocket);
	closesocket(ServerSocket);

	//윈속 종료
	WSACleanup();
}