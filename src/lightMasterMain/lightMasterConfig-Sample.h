//Holds the values for SSID, SSID password, application secret, and any other data that needs to be secured.
//Be sure to remove '-Sample' from the file name.

#ifndef lightMasterConfig_h
#define lightMasterConfig_h

#include <Arduino.h>

#define SSID "" //wifi SSID
#define SSID_PASSWORD "" //wifi password
#define AUTH_TOKEN "" //lifx auth token
#define HOST "api.lifx.com"
#define SSL_PORT 443
#define LIFXSELECTOR "" //selector value for lifx calls

#endif