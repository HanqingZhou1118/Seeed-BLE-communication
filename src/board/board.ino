#include "LSM6DS3.h"
#include "Wire.h"
#include <ArduinoBLE.h>

// 创建 IMU 设备实例
LSM6DS3 myIMU(I2C_MODE, 0x6A);    // I2C 设备地址 0x6A

// 定义 BLE 服务和特性
BLEService imuService("fff0"); // 修正为唯一的服务 UUID
BLECharacteristic imuCharacteristic("2A58", BLERead | BLENotify, 128); // IMU 数据特性 UUID

void setup() {
    Serial.begin(9600);

    // 初始化 IMU
    if (myIMU.begin() != 0) {
        Serial.println("IMU initialization failed!");
        while (1); // 如果 IMU 初始化失败，停止程序
    } else {
        Serial.println("IMU Device OK!");
    }

    // 初始化 BLE
    if (!BLE.begin()) {
        Serial.println("Starting BLE failed!");
        while (1); // 如果 BLE 初始化失败，停止程序
    }

    // 设置 BLE 广播名称
    BLE.setLocalName("XIAO_IMU_BLE");
    BLE.setAdvertisedService(imuService);

    // 添加特性到服务
    imuService.addCharacteristic(imuCharacteristic);
    BLE.addService(imuService);

    // 开始 BLE 广播
    BLE.advertise();
    Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
    BLEDevice central = BLE.central(); // 检测是否有中央设备连接

    if (central) { // 如果有设备连接
        Serial.print("Connected to central: ");
        Serial.println(central.address());

        while (central.connected()) { // 当设备保持连接时
            // 获取 IMU 数据
            float accelX = myIMU.readFloatAccelX();
            float accelY = myIMU.readFloatAccelY();
            float accelZ = myIMU.readFloatAccelZ();
            float gyroX = myIMU.readFloatGyroX();
            float gyroY = myIMU.readFloatGyroY();
            float gyroZ = myIMU.readFloatGyroZ();

            // 将 IMU 数据简化为字符串
            String imuData = String(accelX, 4) + "," +
                             String(accelY, 4) + "," +
                             String(accelZ, 4) + "," +
                             String(gyroX, 4) + "," +
                             String(gyroY, 4) + "," +
                             String(gyroZ, 4);

            // 发送数据到 BLE 特性
            imuCharacteristic.writeValue(imuData.c_str());

            // 打印到串口（调试用）
            Serial.println(imuData);

            // 每 1 秒更新一次数据
            delay(1000);
        }

        Serial.println("Disconnected from central.");
    }
}
