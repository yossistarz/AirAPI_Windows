
#include "utils.h"
#include "deps/hidapi-win/include/hidapi.h"

uint16_t getConnectedProductId() {
	struct hid_device_info* airDevice = hid_enumerate(AIR_VID, AIR_PID);
	struct hid_device_info* air2Device = hid_enumerate(AIR_VID, AIR_2_PID);
	struct hid_device_info* air2proDevice = hid_enumerate(AIR_VID, AIR_2_PRO_PID);

	if (airDevice != NULL) {
		hid_free_enumeration(airDevice);
		return AIR_PID;
	}
	else if (air2Device != NULL) {
		hid_free_enumeration(air2Device);
		return AIR_PID;
	}
	else if (air2proDevice != NULL) {
		hid_free_enumeration(air2proDevice);
		return AIR_PID;
	}

	return NULL;
}