# CatchTheStick
Small "Catch the Stick" Game - Based on ESP8266 and PCF8574 IO Expanders to Control 12 Magnets


# Required Modifications for IoTWebConf

To prevent the need for an Admin Password the following lines in IoTWebConf need to me removed manually bevore build:

```
if (this->_apPassword[0] == '\0')
{
    page += F("You must change the default AP password to continue. Return "
            "to <a href=''>configuration page</a>.");
}
else if (this->_wifiParameters._wifiSsid[0] == '\0')
{
    page += F("You must provide the local wifi settings to continue. Return "
            "to <a href=''>configuration page</a>.");
}
else if (this->_state == NotConfigured)
{
    page += F("Please disconnect from WiFi AP to continue!");
}
else
{
    page += F("Return to <a href='/'>home page</a>.");
}*/
```