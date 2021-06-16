#include "SlidingWindow.h"

void SlidingWindow::AddFrame(const LEAP_HAND& frame) {

	if (this->window.size() == num_timeStep) {
		this->window.pop_front();
		this->window.push_back(frame);
	}
	else
		this->window.push_back(frame);
}

void SlidingWindow::flush() { window.clear(); }

bool SlidingWindow::isFull() { return window.size() == num_timeStep; }

bool SlidingWindow::isEmpty() { return window.empty(); }

const std::list<LEAP_HAND>& SlidingWindow::getWindow() { return this->window; }