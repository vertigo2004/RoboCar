import tkinter
import serial

root = tkinter.Tk()
root.title('Timer')
root.state('normal')

sec = 0.0

doTick1 = False
doTick2 = False


def tick():
    global sec

    if doTick1:
        timeLabel1.configure(text=sec)
    if doTick2:
        timeLabel2.configure(text=sec)
    if doTick1 or doTick2:
        sec = round(sec + 0.1, 1)
        root.after(100, tick)

def stop1():
    global doTick1
    doTick1 = False

def stop2():
    global doTick2
    doTick2 = False

def start():
    global sec
    global doTick1
    global doTick2
    if not doTick1 and not doTick2:
        sec = 0.0
        doTick1 = True
        doTick2 = True
        tick()

def reset():
    global sec
    stop1()
    stop2()
    sec = 0.0
    timeLabel1.configure(text=sec)
    timeLabel2.configure(text=sec)


timeLabel1 = tkinter.Label(root, fg='green',font=('Helvetica',150))
timeLabel1.pack(side=tkinter.LEFT)

timeLabel2 = tkinter.Label(root, fg='blue',font=('Helvetica',150))
timeLabel2.pack(side=tkinter.RIGHT)

timeLabel1.configure(text=sec)
timeLabel2.configure(text=sec)

startButton = tkinter.Button(root, text='Start', command=start)
startButton.pack()

stopButton1 = tkinter.Button(root, text='Stop', command=stop1)
stopButton1.pack()
stopButton2 = tkinter.Button(root, text='Stop', command=stop2)
stopButton2.pack()

resetButton = tkinter.Button(root, text='Reset', command=reset)
resetButton.pack()

root.mainloop()
