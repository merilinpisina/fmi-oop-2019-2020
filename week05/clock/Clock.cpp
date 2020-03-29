#include "Clock.h"

#include <iostream>
#include <time.h>


Clock::Clock() :hours(0), minutes(0), seconds(0) {}

Clock::Clock(int hours, int minutes, int seconds) {
	setHours(hours);
	setMinutes(minutes);
	setSeconds(seconds);
}

int Clock::getHours() const
{
	return hours;
}

void Clock::setHours(int hours) {
	if (hours >= 0 && hours <= MAX_HOURS) {
		this->hours = hours;
		return;
	}
	this->hours = 0;
}

int Clock::getMinutes() const
{
	return minutes;
}

void Clock::setMinutes(int minutes) {
	if (minutes >= 0 && minutes <= MAX_MINUTES) {
		this->minutes = minutes;
		return;
	}
	this->minutes = 0;
}

int Clock::getSeconds() const
{
	return seconds;
}

void Clock::setSeconds(int seconds) {
	if (seconds >= 0 && seconds <= MAX_SECONDS) {
		this->seconds = seconds;
		return;
	}
	this->seconds = 0;
}

void Clock::printTime() const
{
	std::cout << 
		"Time: " << 
		this->hours << 
		":" << 
		this->minutes << 
		":" << 
		this->seconds << 
		std::endl;
}

void Clock::nextTick() {
	++seconds;
	if (seconds > MAX_SECONDS) {
		seconds = 0;
		++minutes;
	}

	if (minutes > MAX_MINUTES) {
		minutes = 0;
		++hours;
	} 
	
	if (hours > MAX_HOURS) {
		hours = 0;
	}
}

void Clock::sync()
{
	time_t  currentTime;
	time(&currentTime);

	tm* timeInfo;
	timeInfo = localtime(&currentTime);

	setHours(timeInfo->tm_hour);
	setMinutes(timeInfo->tm_min);
	setSeconds(timeInfo->tm_sec);
}

void Clock::operator+(int seconds)
{
	this->seconds += seconds;
	if (this->seconds >= MAX_SECONDS) {
		int secondsLeft = this->seconds % MAX_SECONDS;
		int minutesPassed = this->seconds / MAX_SECONDS;
		
		this->seconds = secondsLeft;
		minutes += minutesPassed;
	}

	if (minutes >= MAX_MINUTES) {
		int minutesLeft = this->minutes % MAX_MINUTES;
		int hoursPassed = this->minutes / MAX_MINUTES;

		this->minutes = minutesLeft;
		hours += hoursPassed;
	}

	if (hours >= MAX_HOURS) {
		int hoursLeft = this->hours % MAX_HOURS;
		int hoursPassed = this->hours / MAX_HOURS;

		this->hours = hoursLeft;
	}
}


