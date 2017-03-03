#include "timer.h"



timer::timer()
{
	on = false;
}
void timer::set_clock(int seconds)
{
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	on = true;
}
bool timer::wait()
{
	if (on = true)
	{
		if (clock() < endwait)
		{
			
			return true;
		}
		else
		{
			on = false;
			return false;
		}
	}
	else
		return false;
}
timer::~timer()
{
}
