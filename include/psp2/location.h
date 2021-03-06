﻿/**
* \file location.h
* \brief Header file which defines location related variables and functions
*
* Copyright (C) 2016 Vitasdk developers
*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef _PSP2_LOCATION_H_
#define _PSP2_LOCATION_H_

#include <stdint.h>
#include <psp2/types.h>
#include <psp2/rtc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_LOCATION_DATA_INVALID (-9999.0)

/** Location error codes */
enum {
	SCE_LOCATION_SUCCESS                            = 0,

	SCE_LOCATION_INFO_UNDETERMINED_LOCATION         = -2146430464,
	SCE_LOCATION_INFO_INSUFFICIENT_INFORMATION      = -2146430463,
	SCE_LOCATION_INFO_GET_LOCATION_CANCELED         = -2146430462,
	SCE_LOCATION_INFO_DENIED_BY_USER                = -2146430461,

	SCE_LOCATION_ERROR_INVALID_ADDRESS              = -2146430400,
	SCE_LOCATION_ERROR_INVALID_HANDLE               = -2146430399,
	SCE_LOCATION_ERROR_NO_MEMORY                    = -2146430398,
	SCE_LOCATION_ERROR_TOO_MANY_HANDLES             = -2146430397,
	SCE_LOCATION_ERROR_INVALID_LOCATION_METHOD      = -2146430396,
	SCE_LOCATION_ERROR_INVALID_HEADING_METHOD       = -2146430395,
	SCE_LOCATION_ERROR_MULTIPLE_CALLBACK            = -2146430394,
	SCE_LOCATION_ERROR_NOT_RUNNING_CALLBACK         = -2146430393,
	SCE_LOCATION_ERROR_DIALOG_RESULT_NONE           = -2146430392,
	SCE_LOCATION_ERROR_DISABLE_APPLICATION          = -2146430391,
	SCE_LOCATION_ERROR_MULTIPLE_CONFIRM             = -2146430390,

	SCE_LOCATION_ERROR_UNAUTHORIZED                 = -2146430336,
	SCE_LOCATION_ERROR_PROVIDER_UNAVAILABLE         = -2146430335,
	SCE_LOCATION_ERROR_FILE_IO                      = -2146430334,
	SCE_LOCATION_ERROR_INVALID_FILE_FORMAT          = -2146430333,
	SCE_LOCATION_ERROR_TIME_OUT                     = -2146430332,
	SCE_LOCATION_ERROR_NO_SERVER_MEMORY             = -2146430331,
	SCE_LOCATION_ERROR_INVALID_TITLE_ID             = -2146430330,
	SCE_LOCATION_ERROR_FATAL_ERROR                  = -2146430209
};

//TO DO: further comment each struct and function (i.e. parameters)

/** Location handle datatype */
typedef SceUInt8 SceLocationHandle;

/** Usage permission dialog display status */
typedef enum {
	SCE_LOCATION_DIALOG_STATUS_IDLE     = 0, //!< Dialog initial idle status
	SCE_LOCATION_DIALOG_STATUS_RUNNING  = 1, //!< Dialog running
	SCE_LOCATION_DIALOG_STATUS_FINISHED = 2  //!< Dialog operation finished
} SceLocationDialogStatus;

/** Usage permission dialog result */
typedef enum {
	SCE_LOCATION_DIALOG_RESULT_NONE    = 0, //!< Result is not stored
	SCE_LOCATION_DIALOG_RESULT_DISABLE = 1, //!< Negative result is stored
	SCE_LOCATION_DIALOG_RESULT_ENABLE  = 2  //!< Positive result is stored
} SceLocationDialogResult;

/** location usage permission status for individual application */
typedef enum SceLocationPermissionApplicationStatus
{
	SCE_LOCATION_PERMISSION_APPLICATION_NONE = 0,  //!< liblocation not used
	SCE_LOCATION_PERMISSION_APPLICATION_INIT = 1,  //!< liblocation not accessed
	SCE_LOCATION_PERMISSION_APPLICATION_DENY = 2,  //!< liblocation access denied status
	SCE_LOCATION_PERMISSION_APPLICATION_ALLOW = 3  //!< liblocation access allowed status
} SceLocationPermissionApplicationStatus;

/** location usage permission status */
typedef enum SceLocationPermissionStatus
{
	SCE_LOCATION_PERMISSION_DENY = 0,  //!< liblocation access denied status
	SCE_LOCATION_PERMISSION_ALLOW = 1  //!< liblocation access allowed status
} SceLocationPermissionStatus;

/** Location measurement method */
typedef enum SceLocationLocationMethod
{
	SCE_LOCATION_LMETHOD_NONE = 0,                  //!< Do not perform location measurement
	SCE_LOCATION_LMETHOD_AGPS_AND_3G_AND_WIFI = 1,  //!< Perform measurement by switching between AGPS, Wi-Fi, and 3G
	SCE_LOCATION_LMETHOD_GPS_AND_WIFI = 2,          //!< Perform measurement by switching between GPS and Wi-Fi
	SCE_LOCATION_LMETHOD_WIFI = 3,                  //!< Use only Wi-Fi
	SCE_LOCATION_LMETHOD_3G = 4,                    //!< Use only 3G
	SCE_LOCATION_LMETHOD_GPS = 5                    //!< Use only GPS
}SceLocationLocationMethod;

/** Direction measurement method */
typedef enum SceLocationHeadingMethod
{
	SCE_LOCATION_HMETHOD_NONE = 0,          //!< Don't perform heading measurement
	SCE_LOCATION_HMETHOD_AUTO = 1,          //!< Automatically determine hold orientation and outputs its value
	SCE_LOCATION_HMETHOD_VERTICAL = 2,      //!< Output value in vertical hold reference system
	SCE_LOCATION_HMETHOD_HORIZONTAL = 3,    //!< Output value in horizontal hold reference system
	SCE_LOCATION_HMETHOD_CAMERA = 4         //!< Output value in camera axis reference system
} SceLocationHeadingMethod;

