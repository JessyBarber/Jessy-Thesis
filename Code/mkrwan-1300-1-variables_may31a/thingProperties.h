// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>


const char THING_ID[] = "09f4b4cd-c539-49df-9701-d4c915b536ae";

const char APPEUI[]   = SECRET_APP_EUI;
const char APPKEY[]   = SECRET_APP_KEY;


float dev1_cloud_avg_max_accel_x;
float dev1_cloud_avg_max_accel_y;
float dev1_cloud_avg_max_accel_z;
float dev1_cloud_avg_max_freq_x;
float dev1_cloud_avg_max_freq_y;
float dev1_cloud_avg_max_freq_z;

void initProperties(){
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(dev1_cloud_avg_max_accel_x, 1,
  READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(dev1_cloud_avg_max_accel_y, 2,
  READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(dev1_cloud_avg_max_accel_z, 4,
  READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(dev1_cloud_avg_max_freq_x, 5, 
  READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(dev1_cloud_avg_max_freq_y, 7, 
  READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(dev1_cloud_avg_max_freq_z, 8, 
  READ, ON_CHANGE, NULL);

}

LoRaConnectionHandler ArduinoIoTPreferredConnection(APPEUI, APPKEY, _lora_band::AU915, "ff000001f000ffff00020000");
