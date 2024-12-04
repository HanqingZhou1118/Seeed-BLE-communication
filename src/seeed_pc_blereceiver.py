
import asyncio
from bleak import BleakClient

address = "EF:94:54:F9:55:9B"  # 替换为您的 Arduino BLE 设备的 MAC 地址
sensor_uuids = ["2A6E", "2A6F", "2A70"]  # UUIDs for the sensor characteristics

async def main(address):
    async with BleakClient(address) as client:
        isConnected = await client.is_connected()
        print(f"Connected: {isConnected}")

        # check if it is connected, then set a while loop to read the sensor values
        while isConnected:
            await read_sensor_values(client)

async def read_sensor_values(client):
    for sensor_uuid in sensor_uuids:
        value = await client.read_gatt_char(sensor_uuid)
        sensor_value = float.fromhex(value.hex())

        print(f"Sensor {sensor_uuid}: {sensor_value}")
    await asyncio.sleep(0.05)

if __name__ == "__main__":
    asyncio.run(main(address))