/** Structure of location information */
typedef struct SceLocationLocationInfo
{
	SceDouble64 latitude;   //!< Latitude (deg). Valid range: -90 to + 90. If cannot be obtained, SCE_LOCATION_DATA_INVALID
	SceDouble64 longitude;  //!< Longitude (deg). Valid range: -180 to +180. If cannot be obtained, SCE_LOCATION_DATA_INVALID
	SceDouble64 altitude;   //!< Altitude (m). If cannot be obtained, SCE_LOCATION_DATA_INVALID
	SceFloat32 accuracy;    //!< Horizontal error (m). If cannot be obtained, SCE_LOCATION_DATA_INVALID
	SceFloat32 reserve;     //!< Reserve
	SceFloat32 direction;   //!< Travel direction. If cannot be obtained, SCE_LOCATION_DATA_INVALID
	SceFloat32 speed;       //!< Travel speed (m/s). If cannot be obtained, SCE_LOCATION_DATA_INVALID
	SceRtcTick timestamp;   //!< Time of data acquisition, in μsec (UTC)
} SceLocationLocationInfo;


/** Structure of heading information */
typedef struct SceLocationHeadingInfo
{
	SceFloat32 trueHeading;     //!< Clockwise angle from true north (0 to 360 degrees). If cannot be acquired, SCE_LOCATION_INVALID_DATA
	SceFloat32 headingVectorX;  //!< Direction vector X coordinates element of true north. If cannot be acquired, SCE_LOCATION_INVALID_DATA
	SceFloat32 headingVectorY;  //!< Direction vector Y coordinates element of true north. If cannot be acquired, SCE_LOCATION_INVALID_DATA
	SceFloat32 headingVectorZ;  //!< Direction vector Z coordinates element of true north. If cannot be acquired, SCE_LOCATION_INVALID_DATA
	SceFloat32 reserve;         //!< Reserve
	SceFloat32 reserve2;        //!< Reserve
	SceRtcTick timestamp;       //!< Time acquired in unit of 1 usec (UTC)
} SceLocationHeadingInfo;

/** Location information callback notification function */
typedef void(*SceLocationLocationInfoCallback)(SceInt32 result, SceLocationHandle handle, const SceLocationLocationInfo *location, void *userdata);

/** Callback notification function for direction information */
typedef void(*SceLocationHeadingInfoCallback)(SceInt32 result, SceLocationHandle handle, const SceLocationHeadingInfo *heading, void *userdata);

/** Location information acquisition permission information */
typedef struct SceLocationPermissionInfo {
	SceLocationPermissionStatus parentalstatus;                //!< Status of usage permission through parental control
	SceLocationPermissionStatus mainstatus;                    //!< Status of usage permission through location data item of system settings
	SceLocationPermissionApplicationStatus applicationstatus;  //!< Status of usage permission through location data item for each application in system settings
} SceLocationPermissionInfo;

/** Functions */
/** Library start */
SceInt32 sceLocationOpen(SceLocationHandle *handle, SceLocationLocationMethod locateMethod, SceLocationHeadingMethod headingMethod);

/** Close library */
SceInt32 sceLocationClose(SceLocationHandle handle);

/** Reopen library */
SceInt32 sceLocationReopen(SceLocationHandle handle, SceLocationLocationMethod locateMethod, SceLocationHeadingMethod headingMethod);

/** Get location measurement method */
SceInt32 sceLocationGetMethod(SceLocationHandle handle, SceLocationLocationMethod *locateMethod, SceLocationHeadingMethod *headingMethod);

/** Get location information */
SceInt32 sceLocationGetLocation(SceLocationHandle handle, SceLocationLocationInfo *locationInfo);

/** Cancel location information acquisition operation */
SceInt32 sceLocationCancelGetLocation(SceLocationHandle handle);

/** Start continuous acquisition of location information */
SceInt32 sceLocationStartLocationCallback(SceLocationHandle handle, SceUInt32 distance, SceLocationLocationInfoCallback callback, void *userdata);

/** Stop continuous acquisition of location information */
SceInt32 sceLocationStopLocationCallback(SceLocationHandle handle);

/** Get direction information */
SceInt32 sceLocationGetHeading(SceLocationHandle handle, SceLocationHeadingInfo *headingInfo);

/** Start continuous acquisition of direction information */
SceInt32 sceLocationStartHeadingCallback(SceLocationHandle handle, SceUInt32 difference, SceLocationHeadingInfoCallback callback, void *userdata);

/** Stop continuous acquisition of direction information */
SceInt32 sceLocationStopHeadingCallback(SceLocationHandle handle);

/** Allow acquisition of location information */
SceInt32 sceLocationConfirm(SceLocationHandle handle);

/** Get status of location information acquisition permission dialog */
SceInt32 sceLocationConfirmGetStatus(SceLocationHandle handle, SceLocationDialogStatus *status);

/** Get result of location information acquisition permission dialog */
SceInt32 sceLocationConfirmGetResult(SceLocationHandle handle, SceLocationDialogResult *result);

/** Abort location information acquisition permission dialog */
SceInt32 sceLocationConfirmAbort(SceLocationHandle handle);

/** Get location information acquisition permission/refusal information */
SceInt32 sceLocationGetPermission(SceLocationHandle handle, SceLocationPermissionInfo *info);

/** Get location information acquisition permission information */
SceInt32 sceLocationSetGpsEmulationFile(unsigned char *filename);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_LOCATION_H_ */
