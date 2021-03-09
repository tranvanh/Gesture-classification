#include "geastureLeap.h"


void GestureLeap::processWindow() {
	auto window_data = window.getWindow();
	std::vector<double> normalized_data(model.getNumFeatures() * model.getTimeStep(), 0);
	dataNormalization.scale(window.getWindow(), normalized_data);
	int res = model.predict(normalized_data);

	if (res > 5 && !dynamicGesture)
	{
		dynamicGesture = true;
		switch (res)
		{
		case 6:
			printf("predicted Gesture: %d PINCH\n", res);
			break;
		case 7:
			printf("predicted Gesture: %d RIGHT\n", res);
			break;
		case 8:
			printf("predicted Gesture: %d LEFT\n", res);
			break;
		case 9:
			printf("predicted Gesture: %d UP\n", res);
			break;
		case 10:
			printf("predicted Gesture: %d DOWN\n", res);
			break;
		default:
			break;

		}
	}
	
	if (res == 2)
	{
		dynamicGesture = false;
	}
	if (!dynamicGesture)
	{
		printf("predicted Gesture: %d\n", res);

	}

}

/** Callback for when a frame of tracking data is available. */
void GestureLeap::OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId) {
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

