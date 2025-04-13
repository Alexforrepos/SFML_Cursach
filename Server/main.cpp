#include "./Program/Program.h"
#include <iostream>

int main() 
{
    Program p;
	while (p.isRun())
	{
		p.run();
	}
    return 0;
}