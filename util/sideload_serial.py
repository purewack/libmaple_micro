import serial
import json
import os
import time
import signal
def stop(signum,frame):
    exit(1)
signal.signal(signal.SIGINT, stop)

with open('config.json','r') as f:
    config = json.load(f)

if os.name == 'nt':
    port = config['port_win']
else:
    port = config['port_lnx']

ack_byte = b'\xac'
cart_file = f"{config['root']}/build_cart/{config['filename']}"
cart_size = os.stat(cart_file).st_size
with open(cart_file,"rb") as cart:
    print("libnumcalcium.sideload_serial:")
    print(f"    port: {port} @ {config['baud']}baud")
    print(f"    file: {cart_file} ")
    print(f"    size: {cart_size}b ")

    ser = serial.Serial(port,config['baud'])

    ser.write(cart_size.to_bytes(2, 'little'))
    ack = ser.read()
    if(ack != ack_byte):
        print("ACK size error:")
        print(ack)
        exit(-1)
    print("Uploading data...")
    cart_data = bytearray(cart.read())
    ser.write(cart_data)

    ack = ser.read()
    if(ack != ack_byte):
        print("ACK data write error")
        print(ack)
        exit(-1)
    
    print("Verifing data...")
    verify_data = ser.read(cart_size)
    if(verify_data == cart_data):
        print("[Upload successful]")
    else:
        print("[Invalid data varification]:")
        print("==============[")
        print(verify_data)
        print("==============]")

    ser.close()