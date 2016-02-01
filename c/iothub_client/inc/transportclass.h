#ifndef transportclass_h
#define transportclass_h

#include "transport2.h"
#include "macro_utils.h"

#include "iothub_client.h"

#include "device.h"

#include "doublylinkedlist.h"

/*error codes returned by SUBSCRIBE*/

#define SUBSCRIBE_RESULT_VALUES \
SUBSCRIBE_OK, \
SUBSCRIBE_ERROR

DEFINE_ENUM(SUBSCRIBE_RESULT, SUBSCRIBE_RESULT_VALUES)

typedef void(*CALLBACK)(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback);

/*produces a TRANSPORT2_HANDLE*/
typedef TRANSPORT2_HANDLE (*pfTransportCreate)(const char* iotHubName, const char* iotHubSuffix, const char* protocolGatewayHostName);

/*destroys a created transport*/
typedef void (*pfTransportDestroy)(TRANSPORT2_HANDLE handle);

/*registers a device with the transport*/
typedef DEVICE_HANDLE (*pfTransportRegisterDevice)(TRANSPORT2_HANDLE handle, const char* deviceName, const char* deviceKey, PDLIST_ENTRY waitingToSend); /*so transport is a factory for devices :)*/

/*unregisters a device from its transport*/
typedef void(*pfTransportUnregisterDevice)(DEVICE_HANDLE deviceHandle);

/*dowork*/
typedef void (*pfTransportDoWork)(DEVICE_HANDLE deviceHandle);

/*subscribes to receive stuff*/
typedef SUBSCRIBE_RESULT (*pfTransportSubscribe)(DEVICE_HANDLE deviceHandle, IOTHUB_CLIENT_MESSAGE_CALLBACK_ASYNC callback, void* context);

/*stops receiving stuff*/
typedef void (*pfTransportUnsubscribe)(DEVICE_HANDLE deviceHandle);

typedef struct TRANSPORT_CLASS_TAG
{
    pfTransportCreate transportCreate;
    pfTransportDestroy transportDestroy;

    pfTransportRegisterDevice registerDevice;
    pfTransportUnregisterDevice unregisterDevice;

    pfTransportDoWork doWork;

    pfTransportSubscribe subscribe;
    pfTransportUnsubscribe unsubscribe;

}TRANSPORT_CLASS;

typedef const TRANSPORT_CLASS* (*getClass)(void); /*needed to be implemented by every implementation*/

#endif /*transportclass_h*/

