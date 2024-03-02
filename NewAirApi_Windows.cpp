#include "NewAirAPI_Windows.h"
#include "device3.h"
#include <mutex>
#include <iostream>
#include "device4.h"
#include "deps/Fusion/Fusion/FusionOffset.h"
using namespace std;

device3_quat_type orientation;
device3_vec3_type euler;
std::mutex mtx2;

void track(uint64_t timestamp,
	device3_event_type event,
	const device3_ahrs_type* ahrs) {
	/*device3_quat_type orientation;
	device3_vec3_type euler;*/

	//cout << "Got event";
	switch (event) {
	case DEVICE3_EVENT_INIT:
		//printf("Initialized\n");
		//cout << " DEVICE3_EVENT_INIT\r\n";
		break;
	case DEVICE3_EVENT_UPDATE:
		//cout << " DEVICE3_EVENT_UPDATE\r\n";
		mtx2.lock();
		orientation = device3_get_orientation(ahrs);
		euler = device3_get_euler(orientation);
		//cout << " euler: " << euler.x << "," << euler.y << "," << euler.z << "\r\n";
		mtx2.unlock();
		//printf("Pitch: %.2f; Roll: %.2f; Yaw: %.2f\n", euler.x, euler.y, euler.z);
		break;
	default:
		break;
	}
}

void device4Track(uint64_t timestamp,
	device4_event_type event,
	uint8_t brightness,
	const char* msg) {
	/*switch (event) {
	case DEVICE4_EVENT_MESSAGE:
		printf("Message: `%s`\n", msg);
		break;
	case DEVICE4_EVENT_BRIGHTNESS_UP:
		printf("Increase Brightness: %u\n", brightness);
		break;
	case DEVICE4_EVENT_BRIGHTNESS_DOWN:
		printf("Decrease Brightness: %u\n", brightness);
		break;
	default:
		break;
	}*/
}


device3_type dev3;
device4_type dev4;

int StartConnection_New()
{
	cout << "Starting Connection\r\n";
	auto device3res = device3_open(&dev3, track);

	if (DEVICE3_ERROR_NO_ERROR != device3res) {
		cout << "Error device3: " << device3res << "\r\n";
		return 0;
	}
	device3_clear(&dev3);

	return 1;
}

int StartConroller_New()
{
	cout << "Init Conroller" << endl;
	auto device4res = device4_open(&dev4, device4Track);
	if (DEVICE4_ERROR_NO_ERROR != device4res) {
		cout << "Error device4: " << device4res << "\r\n";
		return 0;
	}
	device4_clear(&dev4);
	return 1;
}

int DeviceRead_New()
{
	return device3_read(&dev3, -1);
	//while (true) {
	//	if (DEVICE3_ERROR_NO_ERROR != )
	//	{
	//		break;
	//	}

	//	//if (DEVICE4_ERROR_NO_ERROR == device4_read(&dev4, -1))
	//	//{
	//	//	break;
	//	//}
	//}
}
//
bool SwitchToSBS_New(short displayMode) {
	return device4_SwitchToSBS(&dev4, displayMode);
	/*if (!send_payload_action(device, DEVICE4_MSG_R_DISP_MODE, 0, NULL)) {
		device4_error("Requesting display mode failed");
		return DEVICE4_ERROR_PAYLOAD_FAILED;
	}

	if (!recv_payload_msg(device, DEVICE4_MSG_R_DISP_MODE, 1, &device->disp_mode)) {
		device4_error("Receiving display mode failed");
		return DEVICE4_ERROR_PAYLOAD_FAILED;
	}*/
}

//int GetDispMode_New() {
//	return dev4.disp_mode;
//	/*if (!send_payload_action(device, DEVICE4_MSG_R_DISP_MODE, 0, NULL)) {
//		device4_error("Requesting display mode failed");
//		return DEVICE4_ERROR_PAYLOAD_FAILED;
//	}
//
//	if (!recv_payload_msg(device, DEVICE4_MSG_R_DISP_MODE, 1, &device->disp_mode)) {
//		device4_error("Receiving display mode failed");
//		return DEVICE4_ERROR_PAYLOAD_FAILED;
//	}*/
//}


int StopConnection_New()
{
	device3_close(&dev3);

	return 1;
}

int StopController_New()
{
	device4_close(&dev4);

	return 1;
}

float* q2 = new float[4];
float* GetQuaternion_New()
{
	mtx2.lock();
	q2[0] = orientation.x;
	q2[1] = orientation.y;
	q2[2] = orientation.z;
	q2[3] = orientation.w;
	mtx2.unlock();
	return q2;
}

float* e2 = new float[3];

float* GetEuler_New()
{
	mtx2.lock();
	e2[0] = euler.x;
	e2[1] = euler.y;
	e2[2] = euler.z;
	mtx2.unlock();
	return e2;
	//mtx.lock();
	//e[0] = euler.angle.pitch;
	//e[1] = euler.angle.roll;
	//e[2] = euler.angle.yaw;
	//mtx.unlock();
	//return e;
}

float* gyroVector = new float[3];
float* GetGyroOffset_New() {
	if (dev3.offset) {
		gyroVector = ((FusionOffset*)dev3.offset)->gyroscopeOffset.array;
		return gyroVector;
	}

	return NULL;
}

int SaveGyroOffset_New(const char* path) {
	
	if (!dev3.offset) {
		return DEVICE3_ERROR_NO_ALLOCATION;
	}

#pragma warning(suppress : 4996)
	FILE* file = fopen(path, "wb");
	if (!file) {

		return DEVICE3_ERROR_FILE_NOT_OPEN;
	}

	device3_error_type result = DEVICE3_ERROR_NO_ERROR;

	size_t count;
	count = fwrite(dev3.offset, 1, sizeof(FusionOffset), file);

	if (sizeof(FusionOffset) != count) {
		result = DEVICE3_ERROR_SAVING_FAILED;
	}

	if (0 != fclose(file)) {
		return DEVICE3_ERROR_FILE_NOT_CLOSED;
	}

	return result;
}

int LoadGyroOffset_New(const char* path) {

	if (!dev3.offset) {
		return DEVICE3_ERROR_NO_ALLOCATION;
	}

#pragma warning(suppress : 4996)
	FILE* file = fopen(path, "rb");
	if (!file) {

		return DEVICE3_ERROR_FILE_NOT_OPEN;
	}

	device3_error_type result = DEVICE3_ERROR_NO_ERROR;

	size_t count;
	count = fread(dev3.offset, 1, sizeof(FusionOffset), file);

	if (sizeof(FusionOffset) != count) {
		result = DEVICE3_ERROR_LOADING_FAILED;
	}

	if (0 != fclose(file)) {
		return DEVICE3_ERROR_FILE_NOT_CLOSED;
	}

	return result;
}
