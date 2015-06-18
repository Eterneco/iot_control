#ifndef __NETWORK_H
#define __NETWORK_H

#include "typeDefs.h"


#define AP_SSID_LEN_MAX         (33)
#define ROLE_INVALID            (-5)


// Application specific status/error codes
typedef enum{
    // Choosing -0x7D0 to avoid overlap w/ host-driver's error codes
    LAN_CONNECTION_FAILED = -0x7D0,
    INTERNET_CONNECTION_FAILED = LAN_CONNECTION_FAILED - 1,
    DEVICE_NOT_IN_STATION_MODE = INTERNET_CONNECTION_FAILED - 1,

    STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;


extern  void InitializeAppVariables();
extern  long ConfigureSimpleLinkToDefaultState();
extern  long ConnectToNetwork();
extern  void ReadDeviceConfiguration();

#endif
