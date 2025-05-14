#pragma once
#define VOID_ID 0


class I_Identifiable
{
	static unsigned long long last_id;	
public:
	/// <summary>
	/// ��� �������� ������ id 
	/// ������������ ��� �������� ���������� ����� �������� 
	/// 
	/// !!! ����� ��� �������� ����� ������� ���� � ������������� ����������� id ����� ���� ��������
	/// </summary>
	/// <returns></returns>
	static unsigned long long generateID() 
	{
		return ++last_id; 
	}
	virtual unsigned long long getId() { return 0; };
	
};

