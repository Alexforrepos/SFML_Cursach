#include "RoomManager.h"

void RoomManager::sendMsg(std::string msg, uint16_t roomId)
{
	if (roomId == ALL_ROOM_FLAG)
	{
		for (auto rms : Rooms)
			rms->sendMsg(msg);
		return;
	}


	auto tofind = std::find_if(Rooms.begin(), Rooms.end(), [&](std::shared_ptr<Room> a) {return a->getId() == roomId; });


	if (tofind == Rooms.end())
	{
		throw std::out_of_range("cdnt find room with this id");
	}

	(*tofind)->sendMsg(msg);
}

void RoomManager::close(uint8_t roomId)
{
	if (roomId == ALL_ROOM_FLAG)
	{
		Rooms.clear();
	}

	auto tofind = std::find_if(Rooms.begin(), Rooms.end(), [&](std::shared_ptr<Room> a) {return a->getId() == roomId; });


	if (tofind == Rooms.end())
	{
		throw std::out_of_range("cdnt find room with this id");
	}

	(*tofind)->close();

}
