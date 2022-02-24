#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSAData wsaData;

	//1.winsock �ʱ�ȭ, �����츸 �մϴ�. linux, unix���� ������� �ʾƿ�.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsock Error : " << GetLastError() <<  endl;
		exit(-1);
	}

	//2.create socket
	SOCKET ServerSocket;

	ServerSocket = socket(
		AF_INET,
		SOCK_STREAM,
		0
	);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	//2. ip, port�� �Ҵ��ؼ� �����̶� ����
	SOCKADDR_IN ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(50000);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "bind Error : " << GetLastError() << endl;
		exit(-1);
	}

	//3. Ŭ���̾�Ʈ ������ ��ٷ���.
	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "listen Error : " << GetLastError() << endl;
		exit(-1);
	}

	//4. �����ؼ� Ŭ���̾�Ʈ�� ������ �ϼ�
	SOCKADDR_IN ClientAddr;
	int ClinetAddrSize = sizeof(ClientAddr);
	SOCKET ClientSocket = 0;
	ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClinetAddrSize);
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "accept Error : " << GetLastError() << endl;
		exit(-1);
	}

	//5. ������ �ڷḦ Ŭ���̾�Ʈ����
	char Message[] = "Hello World"; //'\0'
	send(ClientSocket, Message, strlen(Message) + 1, 0);

	//6. ���� ����
	closesocket(ClientSocket);
	closesocket(ServerSocket);

	//7.Winsock ����, �����츸 �մϴ�.
	WSACleanup();

	return 0;
}