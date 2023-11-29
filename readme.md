---
runme:
  id: 01HGCGX48TT4SYX3NMRCPRCKKK
  version: v2.0
---

# Custom BLE Beacon and Ranged detector

The provided Arduino code is designed for scanning for Bluetooth Low Energy (BLE) devices and identifying whether they are within a certain proximity. It uses the ESP32's BLE library to achieve this. Let's break down the code and provide documentation for each section:

```cpp {"id":"01HGCGX48TT4SYX3NMQXPX25X4"}
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

```

These lines include the necessary libraries for Bluetooth Low Energy functionality in Arduino using the ESP32 platform.

```cpp {"id":"01HGCGX48TT4SYX3NMR07MQTSB"}
BLEScan* pBLEScan;
unsigned long previousMillis = 0;
const long interval = 1000; // 1 second

```

Here, a pointer to a BLEScan object is declared (pBLEScan), and variables for timing the BLE scans are defined. previousMillis is used to store the last time a scan was performed, and interval determines the time between consecutive scans (1 second in this case).

```cpp {"id":"01HGCGX48TT4SYX3NMR13A8BWG"}
const String avoid_list[] = {
  "0d:ba:05:bc:da:6e",
  // ... (other MAC addresses to avoid)
};
const int avoid_list_size = sizeof(avoid_list) / sizeof(avoid_list[0]);

```

An array avoid_list is defined to store MAC addresses of BLE devices that should be avoided. The avoid_list_size is calculated based on the size of the array.

```cpp {"id":"01HGCGX48TT4SYX3NMR2XF1NPR"}
void setup() {
  Serial.begin(115200);
  while (!Serial);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
}

```

The setup() function initializes the serial communication for debugging purposes, initializes the BLE device, and sets up the BLE scan with active scanning enabled.

```cpp {"id":"01HGCGX48TT4SYX3NMR6BGBPQM"}
bool isInAvoidList(const String& address) {
  // Function to check if a given BLE device address is in the avoid list
  // Returns true if it is, false otherwise
}
 
bool startsWith(const char *str, const char *prefix) {
  // Function to check if a string starts with a given prefix
  // Returns true if it does, false otherwise
}

// ... (other functions will be explained later)

```

These functions are utility functions used to check if a BLE device address is in the avoid list (isInAvoidList) and if a string starts with a certain prefix (startsWith).

```cpp {"id":"01HGCGX48TT4SYX3NMR89Q8FGN"}
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // ... (BLE scanning logic)
  }

  // ... (non-blocking tasks can go here)
}

```

The loop() function is where the main logic resides. It checks if the specified interval has passed since the last BLE scan, and if so, it performs a new scan for BLE devices.

```cpp {"id":"01HGCGX48TT4SYX3NMRATT7SSN"}
float calculateDistance(int txPower, int rssi) {
  // Function to calculate distance based on received signal strength
  // using the formula: distance = 10 ^ ((txPower - rssi) / 20)
  // Returns the calculated distance
}

```

The calculateDistance function computes the distance between the BLE device and the scanner based on the received signal strength indicator (RSSI) and the transmission power (txPower).

The code within the loop performs the following steps:

## BLE Scanning:

- Initiates a BLE scan and retrieves the list of discovered devices.
- Iterates through each device and extracts its address, RSSI, and calculates distance using the calculateDistance function.

## Filtering Devices:

- Checks if the device address starts with "ff:ff:" to identify it as an iTag device.
- Verifies if the device is not in the avoid list.

## Proximity Check:

- Checks if the calculated distance is less than or equal to 2 meters.
## Logging and Record Keeping:

- Prints information about the device if it satisfies the conditions.
- Checks if the device has been recorded before and logs its information if it's a new encounter.
## Non-blocking Tasks:

- Any non-blocking tasks can be placed outside the time-sensitive BLE scanning logic.

##### Please note that some functions (e.g., isRecorded, addRecord) are referenced in the comments but not defined in the provided code. These functions would presumably be part of a larger program, and their implementations are not included here.