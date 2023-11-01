#pragma once

#ifdef AIRAPI_EXPORTS
#define AIR_API __declspec(dllexport)
#else
#define AIR_API __declspec(dllimport)
#endif

//Function to start connection to Air
extern "C" AIR_API int StartConnection_New();

//Function to stop connection to Air
extern "C" AIR_API int StopConnection_New();

//Function to get quaternion
extern "C" AIR_API float* GetQuaternion_New();

//Function to get euler
extern "C" AIR_API float* GetEuler_New();

extern "C" AIR_API void DeviceRead_New();

//extern "C" AIR_API bool SwitchToSBS_New();
//
//extern "C" AIR_API int GetDispMode_New();

//Function to get brightness
//extern "C" AIR_API int GetBrightness();