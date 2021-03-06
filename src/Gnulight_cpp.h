#include "Gnulight.h"

inline Gnulight::Gnulight(GnulightLightDriver &lightDriver, const char *name) :
		GenericDevice(&offMode, name), lightDriver(lightDriver) {
	lightDriver.maxBrightnessSetter = new GradualCappablePotentiometerActuator(
			DELAY_BETWEEN_LEVEL_CHANGE, taskManager, lightDriver);
}

inline void Gnulight::onSetup() {
	enterState(offMode);
}

inline void Gnulight::setState(OnOffState state) {
	powerState = state;

	if (state == OnOffState::ON) {
		logger.debug("onSwitch%s", "On");
		onSwitchOn();

		if (pBatteryMonitor != nullptr) {
			taskManager.StartTask(pBatteryMonitor);
		}

		if (pTempMonitor != nullptr) {
			taskManager.StartTask(pTempMonitor);
		}
	} else {
		if (pBatteryMonitor != nullptr) {
			taskManager.StopTask(pBatteryMonitor);
		}

		if (pTempMonitor != nullptr) {
			taskManager.StopTask(pTempMonitor);
		}

		lightnessDimmer.setState(OnOffState::OFF);

		logger.debug("onSwitch%s", "Off");
		onSwitchOff();
	}
}

inline OnOffState Gnulight::getState() {
	return powerState;
}

inline void Gnulight::onSwitchOn() {

}

inline void Gnulight::onSwitchOff() {

}
