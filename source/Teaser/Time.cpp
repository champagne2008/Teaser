#include "Time.h"

#include <iostream>
#include <chrono>
#include <Teaser/Time.hpp>
#include <SDL\SDL.h>

namespace Teaser
{

Time::Time()
: deltaTime(0.000001)
, lastFrame(0)
, firstTime(true)
, secondTimer(0.0)
,fps(0)
,frameCounter(0)
{
}

Time::~Time() {}

void Time::update()
{
	long thisFrame = getCurrentTime(Time::MICROSECONDS);

	if (firstTime)
	{
		deltaTime = 0.000001;
		firstTime = false;
	}
	else
	{
		deltaTime = (double)(thisFrame - lastFrame) / 1000000.00;
	}
	lastFrame = thisFrame;

	secondTimer += deltaTime;
	frameCounter++;

	if (secondTimer >= 1.0) 
	{
		fps = frameCounter;
		frameCounter = 0;
		secondTimer = 0.0;
	}
}

std::string Time::deltaTimeToString()const 
{
	return std::to_string(deltaTime);
}


long long Time::getCurrentTime(Timeformat tf)
{

	switch (tf)
	{

	case Time::SECONDS:
	{
		std::chrono::seconds s =
		    std::chrono::duration_cast<std::chrono::seconds>(
		        std::chrono::system_clock::now().time_since_epoch());
		return s.count();
		break;
	}

	case Time::MILLISECONDS:
	{
		std::chrono::milliseconds ms =
		    std::chrono::duration_cast<std::chrono::milliseconds>(
		        std::chrono::system_clock::now().time_since_epoch());
		return ms.count();
		break;
	}

	case Time::MICROSECONDS:
	{
		std::chrono::microseconds mcs =
		    std::chrono::duration_cast<std::chrono::microseconds>(
		        std::chrono::system_clock::now().time_since_epoch());
		return mcs.count();
		break;
	}

	case Time::NANOSECONDS:
	{
		std::chrono::nanoseconds ns =
		    std::chrono::duration_cast<std::chrono::nanoseconds>(
		        std::chrono::system_clock::now().time_since_epoch());
		return ns.count();
		break;
	}
	}
	return 0;
}

//--------------------------------------------------
//	Returns the current Date in Format yyyy/mm/dd
//--------------------------------------------------
std::string Time::getDateAsString()
{

	time_t t       = time(0);
	struct tm* now = new tm;
	localtime_s(now,&t);
	std::string date;

	unsigned int year  = (now->tm_year + 1900);
	unsigned int month = (now->tm_mon + 1);
	unsigned int day   = now->tm_mday;

	date = std::to_string(year) + "/" + ((month < 10) ? "0" : "") +
	       std::to_string(month) + "/" + ((day < 10) ? "0" : "") +
	       std::to_string(day);

	delete now;

	return date;
}

//--------------------------------------------------
//	Returns the current Time in Format hh::mm::ss
//--------------------------------------------------
std::string Time::getTimeAsString()
{

	time_t t       = time(0);
	struct tm* now = new tm;
	localtime_s(now,&t);
	std::string time;

	unsigned int hour   = now->tm_hour;
	unsigned int min    = now->tm_min;
	unsigned int second = now->tm_sec;

	time = ((hour < 10) ? "0" : "") + std::to_string(hour) + ":" +
	       ((min < 10) ? "0" : "") + std::to_string(min) + ":" +
	       ((second < 10) ? "0" : "") + std::to_string(second);

	delete now;
	return time;
}

Stopwatch::Stopwatch() {}

Stopwatch::~Stopwatch() {}

void Stopwatch::start() { startMilliseconds = SDL_GetTicks(); }

void Stopwatch::end()
{
	elapsedMilliseconds = SDL_GetTicks() - startMilliseconds;
}

void Stopwatch::reset()
{
	elapsedMilliseconds = SDL_GetTicks() - startMilliseconds;
	startMilliseconds   = SDL_GetTicks();
}

unsigned int Stopwatch::getElapsedMilliseconds() const 
{
	return SDL_GetTicks() - startMilliseconds;
}

std::string Stopwatch::toString() const 
{
	return std::to_string(getElapsedMilliseconds());
}


std::ostream& operator <<(std::ostream& stream, const Stopwatch& sw) 
{
	stream << sw.toString();
	return stream;
}

} // namespace Teaser
