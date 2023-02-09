import serial
from common import *

def sideload(ser, cart_file):
    ack_byte = b'\xac'
    cart_size = os.stat(cart_file).st_size

    with open(cart_file,"rb") as cart:
        ser.write(cart_size.to_bytes(2, 'little'))
        ack = ser.read()
        if(ack != ack_byte):
            return -1
        cart_data = bytearray(cart.read())
        ser.write(cart_data)

        ack = ser.read()
        if(ack != ack_byte):
            return -2
        
        verify_data = ser.read(cart_size)
        if(verify_data != cart_data):
            return -3

    return 0

if(__name__ == '__main__'):
    print("Sideloading cart")
    cart_file = f"{root}/../{config['sideload']}"
    ser = serial.Serial(config['port'],115200)
    ret = sideload(ser,cart_file)
    ser.close()
    if(ret == 0):
        print("Sideloading cart done")