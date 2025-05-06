#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "Room.h"
#include <memory>


#define ALL_ROOM_FLAG 0

class RoomManager
{
	std::vector<std::shared_ptr<Room>> Rooms;

public:

	uint8_t GenrateNewRoom()
	{
		auto newRoom = std::make_shared<Room>();
		Rooms.push_back(newRoom);
		return newRoom->getId();
		
	};
	void clear()
	{
		close();
	};

	void sendMsg(std::string msg, uint16_t roomId = ALL_ROOM_FLAG);;

	void close(uint8_t roomId = ALL_ROOM_FLAG);

	uint8_t totalCount() const { return Rooms.size(); }

	~RoomManager()
	{

	}

	std::shared_ptr<Room>& operator[](uint8_t index)
	{
		if (Rooms.size() >= index)
			throw std::out_of_range("index of room out of range");
		return Rooms[index];
	}
};