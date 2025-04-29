#pragma once
//#include <sstream>
#include <thread>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <windows.h>

#define ROOMSTATRPORT 54000
#define DEFAULT_PIPE_NAME "pipe_"
#define MAXBUFSIZE 100



class Room
{
	static unsigned lastPort;
	unsigned port;

	bool activeflag;
	HANDLE room_Pipe;
	
	void startProcess()
	{

	}


public:
	Room()
		:activeflag(true),port(++lastPort)
	{
		///�� ������ ������� ���� ��������� �����
		/*room_Pipe = CreateFile(
			LPWCH((std::string("./TMP/") + DEFAULT_PIPE_NAME + std::to_string(lastPort % 1000)).c_str()),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);*/ 
		room_Pipe = NULL;
		start();
	}
	void start()
	{
		if (room_Pipe != NULL)
			throw "ROOM Pipe Exeption";
		HANDLE hPipe = CreateNamedPipe(
			LPWCH((std::string("./TMP/") + DEFAULT_PIPE_NAME + std::to_string(lastPort % 1000)).c_str()),          // ��� ������
			PIPE_ACCESS_DUPLEX,             // ��������������� �����
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			1,                              // ����. ���������� �����������
			MAXBUFSIZE, MAXBUFSIZE,			// ������ ��������/��������� ������
			0,                              // ������� �� ���������
			NULL                            // �������� ������������
		);

	};
	void stop()
	{

	};
	void sendCommand();

	~Room()
	{

	}
public:
	enum class Command
	{
		STOP,EXIT,
	};
};