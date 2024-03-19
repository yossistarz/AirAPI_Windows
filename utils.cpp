
#include "utils.h"
#include "deps/hidapi-win/include/hidapi.h"
#include <iostream>

uint16_t getConnectedProductId() {
	struct hid_device_info* airDevice = hid_enumerate(AIR_VID, AIR_PID);
	struct hid_device_info* air2Device = hid_enumerate(AIR_VID, AIR_2_PID);
	struct hid_device_info* air2proDevice = hid_enumerate(AIR_VID, AIR_2_PRO_PID);

	if (airDevice != NULL) {
		std::cout << "Air Device" << std::endl;
		hid_free_enumeration(airDevice);
		return AIR_PID;
	}
	else if (air2Device != NULL) {
		std::cout << "Air2 Device" << std::endl;

		hid_free_enumeration(air2Device);
		return AIR_2_PID;
	}
	else if (air2proDevice != NULL) {
		std::cout << "Air2 pro Device" << std::endl;
		hid_free_enumeration(air2proDevice);
		return AIR_2_PRO_PID;
	}

	return NULL;
}