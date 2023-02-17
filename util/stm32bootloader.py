import serial
from common import *

st_ack = b'\x79'
st_nack = b'\x1f'

def init_bootloader(ser:serial.Serial):
    ser.parity = serial.PARITY_EVEN
    ser.write(b'\x7f')
    resp = ser.read()
    if(resp == st_ack):
        return 'init @ 1st response'
    return 0

def finish_bootloader(ser:serial.Serial):
    ser.parity = serial.PARITY_NONE

def chip_id_bootloader(ser:serial.Serial):
    code = 0x02

    ser.reset_input_buffer()
    ser.reset_output_buffer()
    ser.write(bytearray([code,0xff-code]))
    resp = ser.read()
    if(resp != st_ack):
        return 'ID @ 1st response'
    
    n = int.from_bytes(ser.read(),'big')+1
    if(n < 1):
        return f'ID @ bytes N, got {n}'
    
    id = int.from_bytes(ser.read(n),'big',signed=False)
    resp = ser.read()
    if(resp != st_ack):
        return 'ID @ 2nd response'

    return id

def get_cmd_bootloader(ser:serial.Serial):
    code = 0x00

    ser.reset_input_buffer()
    ser.reset_output_buffer()
    ser.write(bytearray([code,0xff-code]))
    resp = ser.read()
    if(resp != st_ack):
        return 'GET @ 1st response'
    
    n = int.from_bytes(ser.read(),'big')
    if(n < 1):
        return f'GET @ bytes N, got {n}'
    
    protocol = int.from_bytes(ser.read(),'big')
    if(protocol < 1):
        return f'GET @ invalid protocol'
    
    cmds = ser.read(n)
    return [protocol,cmds]

def eraseall_bootloader(ser:serial.Serial):
    code = 0x43

    ser.reset_input_buffer()
    ser.reset_output_buffer()
    ser.write(bytearray([code,0xff-code]))
    
    resp = ser.read()
    if(resp != st_ack):
        return 'ERASE @ 1st response'
    
    ser.write(bytearray([0xff,0x00]))

    resp = ser.read()
    if(resp != st_ack):
        return 'ERASE @ 2nd response'
    
    return 0

def read_bootloader(ser:serial.Serial, offset=0):
    code = 0x11

    ser.reset_input_buffer()
    ser.reset_output_buffer()
    ser.write(bytearray([code,0xff-code]))
    
    resp = ser.read()
    if(resp != st_ack):
        return 'READ @ 1st response'
    
    addr = 0x08000000 + offset
    addrb = addr.to_bytes(4,'big',signed=False)
    addrx = addrb[0] ^ addrb[1] ^ addrb[2] ^ addrb[3]
    ser.write(addrb)
    ser.write(addrx.to_bytes(1,'big'))

    resp = ser.read()
    if(resp != st_ack):
        return 'READ @ 2nd response'
    
    N = 255
    ser.write(bytearray([N,255-N]))

    resp = ser.read()
    if(resp != st_ack):
        return 'READ @ 3rd response'
    
    data = ser.read(N)
    return data

def write_bootloader(ser:serial.Serial, fw_file, verify=False):

    if(not config['firmware'].endswith('.bin')):
        return 'WRITE @ invalid firmware format, expecting .bin'
    
    er = eraseall_bootloader(ser)
    if(not isinstance(er,int)):
        return er

    fw_file = f"{root}/../{config['firmware']}"
    fw_size = os.stat(fw_file).st_size
    fw_chunks = fw_size // 256
    # fw_tail = fw_size - 256*fw_chunks

    with open(fw_file,"rb") as fw:
        
        for i in range(fw_chunks+1):

            code = 0x31 
            ser.reset_input_buffer()
            ser.reset_output_buffer()
            ser.write(bytearray([code,0xff-code]))
            
            resp = ser.read()
            if(resp != st_ack):
                return f'WRITE @ [{i}] 1st response'
            
            addr = 0x08000000 + i*256
            addrb = addr.to_bytes(4,'big',signed=False)
            addrx = addrb[0] ^ addrb[1] ^ addrb[2] ^ addrb[3]
            ser.write(addrb)
            ser.write(addrx.to_bytes(1,'big'))

            resp = ser.read()
            if(resp != st_ack):
                return f'WRITE @ [{i}] 2nd response'
            
            chunk = fw.read(256)
            chunk_chk = len(chunk)-1
            for j in range(len(chunk)):
                chunk_chk ^= chunk[j]

            ser.write((len(chunk)-1).to_bytes(1,'big',signed=False))
            ser.write(chunk)
            ser.write(chunk_chk.to_bytes(1,'big',signed=False))

            resp = ser.read()
            if(resp != st_ack):
                return f'WRITE @ [{i}] 3rd response'
            

            #verify
            code = 0x11

            ser.reset_input_buffer()
            ser.reset_output_buffer()
            ser.write(bytearray([code,0xff-code]))
            
            resp = ser.read()
            if(resp != st_ack):
                return f'VERIFY @ [{i}] 1st response'
            
            addr = 0x08000000 + i*256
            addrb = addr.to_bytes(4,'big',signed=False)
            addrx = addrb[0] ^ addrb[1] ^ addrb[2] ^ addrb[3]
            ser.write(addrb)
            ser.write(addrx.to_bytes(1,'big'))

            resp = ser.read()
            if(resp != st_ack):
                return f'VERIFY @ [{i}] 2nd response'
            
            N = len(chunk)-1
            ser.write(bytearray([N,255-N]))

            resp = ser.read()
            if(resp != st_ack):
                return f'VERIFY @ [{i}] 3rd response'
            
            data = ser.read(N+1)
            if(data != chunk):
                return f'VERIFY @ [{i},{N}] data mismatch'

            
    return 0
            
            
        


if(__name__ == '__main__'):

    # print("Uploading firmware @ USART")
    fw_file = f"{root}/../{config['firmware']}"
    ser = serial.Serial(config['port'],115200)
    ret = write_bootloader(ser,fw_file)
    if(not isinstance(ret,int)):
        print(ret)
    ser.close()
    # if(ret == 0):
    #     print("Uploading firmware done")