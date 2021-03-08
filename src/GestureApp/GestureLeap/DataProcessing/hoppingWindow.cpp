#include "hoppingWindow.h"

void HoppingWindow::AddFrame(const LEAP_HAND& frame) {

	if (this->window.size() == num_timeStep) {
		this->window.pop_front();
		this->window.push_back(frame);
	}
	else
		this->window.push_back(frame);
}

void HoppingWindow::flush() { window.clear(); }

bool HoppingWindow::isFull() { return window.size() == num_timeStep; }

bool HoppingWindow::isEmpty() { return window.empty(); }

const std::list<LEAP_HAND>& HoppingWindow::getWindow() { return this->window; }