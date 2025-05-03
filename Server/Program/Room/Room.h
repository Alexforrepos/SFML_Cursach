#pragma once
//#include <sstream>
#include <stdexcept>
#include <thread>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <windows.h>

#define ROOMSTATRPORT 54000
#define DEFAULT_PIPE_NAME "pipe_"
#define MAXBUFSIZE 100


#define MAX_BUF_SIZE 4000


class Room
	:public std::enable_shared_from_this<Room>
{
	struct ProcessInfo
	{
	private:
		static uint8_t nextId;
		uint8_t id;


		//const LPSECURITY_ATTRIBUTES saProc{ sizeof(saProc), nullptr, TRUE }, saThread{ sizeof(saThread), nullptr, TRUE };

		const wchar_t* pathRoomExe = L"C:\\Users\\tvink\\source\\repos\\SFML_Cursach\\x64\\Debug\\RoomProcess.exe";

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

	public:
		bool exist;

		ProcessInfo()
			: id(nextId++), si({ sizeof(si) }), exist(true)
		{

			auto success = CreateProcessW(
				pathRoomExe,
				nullptr,
				nullptr, nullptr,
				FALSE,
				CREATE_NEW_CONSOLE,
				nullptr,
				nullptr,
				&si,
				&pi
			);

			if (!success)
			{

				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				throw std::runtime_error("Process creating err(" + std::to_string(GetLastError()) + ")\n");
			}
		}

		~ProcessInfo()
		{
			closeProcess();
		}

		uint8_t getId() { return id; };

		void closeProcess()
		{
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		};
	};

	struct Pipe
	{

	private:
		HANDLE pipe;
	public:
		bool exist;
		std::string pipeName;

		Pipe(uint8_t id)
			: pipeName(std::string("\\\\.\\pipe\\") + "pipe_" + std::to_string(id)), exist(true)
		{
			pipe = CreateNamedPipeW(LPCWSTR(pipeName.c_str()),
				PIPE_ACCESS_DUPLEX,
				PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
				1,
				4096, 4096,
				0,
				nullptr);
			if (pipe == INVALID_HANDLE_VALUE)
				throw std::runtime_error("Creating Pipe Err(" + std::to_string(GetLastError()) + ")\n");
		}

		void start();

		void closePipe()
		{
			DisconnectNamedPipe(pipe);
			CloseHandle(pipe);
		};

		void send(std::string& msg)
		{
			DWORD datav = msg.size();

			if (!WriteFile(pipe, pipeName.c_str(), datav, nullptr, nullptr)) throw "PIPE MSG SEND ERR";

		}
	};


private:

	static uint8_t nextId;
	uint8_t id;

	ProcessInfo pci;
	Pipe ppi;

private:


public:

	void sendMsg(std::string& msg)
	{
		ppi.send(msg);
	};

	uint8_t getId() { return id; }

	void close()
	{
		ppi.closePipe();
		pci.closeProcess();
	};

	Room()
		:id(nextId), ppi(nextId), pci()
	{
		nextId++;
	}

};