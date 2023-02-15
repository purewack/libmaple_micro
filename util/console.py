import time
import serial
import curses
from common import *
from sideload_serial import sideload
import stm32loader


def stats_update():
    winStats.clear()
    winStats.border()
    winStats.addstr(0,2,'libnumcalcium tool')
    winStats.addnstr(1,1,f'Port:{config["port"]}',30)
    winStats.addnstr(2,1,f'Open:{ser.is_open}',30)
    winStats.addnstr(3,1,f'[T]imestamp:{config["timeStamp"]}',30)
    winStats.addnstr(4,1,f'[A]utoscroll:{config["autoScroll"]}',30)
    winStats.addnstr(5,1,f'[S]ideload:{config["sideload"]}',30)
    winStats.addnstr(6,1,f'[F]irmware:{config["firmware"]}',30)
    winStats.addnstr(7,1,f'[C]lear',30)
    winStats.refresh()

def try_port():
    curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_RED)

    try:
        ser.open()
        winConsole.bkgd(' ', curses.color_pair(1) | curses.A_BOLD)
    except:
        winConsole.bkgd(' ', curses.color_pair(2) | curses.A_BOLD)
    
    winConsole.refresh()
    stats_update()

def main(stdscr):
    curses.init_color(curses.COLOR_RED, 400, 0, 0)
    stdscr.nodelay(1)
    stdscr.clear()
    stdscr.refresh()
    curses.curs_set(0)
    
    global winConsole 
    winConsole = curses.newwin(curses.LINES,128,0,32)
    winConsole.scrollok(True)

    global winStats 
    winStats = curses.newwin(12,32,0,0)
    
    global ser 
    ser = serial.Serial()
    ser.port = config['port']
    ser.baudrate = 115200

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

        if(ser.is_open and ser.in_waiting):
            while(ser.in_waiting):
                if(wasNewline):
                    wasNewline = False
                    if(config['timeStamp']):
                        winConsole.addstr(f'@ [{time.time()}] :')
                        winConsole.addstr(b'\n>\t')
                    else:
                        winConsole.addstr('>')

                c = ser.read()
                winConsole.addstr(c)
                
                if(c == b'\n'):
                    winConsole.refresh()
                    wasNewline = True
            

    ser.close()

curses.wrapper(main)