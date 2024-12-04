import asyncio
import os
from datetime import datetime
from bleak import BleakClient

# 替换为您的 Arduino BLE 设备的 MAC 地址
address = "EF:94:54:F9:55:9B"
# 替换为 Arduino 广播的 IMU 特性 UUID
imu_uuid = "2A58"

# 文件路径：保存到桌面
desktop_path = os.path.join(os.path.expanduser("~"), "Desktop")
file_name = f"imu_data_{datetime.now().strftime('%Y%m%d_%H%M%S')}.txt"
file_path = os.path.join(desktop_path, file_name)

async def main(address):
    """主函数：连接 BLE 设备并订阅 IMU 数据"""
    async with BleakClient(address, timeout=30.0) as client:
        is_connected = await client.is_connected()
        print(f"Connected: {is_connected}")

        if is_connected:
            # 打开文件以追加模式写入数据
            with open(file_path, "a") as file:
                print(f"Saving IMU data to: {file_path}")
                # 订阅 IMU 特性通知
                await client.start_notify(imu_uuid, lambda sender, data: notification_handler(sender, data, file))
                print(f"Subscribed to {imu_uuid} notifications.")
                try:
                    # 无限循环接收数据，直到用户手动停止
                    while True:
                        await asyncio.sleep(1)
                except KeyboardInterrupt:
                    print("\nUser stopped the program.")
                finally:
                    # 停止订阅
                    await client.stop_notify(imu_uuid)
                    print("Stopped notifications.")

def notification_handler(sender, data, file):
    """处理从 BLE 接收的通知数据并保存到文件"""
    try:
        # 解码接收到的字符串数据
        imu_data = data.decode("utf-8")
        values = imu_data.split(",")
        accel = values[:3]
        gyro = values[3:]
        print(f"Accel: {accel}, Gyro: {gyro}")

        # 写入到文件（添加时间戳）
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        file.write(f"{timestamp} - Accel: {accel}, Gyro: {gyro}\n")
        file.flush()  # 确保立即写入硬盘
    except Exception as e:
        print(f"Error decoding data: {e}")

if __name__ == "__main__":
    asyncio.run(main(address))
