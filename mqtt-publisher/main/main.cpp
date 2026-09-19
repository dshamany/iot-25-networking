

#include "wifi.h"
#include "mqtt-publisher.h"
#include <string>
extern "C" void app_main()
{
    Wifi wifi;
    wifi.init_sta();
    MqttPublisher mqtt("mqtt://172.16.216.222:1883");
    mqtt.start();
    vTaskDelay(pdMS_TO_TICKS(5000));
    for(int i = 0; i < 100; i++)
    {
        char digit = '0' + i;
        mqtt.publish("test/topic", &digit);
    }
}