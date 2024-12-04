import asyncio
from bleak import BleakClient

address = "EF:94:54:F9:55:9B"  # 替换为您的 Arduino BLE 设备的 MAC 地址
temperature_uuid = "FFF1"  # 替换为您的温度特征 UUID

async def read_temperature(client):
    """读取温度数据"""
    try:
        temperature = await client.read_gatt_char(temperature_uuid)
        temperature_value = int.from_bytes(temperature, byteorder='little')
        print(f"Temperature: {temperature_value} °C")
    except Exception as e:
        print(f"Error reading temperature: {e}")

async def main(address):
    async with BleakClient(address) as client:
        isConnected = await client.is_connected()
        print(f"Connected: {isConnected}")

        # 如果连接成功，循环读取数据
        if isConnected:
            while True:
                await read_temperature(client)
                await asyncio.sleep(2)  # 每 2 秒读取一次数据

if __name__ == "__main__":
    asyncio.run(main(address))




import asyncio
from bleak import BleakClient

address = "your:device:mac:address"  # Use the correct MAC address
sensor_uuids = ["2A6E", "2A6F", "2A70"]  # UUIDs for the sensor characteristics

async def main(address):
    async with BleakClient(address) as client:
        isConnected = await client.is_connected()
        print(f"Connected: {isConnected}")

        for uuid in sensor_uuids:
            value = await client.read_gatt_char(uuid)
            # Assuming the value is a float stored as 4 bytes
            sensor_value = float.fromhex(value.hex())
            print(f"Sensor Value ({uuid}): {sensor_value}")

if __name__ == "__main__":
    asyncio.run(main(address))
