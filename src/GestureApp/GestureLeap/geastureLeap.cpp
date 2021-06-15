#include "geastureLeap.h"


void GestureLeap::processWindow() {
	int res = gesturePrediction.predict(window.getWindow());
	if (res < 0)
		return;

	if (res > 5)
	{
		switch (res)
		{
		case 7:
			printf("predicted Gesture: %d LEFT\n", res);
			window.flush();
			break;
		case 6:
			printf("predicted Gesture: %d RIGHT\n", res);
			window.flush();
			break;
		default:
			break;
		}
	}

	else
		printf("predicted Gesture: %d\n", res);


}

void GestureLeap::OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId, void* context) {
	if (frame->nHands == 0) {
		if (!window.isEmpty())
			processWindow();
		window.flush();
		return;
	}

	LEAP_HAND hand = frame->pHands[0];

	window.AddFrame(hand);
	if (window.isFull())
		processWindow();
}

