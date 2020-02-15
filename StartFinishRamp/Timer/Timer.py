import tkinter
import serial
import asyncio

SERIAL_START = b'1'
SERIAL_RESET = b'2'
SERIAL_STOP1 = '3'
SERIAL_STOP2 = '4'

ARDUINO_PORT = '/dev/ttyUSB0'

ser = serial.Serial(ARDUINO_PORT, 9600) # Establish the connection on a specific port

root = tkinter.Tk()
root.title('Timer')
root.state('normal')

sec = 0.0

doTick1 = False
doTick2 = False


def tick():
    global sec
    global SERIAL_STOP1
    global SERIAL_STOP2
    global doTick1
    global doTick2

    if ser.inWaiting() > 0:
        data = ser.read(ser.inWaiting()).decode('ascii')
        print('data received', repr(data))

        if data == SERIAL_STOP1:
            doTick1 = False
        if data == SERIAL_STOP2:
            doTick2 = False

    if doTick1:
        timeLabel1.configure(text=sec)
    if doTick2:
        timeLabel2.configure(text=sec)

    if doTick1 or doTick2:
        sec = round(sec + 0.1, 1)
        root.after(100, tick)


def start():
    global sec
    global doTick1
    global doTick2
    global loop

    if not doTick1 and not doTick2:
        sec = 0.0
        doTick1 = True
        doTick2 = True
        ser.write(SERIAL_START)

        tick()


def reset():
    global sec
    global doTick1
    global doTick2

    ser.write(SERIAL_RESET)
    doTick1 = False
    doTick2 = False

    sec = 0.0
    timeLabel1.configure(text=sec)
    timeLabel2.configure(text=sec)


timeLabel1 = tkinter.Label(root, fg='green', font=('Helvetica',150))
timeLabel1.pack(side=tkinter.LEFT)

timeLabel2 = tkinter.Label(root, fg='blue', font=('Helvetica',150))
timeLabel2.pack(side=tkinter.RIGHT)

timeLabel1.configure(text=sec)
timeLabel2.configure(text=sec)

startButton = tkinter.Button(root, text='Start', command=start)
startButton.pack()

resetButton = tkinter.Button(root, text='Reset', command=reset)
resetButton.pack()

root.mainloop()

ser.close()
