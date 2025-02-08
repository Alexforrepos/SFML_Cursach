#pragma once

class Game_Proc
{
	friend class Game;

	bool isrun;
public:

	Game_Proc()
		:isrun(false)
	{

	}

	bool GetIsRun() { return isrun; };

	void Run();
	void Close();
	void Start();
};