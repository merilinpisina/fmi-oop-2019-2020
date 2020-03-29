#ifndef CLOCK_H
#define CLOCK_H

const int MAX_MINUTES = 60;
const int MAX_SECONDS = 60;
const int MAX_HOURS = 24;

class Clock
{
public:
	Clock();
	Clock(int, int, int);

	int getHours()const;
	void setHours(int);

	int getMinutes()const;
	void setMinutes(int);

	int getSeconds()const;
	void setSeconds(int);

	void printTime()const;

	void nextTick();

	void sync();

	void operator+(int);



	//Clock(const Clock&);
	//Clock& operator=(const Clock&);
	//~Clock();

private:
	int hours;
	int minutes;
	int seconds;
};

#endif