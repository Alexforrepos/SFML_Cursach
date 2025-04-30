#pragma once
#define VOID_ID 0


class I_Identifiable
{
	static unsigned long long last_id;	
public:
	/// <summary>
	/// для создания нового id 
	/// используется для создания уникальных новых объектов 
	/// 
	/// !!! важно что создавая новый объекты даже с конструктором копирования id может быть пропущен
	/// </summary>
	/// <returns></returns>
	static unsigned long long generateID() 
	{
		last_id += 1;
		return last_id; 
	}
	virtual unsigned long long getId() { return 0; };
	
};

