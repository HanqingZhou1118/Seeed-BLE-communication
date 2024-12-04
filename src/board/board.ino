#include <ArduinoBLE.h>

BLEService sensorService("fff0"); // Custom Service UUID, use a unique UUID

// Define one characteristic for each sensor with a unique UUID
BLEFloatCharacteristic sensor1Characteristic("2A6E", BLERead | BLENotify);
BLEFloatCharacteristic sensor2Characteristic("2A6F", BLERead | BLENotify);
BLEFloatCharacteristic sensor3Characteristic("2A70", BLERead | BLENotify);

const uint8_t manufactData[4] = {0x01, 0x02, 0x03, 0x04};
const uint8_t serviceData[3] = {0x00, 0x01, 0x02};


void setup() {
  Serial.begin(9600);
  //while (!Serial);

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("MultiSensor");
  BLE.setAdvertisedService(sensorService);
  
  // Add characteristics to service
  sensorService.addCharacteristic(sensor1Characteristic);
  sensorService.addCharacteristic(sensor2Characteristic);
  sensorService.addCharacteristic(sensor3Characteristic);
  
  // Add service
  BLE.addService(sensorService);
  
  // Set initial value for each characteristic
  sensor1Characteristic.writeValue(0.0f);
  sensor2Characteristic.writeValue(0.0f);
  sensor3Characteristic.writeValue(0.0f);


  // Build scan response data packet
  BLEAdvertisingData scanData;
  // Set parameters for scan response packet
  scanData.setLocalName("Test enhanced advertising");
  // Copy set parameters in the actual scan response packet
  BLE.setScanResponseData(scanData);



  BLEAdvertisingData advData;
  // Set parameters for advertising packet
  advData.setManufacturerData(0x004C, manufactData, sizeof(manufactData));
  advData.setAdvertisedService(sensorService);
  advData.setAdvertisedServiceData(0xfff0, serviceData, sizeof(serviceData));
  // Copy set parameters in the actual advertising packet
  BLE.setAdvertisingData(advData);





  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // Simulate or read actual sensors
  float sensor1Value = analogRead(A0) * (5.0 / 1023.0); // Convert to voltage
  float sensor2Value = analogRead(A1) * (5.0 / 1023.0); 
  float sensor3Value = analogRead(A2) * (5.0 / 1023.0); 

  // Update characteristics
  sensor1Characteristic.writeValue(sensor1Value);
  sensor2Characteristic.writeValue(sensor2Value);
  sensor3Characteristic.writeValue(sensor3Value);

  //delay(1000); // Delay for demonstration purposes
  BLE.poll();
}
