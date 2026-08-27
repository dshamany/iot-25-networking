# mqtt-publisher

ESP32 firmware (ESP-IDF, C++) that reads sensor data and will publish it to an
MQTT broker. It currently provides:

- `main/sensor.h` / `main/sensor.cpp` — the `Sensor` struct: takes readings,
  and formats them as human-readable type/unit strings or a CSV row.
- `utils/timestamp.h` / `utils/timestamp.cpp` — converts a `time_t` to an
  ISO 8601 UTC string, used by `Sensor::to_csv_row()`.
- `main/mqtt-publisher.cpp` — the `app_main` entry point (Wi-Fi/MQTT wiring
  goes here).

## Prerequisites

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
  v5.3, targeting the `esp32` chip (see `sdkconfig`).
- An ESP32 dev board connected over USB.

## Building and flashing

From the `mqtt-publisher/` directory:

```sh
# Source the ESP-IDF environment (once per shell session)
. $HOME/.esp-idf/export.sh

# Build
idf.py build

# Flash and view logs (replace PORT, e.g. /dev/ttyUSB0)
idf.py -p PORT flash monitor
```

`idf.py monitor` streams the device's serial output; press `Ctrl+]` to exit.
If you only want to flash without monitoring, drop `monitor` from the command.

## Running the unit tests

Unit tests (`tests/sensor_unittest.cpp`, using GoogleTest) build and run
**on your host machine**, independently of the ESP-IDF/xtensa toolchain —
they exercise `Sensor` and the timestamp helper as plain C++.

Requires CMake >= 3.16, a C++17 host compiler, and GoogleTest (e.g. the
`gtest`/`gtest-devel` system package, or any install `find_package(GTest)`
can locate).

### First time

From `mqtt-publisher/tests/`:

```sh
cmake -S . -B build
cmake --build build
./build/sensor_tests
```

### On subsequent runs

After editing test or source files, you only need to rebuild — `cmake
--build` picks up changed files automatically, and CMake will reconfigure
itself if `CMakeLists.txt` changed:

```sh
cmake --build build
./build/sensor_tests
```

You can also run the suite through CTest, which reports one line per test:

```sh
ctest --test-dir build
```

Only re-run the initial `cmake -S . -B build` step if you want a clean
build (e.g. delete `tests/build/` and start over).
