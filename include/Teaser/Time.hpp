
#ifndef TEASER_TIME_HPP
#define TEASER_TIME_HPP

#include <Teaser/Common.hpp>

#include <string>

namespace Teaser
{

class Time
{
public:
	Time();
	~Time();

	long long lastFrame;

	// Put this in the gameloop
	void update();

	std::string deltaTimeToString() const;

	enum Timeformat
	{
		SECONDS,
		MILLISECONDS,
		MICROSECONDS,
		NANOSECONDS
	};

	static long long getCurrentTime(Timeformat tf);
	// Returns date as string yyyy/mm/dd
	static std::string getDateAsString();
	// Returns time as string hh:mm:ss
	static std::string getTimeAsString();

	inline unsigned int getFPS() const
	{
		return fps;
	}

	inline double getDeltaTime() const
	{
		return deltaTime;
	}

private:
	double deltaTime;

	bool firstTime;

	double secondTimer;
	unsigned int frameCounter;
	unsigned int fps;
};

class Stopwatch
{

public:
	Stopwatch();
	virtual ~Stopwatch();

	void start();
	void end();
	void reset();

	unsigned int getElapsedMilliseconds()const;

	std::string toString() const;

private:
	unsigned int elapsedMilliseconds;
	unsigned int startMilliseconds;
};

std::ostream& operator <<(std::ostream& stream, const Stopwatch& sw);

} // namespace Teaser

#endif // TEASER_TIME_HPP
