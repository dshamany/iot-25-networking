#include "mqtt-publisher.h"
#include "mqtt_client.h"
#include "esp_log.h"

static const char *TAG = "MqttPublisher";

MqttPublisher::MqttPublisher(const char* broker_uri) : _broker_uri(broker_uri), _client(nullptr), _connected(false) {}

bool MqttPublisher::start()
{
    if(_client != nullptr)
    {
        ESP_LOGW(TAG, "MQTT client has already been initialized");
        return false;
    }
    esp_mqtt_client_config_t config = {};
    config.broker.address.uri = _broker_uri;

    _client = esp_mqtt_client_init(&config);

    if(_client == nullptr)
    {
        ESP_LOGE(TAG, "Failed to initialize MQTT client");
        return false;
    }

    esp_err_t result = esp_mqtt_client_register_event(_client, MQTT_EVENT_ANY, eventHandler, this);

    if(result != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to register MQTT event handler");
        return false;
    }
    result = esp_mqtt_client_start(_client);
    if (result != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to start MQTT client");
        return false;
    }
    return true;
}

bool MqttPublisher::publish(const char* topic, const char* message)
{
    if(!_connected)
    {
        ESP_LOGW(TAG, "Publishing failed, MQTT not connected");
        return false;
    }
    int message_id = esp_mqtt_client_publish(_client, topic, message, 0, 1, 0);
    if(message_id < 0)
    {
        ESP_LOGE(TAG, "Failed to publish message");
        return false;
    }
    ESP_LOGI(TAG, "Published message with id %d", message_id);
    return true;
}


void MqttPublisher::eventHandler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    MqttPublisher* publisher = static_cast<MqttPublisher*>(arg);
    switch(event_id)
    {
        case MQTT_EVENT_CONNECTED:
        {
            publisher->_connected = true;
            ESP_LOGI(TAG, "Connected to MQTT broker");
            break;
        }
        
        case MQTT_EVENT_DISCONNECTED:
        {
            publisher->_connected = false;
            ESP_LOGW(TAG, "Disconnected from MQTT broker");
            break;
        }
        case MQTT_EVENT_ERROR:
        {
            ESP_LOGE(TAG, "MQTT error");
            break;
        }
        default: break;
    }
}


