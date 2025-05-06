#include "Room.h"

uint8_t Room::nextId = 1;
uint8_t Room::ProcessInfo::nextId = 1;

void Room::Pipe::start()
{
	pipe = CreateNamedPipeW(LPCWSTR(pipeName.c_str()),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		1,
		4096, 4096,
		0,
		nullptr);
	if (pipe == INVALID_HANDLE_VALUE)
		throw std::	runtime_error("Creating Pipe Err(" + std::to_string(GetLastError()) + ")\n");
}
