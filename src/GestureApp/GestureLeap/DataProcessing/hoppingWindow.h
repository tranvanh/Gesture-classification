#include <vector>
#include <list>
#include <LeapC.h>

class HoppingWindow
{
public:
	HoppingWindow(const int& t) :num_timeStep(t) {}
	void AddFrame(const LEAP_TRACKING_EVENT* frame);
	void flush();
	bool isFull();
	const std::list<const LEAP_TRACKING_EVENT*>& getWindow();
private:
	int num_timeStep;
	std::list<const LEAP_TRACKING_EVENT*>  window;
};