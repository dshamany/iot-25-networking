idf_component_register(
    SRCS "non-volatile-storage.cpp"

    PRIV_REQUIRES nvs_flash
    INCLUDE_DIRS "."
)