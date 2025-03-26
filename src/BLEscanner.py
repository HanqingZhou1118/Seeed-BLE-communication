import asyncio
from bleak import BleakScanner

async def scan_for_devices():
    print("Scanning for BLE devices...")
    devices = await BleakScanner.discover()
    for device in devices:
        print(f"Device found: {device.name}, MAC Address: {device.address}")

loop = asyncio.get_event_loop()
loop.run_until_complete(scan_for_devices())

