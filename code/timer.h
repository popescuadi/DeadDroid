#pragma once
# include <iostream>
# include <ctime>
class timer
{
public:
	timer();
	void set_clock(int seconds);
	bool wait();
	~timer();
private:
	bool on = false;
	clock_t endwait;
};

