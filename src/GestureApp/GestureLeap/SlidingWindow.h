#include <vector>
#include <list>
#include <LeapC.h>

class SlidingWindow
{
public:
	SlidingWindow() {}
	SlidingWindow(const int& t, const int& r) :num_timeStep(t), rate(r) { if (rate > t) throw "Rate must be lower than number of timesteps"; }
	void AddFrame(const LEAP_HAND& frame);
	void flush();
	void slide();
	bool isFull();
	bool isEmpty();
	const std::list<LEAP_HAND>& getWindow();
private:
	int num_timeStep;
	int rate;
	std::list<LEAP_HAND>  window;
};