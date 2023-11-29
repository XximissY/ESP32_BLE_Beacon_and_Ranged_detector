#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan* pBLEScan;
unsigned long previousMillis = 0;
const long interval = 1000; // 1 second

const String avoid_list[] = {
  "0d:ba:05:bc:da:6e",
  "5d:0e:a2:59:32:d8",
  "33:f4:d7:1b:44:aa",
  "64:bd:84:56:f5:83",
  "1e:8e:52:00:2c:fa",
  "4b:49:67:9c:a8:5c",
  "d1:cd:51:44:b6:f6",
  "07:c3:99:a9:e9:fd",
  "40:95:da:df:b1:a9",
  "0a:27:67:38:5e:44",
  "1c:7d:ce:45:d4:47",
  "37:6f:55:20:89:45",
};
const int avoid_list_size = sizeof(avoid_list) / sizeof(avoid_list[0]);
 

void setup() {
  Serial.begin(115200);
  while (!Serial);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
}

bool isInAvoidList(const String& address) {
  for (int i = 0; i < avoid_list_size; i++) {
    if (address.equals(avoid_list[i])) {
      return true;
    }
  }
  return false;
}
 

bool startsWith(const char *str, const char *prefix) {
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if 1 second has passed since the last scan
  if (currentMillis - previousMillis >= interval) {
    // Save the current time
    previousMillis = currentMillis;

    // Scan for BLE devices
    BLEScanResults foundDevices = pBLEScan->start(1);

    for (int i = 0; i < foundDevices.getCount(); i++) {
      BLEAdvertisedDevice device = foundDevices.getDevice(i);

      // Get the device address as a String
      String deviceAddress = String(device.getAddress().toString().c_str());
      // Check if the device is not iTag
      if (startsWith(deviceAddress.c_str(), "ff:ff:")) {
        // Check if the device is in the avoid list
        if (!isInAvoidList(deviceAddress)) {
          // Get RSSI and calculate distance
          int rssi = device.getRSSI();
          float distance = calculateDistance(-65, rssi);

          // Check if the distance is less than or equal to 2 meters
          if (distance <= 2.00f) {
            // Print information for the device
            Serial.print("Device found: ");
            Serial.print(deviceAddress);
            Serial.print(" RSSI: ");
            Serial.print(rssi);
            Serial.print(" Distance: ");
            Serial.print(distance);
            Serial.println(" meters");

            // Check if the device has passed by before
            if (!isRecorded(deviceAddress)) {
              // Store the device information
              addRecord(deviceAddress, rssi, distance);
            }
          }
        }
      }
    }
  }

  // Your non-blocking tasks can go here
}

// Function to calculate distance using the formula
float calculateDistance(int txPower, int rssi) {
  return pow(10.0, ((txPower - rssi) / 20.0));
}
