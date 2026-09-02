idf_component_register(
    SRCS "wifi.cpp"
    REQUIRES esp_wifi non-volatile-storage
    INCLUDE_DIRS "." 
)