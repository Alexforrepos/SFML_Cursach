#include "MSG_Manager.h"
using namespace std;

MSG_Manager* MSG_Manager::MSGM_ = nullptr;

void MSG_Manager::unique()
{

	for (int i = 0; i < msges[int(MSG_TYPE::MSG_TYPE_KILL)].size();i++)
	{
        auto& msg_list = msges[int(MSG_TYPE::MSG_TYPE_KILL)];

        for (size_t i = 0; i < msg_list.size(); ++i) {
            auto msg = msg_list[i];
            int count = std::count_if(msg_list.begin(), msg_list.end(),
                [&](MSG* arg) { return get<MSG_TYPE_KILL>(arg->MSG_TYPE) == get<MSG_TYPE_KILL>(msg->MSG_TYPE); });

            if (count > 1) {
               
                auto it = msg_list.begin();
                while (it != msg_list.end()) {
                    if (get<MSG_TYPE_KILL>((*it)->MSG_TYPE) == get<MSG_TYPE_KILL>(msg->MSG_TYPE) && (*it) != msg) {
                        cout << "delete not uniq msg with kill = " << get<MSG_TYPE_KILL>((*it)->MSG_TYPE).victim << endl;
                        delete* it; 
                        it = msg_list.erase(it); 
                    }
                    else {
                        ++it; 
                    }
                }
            }
        }
    }
}
