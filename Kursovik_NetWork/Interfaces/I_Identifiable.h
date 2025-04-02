#pragma once
#define VOID_ID 0


class I_Identifiable
{
	static unsigned long long last_id;	
public:
	static unsigned long long generateID() 
	{
		last_id += 1;
		return last_id; 
	}
	virtual unsigned long long getId() { return 0; };
};