#include "geastureLeap.h"


/** Callback for when a frame of tracking data is available. */
void GestureLeap::OnFrame(const LEAP_TRACKING_EVENT* frame, const unsigned deviceId) {
	if (frame->nHands == 0) {
		window.flush();
		return;
	}

	window.AddFrame(frame);
	if (window.isFull())
	{
		auto window_data = window.getWindow();
		std::vector<float> normalized_data(model.getNumFeatures() * model.getTimeStep());
		dataNormalization.scale(window.getWindow(), normalized_data);
		int res = model.predict(normalized_data);
		printf("predicted Gesture: %d\n", res);
	}

	//for (uint32_t h = 0; h < frame->nHands; h++) {

	//	LEAP_HAND* hand = &frame->pHands[h];
	//	printf("    TEST:%d Hand id %i from device %i is a %s hand with position (%f, %f, %f) with confidence %f.\n",
	//		model.getTimeStep(),
	//		hand->id,
	//		deviceId,
	//		(hand->type == eLeapHandType_Left ? "left" : "right"),
	//		hand->palm.position.x,
	//		hand->palm.position.y,
	//		hand->palm.position.z,
	//		hand->confidence);
	//}
}