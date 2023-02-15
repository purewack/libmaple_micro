import serial
from common import *
st_ack = b'\x79'
st_nack = b'\x1f'

def info_bootloader(ser:serial.Serial):
    pass

def write_bootloader(ser:serial.Serial, fw_file):
    fw_size = os.stat(fw_file).st_size

    with open(fw_file,"rb") as fw:
        ser.write(fw_size.to_bytes(2, 'little'))
        ack = ser.read()
        if(ack != st_ack):
            return -1
        fw_data = bytearray(fw.read())
        ser.write(fw_data)

        ack = ser.read()
        if(ack != st_ack):
            return -2
        
        verify_data = ser.read(fw_size)
        if(verify_data != fw_data):
            return -3

    return 0

if(__name__ == '__main__'):
    print("Uploading firmware @ USART")
    fw_file = f"{root}/../{config['firmware']}"
    ser = serial.Serial(config['port'],115200)
    ret = write_bootloader(ser,fw_file)
    ser.close()
    if(ret == 0):
        print("Uploading firmware done")