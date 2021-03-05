#include <vector>
#include <list>
#include <LeapC.h>

class HoppingWindow
{
public:
	HoppingWindow(const int& t) :num_timeStep(t) {}
	void AddFrame(const LEAP_HAND& frame);
	void flush();
	bool isFull();
	const std::list<LEAP_HAND>& getWindow();
private:
	int num_timeStep;
	std::list<LEAP_HAND>  window;
};