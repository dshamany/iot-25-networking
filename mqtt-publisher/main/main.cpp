

#include "wifi.h"
#include "mqtt-publisher.h"

extern "C" void app_main()
{
    Wifi wifi;
    wifi.init_sta();
    MqttPublisher mqtt("mqtt://192.168.1.115:1883");
    mqtt.start();
    vTaskDelay(pdMS_TO_TICKS(5000));
    mqtt.publish("test/topic", "dude10");
}