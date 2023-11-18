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

extern "C" AIR_API int DeviceRead_New();

extern "C" AIR_API float* GetGyroOffset_New();

extern "C" AIR_API int LoadGyroOffset_New(const char* path);

extern "C" AIR_API int SaveGyroOffset_New(const char* path);
//extern "C" AIR_API bool SwitchToSBS_New();
//
//extern "C" AIR_API int GetDispMode_New();

//Function to get brightness
//extern "C" AIR_API int GetBrightness();