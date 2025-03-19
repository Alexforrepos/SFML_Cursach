#pragma once
	


/// <summary>
/// ����� ������� ������������� �� ������� �������
/// </summary>
class GameProcess
{
	bool isActive;


public:
	GameProcess()
		: isActive(false)
	{

	}
	
	/// <returns>���������� ��������� �����</returns>
	bool isRun() { return isActive; }

	/// <summary>
	/// �������� ���� �������� ���� 
	/// </summary>
	void start();


	/// <summary>
	/// ���������� ���� ����
	/// </summary>
	void run();


	/// <summary>
	/// �������� �������� �������� 
	/// </summary>
	void close();

};