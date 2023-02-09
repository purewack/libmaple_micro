import time
from common import *
import serial
import curses
from sideload_serial import sideload

def stats(win,options,config):
    win.clear()
    win.border()
    win.addstr(0,2,'libnumcalcium tool')
    win.addnstr(1,1,f'Port:{config["port"]}',30)
    win.addnstr(2,1,f'TS:{options["timeStamp"]}',30)
    win.addnstr(3,1,f'Sideload:{config["sideload"]}',30)
    win.addnstr(4,1,f'Firmware:{config["firmware"]}',30)
    win.refresh()

def main(stdscr):
    ser = serial.Serial(config['port'],115200)
    
    stdscr.nodelay(1)
    stdscr.clear()
    stdscr.refresh()
    curses.curs_set(0)
    
    winConsole = curses.newwin(64,128,0,32)

    winStats = curses.newwin(8,32,0,0)
    options = {
        "timeStamp" : False
    }
    stats(winStats,options,config)

    wasNewline = True
    while(True):
        try:
            key = stdscr.getch()
        except:
            key = None

        if(key == ord('q')):
            break

        if(key == ord('s')):
            winConsole.addstr(f'\t[Sideload]:{config["sideload"]}\n')
            winConsole.refresh()
            sideload(ser,f"{root}/../{config['sideload']}")
        elif(key == ord('t')):
            options['timeStamp'] = not options['timeStamp']
            stats(winStats,options,config)

        if(ser.in_waiting):
            while(ser.in_waiting):
                if(wasNewline):
                    wasNewline = False
                    if(options['timeStamp']):
                        winConsole.addstr(f'@ [{time.time()}] :')
                        winConsole.addstr(b'\n>\t')
                    else:
                        winConsole.addstr('>')

                c = ser.read()
                winConsole.addstr(c)
                
                if(c == b'\n'):
                    wasNewline = True
            
            winConsole.refresh()

    ser.close()

curses.wrapper(main)