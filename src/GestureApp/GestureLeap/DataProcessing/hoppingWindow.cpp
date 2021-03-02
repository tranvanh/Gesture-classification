#include "hoppingWindow.h"

void HoppingWindow::AddFrame(const LEAP_TRACKING_EVENT* frame) {

	if (this->window.size() == num_timeStep) {
		this->window.pop_front();
		this->window.push_back(frame);
	}
	else
		this->window.push_back(frame);
}

void HoppingWindow::flush() { window.clear(); }

bool HoppingWindow::isFull() { return window.size() == num_timeStep; }

const std::list<const LEAP_TRACKING_EVENT*>& HoppingWindow::getWindow() { return this->window; }