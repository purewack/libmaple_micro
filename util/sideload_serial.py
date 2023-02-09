import serial
from common import *

ack_byte = b'\xac'
cart_file = f"{root}/../{config['sideload']}"
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