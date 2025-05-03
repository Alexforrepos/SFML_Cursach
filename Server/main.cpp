#include "./Program/Program.h"
#include <iostream>

int main() 
{
    ServerProgram::Program p;
	while (p.isRun())
	{
		p.run();
	}
    return 0;
}