#include "esphome.h"


using namespace esphome;

#define DELAY_MS 30000 // Delay in miliseconds between window checks, give it some time

// AXA REMOTE 2.0 return strings

// 200 OK                    -> OPEN / CLOSE
// 210 Unlocked              -> STATUS
// 211 Strong Locked         -> STATUS
// 260 AXA RV2900 2.0        -> DEVICE
// 261 Firmware v1.20 2012   -> FIRMWARE
// 502 Command not implemented

#define AXA_OPENED 210 // 210 Unlocked
#define AXA_CLOSED 211 // 211 Strong Locked


class CustomAXA2RemoteUART : public Component, public UARTDevice {
  protected:
    unsigned long lastread;
    char buff[30];
    int i,dummy;
    int axa_status;
 public:
  CustomAXA2RemoteUART(UARTComponent *parent) : UARTDevice(parent) {}
  Sensor *axa_window = new Sensor();
  void setup() override {
    lastread = 0;
    ESP_LOGCONFIG("espaxa", "Setting up AXA UART...");
  }
 
  void loop() override {
    unsigned long now = millis();
	
	  if (now - lastread > DELAY_MS || lastread == 0) {
		  lastread = now;
    while (available()) { // empty UART input buffer
        dummy=read();
    }
    write_str("\r\n");  // send dummy character
    delay(100);
    write_str("STATUS\r\n");  // ask status
    delay(100);
    if (available() )
    {
      i=0;
      while (available()) {
        buff[i++]=read(); // get return string
      }
      buff[i]=0;
      axa_status=100*(buff[0]-'0')+10*(buff[1]-'0')+(buff[2]-'0');  // calculate status code from first three digits
      i=i-2;
      buff[i]=0; // remove 0D 0A linebreak
      ESP_LOGD("espaxa", "%s-> %d", buff,axa_status);
      if (axa_status==AXA_CLOSED)
      {
        axa_window->publish_state(COVER_CLOSED); // only AXA_CLOSED will return CLOSED
      }
      else if (axa_status==AXA_OPENED)
      {
        axa_window->publish_state(COVER_OPEN);  // only AXA_OPENED will return OPEN
      }
      // no messages will be published on any other state (ie. 502 Command not implemented)
    }
    }
  }
};
