#include <WinSock2.h>
#include <iostream>
#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData WasData;
	WSAStartup(MAKEWORD(2, 2), &WasData);
	// 1.winsock �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &WasData));
	{
		cout << "Winsock Error : " << GetLastError() << endl;
		exit(-1);
	}

	//2. �������� ����
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "SOCKET Error : " << GetLastError() << endl;
		exit(-1);
	}

	//3.IP, PORT �� ������ ���Ͽ� �Ҵ�
	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(50000);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
	cout << "Bind Error :  " << GetLastError() << endl;
	exit(-1);
	}

	//4. �����ؼ� Ŭ���̾�Ʈ�� ������ �ϼ�
	SOCKADDR_IN ClientAddr;
	int ClinteAddrSize = sizeof(ClientAddr);
	SOCKET ClientSocket;
	ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClinteAddrSize);
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "accept Error : " << GetLastError() << endl;
		exit(-1);
	}
	
	//5. Send
	char Buffer[] = "Hellow World";
	recv(ClientSocket, Buffer, 1024, 0);
	send(ClientSocket, Buffer, strlen(Buffer) + 1, 0);
	cout << "client send : " << Buffer << endl;

	//6. ��������
	closesocket(ClientSocket);
	closesocket(ServerSocket);

	//7. Winsock ����
	WSACleanup();
	
	return 0;
}