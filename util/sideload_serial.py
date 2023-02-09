import serial
import json
import os
import time

config_file = "../config.json"
default_config = {
    "filename":"example/build_cart/cart.bin",
    "port":"/dev/tty.usbserial-1410"
}

if os.path.exists(config_file):
    with open(config_file,'r') as f:
        config = json.load(f)
else:
    with open(config_file,'w+') as f:
        json.dump(default_config,f)
        config = default_config

ack_byte = b'\xac'
cart_file = f"{os.path.dirname(os.path.realpath(__file__))}/../{config['filename']}"
cart_size = os.stat(cart_file).st_size
with open(cart_file,"rb") as cart:
    print("libnumcalcium.sideload_serial:")
    print(f"    port: {config['port']} @ 115200 baud")
    print(f"    file: {cart_file} ")
    print(f"    size: {cart_size}b ")

    ser = serial.Serial(config['port'],115200)

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