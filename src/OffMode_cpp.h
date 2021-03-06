#include "OffMode.h"

inline OffMode::OffMode(Gnulight &gnulight) :
		State(gnulight, " OffMode") {
}

inline bool OffMode::onEnterState() {
	Device().setState(OnOffState::OFF);
	return true;
}

inline void OffMode::onExitState() {
	Device().setState(OnOffState::ON);
}

inline bool OffMode::handleEvent(const ButtonEvent &event) {

	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
		case 2:
			Device().enterState(Device().constantLightMode, event);
			return true;
		case 3:
			Device().enterState(Device().strobeMode, event);
			return true;
		case 4:
			Device().enterState(Device().parameterCheckMode, MessageEvent(Device().parameterCheckMode.BATTERY_CHECK_MSG));
			return true;
		case 5:
			Device().enterState(Device().parameterCheckMode, MessageEvent(Device().parameterCheckMode.LAMP_TEMPERATURE_CHECK_MSG));
			return true;
		case 6:
			Device().lightnessDimmer.isLightnessSimulationEnabled(
					!Device().lightnessDimmer.isLightnessSimulationEnabled());
			return true;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		Device().enterState(Device().constantLightMode, event);
		return true;
	} else {
		return false;
	}
}
