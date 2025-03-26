# BLE Scanner and IMU Data Receiver

## Overview
This repository contains Python scripts for scanning Bluetooth Low Energy (BLE) devices and receiving Inertial Measurement Unit (IMU) sensor data from a BLE-enabled Arduino device. These scripts can be used to:

- **Scan and list available BLE devices** using `BLEscanner.py`.
- **Connect to a specific Arduino device and receive real-time IMU sensor data (acceleration and gyroscope values)** using `seeed_pc_blereceiver.py`.
- **(Optional) Arduino BLE broadcasting program** included as `board.ino` for setting up your Arduino device to broadcast IMU data via BLE.

---

## File Descriptions

### 📄 `BLEscanner.py`
A Python script for scanning and displaying nearby BLE devices.

- **Dependencies:**
  - Python 3.x
  - bleak (`pip install bleak`)

- **Usage:**
```bash
python BLEscanner.py
```

- **Functionality:**
  - Initiates a BLE scan and prints out the discovered devices, including their names and MAC addresses.

---

### 📄 `seeed_pc_blereceiver.py`
A Python script for connecting to an Arduino BLE device, subscribing to IMU sensor notifications, and saving the received data to a file on the desktop.

- **Dependencies:**
  - Python 3.x
  - bleak (`pip install bleak`)

- **Important Configuration:**
Modify these variables in the script according to your specific setup:

- `address`: BLE MAC address of your Arduino device.
- `imu_uuid`: UUID of the IMU sensor data characteristic broadcasted by Arduino.

- **Usage:**
```bash
python seeed_pc_blereceiver.py
```

- **Functionality:**
  - Connects to the specified BLE device.
  - Subscribes to IMU data notifications (accelerometer and gyroscope).
  - Writes timestamped IMU sensor data to a `.txt` file saved to your desktop.

- **Output Example:**
```
2025-03-26 15:25:41 - Accel: ['-0.01', '0.02', '9.80'], Gyro: ['-0.01', '0.02', '0.03']
```

---

### 📄 `board.ino`
An Arduino sketch file (`.ino`) designed for Arduino devices equipped with BLE modules and IMU sensors. This script broadcasts IMU sensor data via BLE.

- **Dependencies:**
  - Arduino IDE
  - Appropriate Arduino BLE libraries
  - IMU sensor libraries compatible with your Arduino hardware (e.g., Arduino Nano 33 BLE, Arduino Nano 33 BLE Sense, etc.)

- **Usage:**
  - Upload the script to your Arduino device via Arduino IDE.
  - Make sure BLE functionality and IMU sensor data reading are correctly initialized and broadcasted.

- **Functionality:**
  - Initializes BLE and IMU sensors on the Arduino.
  - Broadcasts real-time accelerometer and gyroscope sensor data.

---

## Quick Start Guide

1. **Prepare Arduino device:**
   - Upload `board.ino` using Arduino IDE to your BLE-enabled Arduino device.
   - Ensure the Arduino device is powered and running correctly.

2. **Scan BLE devices:**
   ```bash
   python BLEscanner.py
   ```
   - Identify and copy the MAC address of your Arduino device from the listed results.

3. **Receive IMU data:**
   - Open `seeed_pc_blereceiver.py` and replace the placeholder MAC address with your Arduino device's MAC address.
   - Confirm that the IMU UUID matches the characteristic being broadcast by your Arduino.
   - Run the script:
   ```bash
   python seeed_pc_blereceiver.py
   ```
   - The received IMU data will be continuously saved to a timestamped file on your desktop.

---

## Troubleshooting

- **Ensure Bluetooth is enabled and supported** on your host device.
- **Check Arduino broadcasting**: Verify Arduino correctly broadcasts BLE data.
- **UUID mismatch**: Confirm UUID used in scripts matches the Arduino broadcast UUID.
- **Python dependencies**: Reinstall dependencies if errors occur:
```bash
pip install --upgrade bleak
```

---

## Dependencies Installation

Install Python dependencies easily via pip:

```bash
pip install bleak
```

---

## License

This project is open-source. Feel free to use, modify, and distribute the code provided.

---

## Contact

For any issues or queries, please open an issue in this repository or contact the project maintainer directly.

Happy coding! 🎉