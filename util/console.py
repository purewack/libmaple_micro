import time
import serial
import curses
from common import *
from sideload_serial import sideload
from stm32bootloader import *

COL_BG_PORT = 1
COL_FG_PORT = 2
COL_KO_PORT = 3
COL_OK_PORT = 4

def stats_update():
    if(ser.is_open):
        cc = curses.color_pair(COL_OK_PORT)
    else:
        cc = curses.color_pair(COL_KO_PORT)
    winStats.clear()
    winStats.move(1,1)
    winStats.addstr('   libnumcalcium tools\n')
    winStats.addnstr(f' Port:{config["port"]}\n',30,cc)
    winStats.addnstr(f' [T]imestamp:{config["timeStamp"]}\n',30)
    # winStats.addnstr(f' [A]utoscroll:{config["autoScroll"]}\n',30)
    winStats.addnstr(f' [S]ideload:{config["sideload"]}\n',30)
    winStats.addnstr(f' [F]irmware:{config["firmware"]}\n',30)
    winStats.addnstr(f' [C]lear\n',30)
    winStats.addnstr(f' [Q]uit\n',30)
    winStats.border()
    winStats.refresh()

def try_port():
    try:
        if(ser.is_open):
            ser.close()
        else:
            ser.open()
    except:
        pass

    if(ser.is_open):
        winConsole.bkgd(' ', curses.color_pair(COL_FG_PORT) | curses.A_BOLD)
    else:
        winConsole.bkgd(' ', curses.color_pair(COL_BG_PORT) | curses.A_BOLD)
    
    winConsole.refresh()
    stats_update()

def main(stdscr):
    curses.init_pair(COL_BG_PORT, curses.COLOR_WHITE, curses.COLOR_BLACK)
    curses.init_pair(COL_FG_PORT, curses.COLOR_YELLOW, curses.COLOR_BLACK)
    curses.init_pair(COL_KO_PORT, curses.COLOR_WHITE, curses.COLOR_RED)
    curses.init_pair(COL_OK_PORT, curses.COLOR_WHITE, curses.COLOR_GREEN)
    try:
        curses.init_color(curses.COLOR_RED, 400, 0, 0)
        curses.init_color(curses.COLOR_BLACK, 10, 10, 10)
    except:
        pass

    stdscr.nodelay(1)
    stdscr.clear()
    stdscr.refresh()
    curses.curs_set(1)
    
    global winConsole 
    winConsole = curses.newwin(curses.LINES,curses.COLS-32,0,32)
    winConsole.scrollok(True)

    global winStats 
    winStats = curses.newwin(12,32,0,0)
    
    global ser 
    ser = serial.Serial()
    ser.parity = serial.PARITY_NONE
    ser.baudrate = 115200
    ser.port = config['port']

    try_port()

    wasNewline = True
    while(True):
        try:
            key = stdscr.getch()
        except:
            key = None

        if(key == ord('q')):
            config_save()
            break
        
        elif(key == ord('p')):
            try_port()

        elif(key == ord('f')):
            pass

        elif(key == ord('s')):
            winConsole.addstr(f'![Sideload]:{config["sideload"]}\n')
            winConsole.refresh()
            sideload(ser,f"{root}/../{config['sideload']}")
        elif(key == ord('t')):
            config['timeStamp'] = not config['timeStamp']
            stats_update()
        elif(key == ord('c')):
            winConsole.clear()
            winConsole.refresh()
        elif(key == ord('b')):
            winConsole.addstr(f'----[bootloader] begin\n')
            winConsole.refresh()
            init_bootloader(ser)
            time.sleep(0.1)
            
            winConsole.addstr(f'----[bootloader] get data\n')
            winConsole.refresh()
            data = write_bootloader(ser,config['firmware'])
            if(isinstance(data,int)):
                winConsole.addstr(f'----[bootloader] firmware written ok\n')
            else:
                winConsole.addstr(f'----[bootloader error] {data}\n')

            # winConsole.addstr(f'----[bootloader] get cmds\n')
            # winConsole.refresh()
            # [prot,cmds] = get_cmd_bootloader(ser)
            # if(isinstance(cmds,bytes)):
            #     winConsole.addstr(f'----Protocol \n\t: ')
            #     winConsole.addstr(f'{hex(prot)}')
            #     winConsole.addstr(f'\n----Supported CMDS \n\t: ')
            #     for i in range(len(cmds)):
            #         winConsole.addstr(f'{hex(cmds[i])},')
            #     winConsole.addstr(f'\n----[info] refer to: https://www.st.com/resource/en/application_note/an3155-usart-protocol-used-in-the-stm32-bootloader-stmicroelectronics.pdf\n')
            # else:
            #     winConsole.addstr(f'----[bootloader error] #{cmds}#\n')
            winConsole.refresh()
            time.sleep(0.1)

            finish_bootloader(ser)
            winConsole.addstr(f'----[bootloader] end\n')
            winConsole.refresh()
            time.sleep(0.1)
            

        if(ser.is_open and ser.in_waiting):
            while(ser.in_waiting):
                if(wasNewline):
                    wasNewline = False
                    if(config['timeStamp']):
                        winConsole.addstr(f'@ [{time.time()}] :')
                        winConsole.addstr('\n>>\t')
                    else:
                        winConsole.addstr('>')

                c = ser.read()
                if(c != b'\r'):
                    winConsole.addch(c)
                
                if(c == b'\n'):
                    winConsole.refresh()
                    wasNewline = True
            

    ser.close()

curses.wrapper(main)