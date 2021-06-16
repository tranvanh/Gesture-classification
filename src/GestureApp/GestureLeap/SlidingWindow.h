#include <vector>
#include <list>
#include <LeapC.h>

class SlidingWindow
{
public:
	SlidingWindow(const int& t) :num_timeStep(t) {}
	void AddFrame(const LEAP_HAND& frame);
	void flush();
	bool isFull();
	bool isEmpty();
	const std::list<LEAP_HAND>& getWindow();
private:
	int num_timeStep;
	std::list<LEAP_HAND>  window;
};