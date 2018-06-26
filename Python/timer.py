from Tkinter import *
from tkMessageBox import *#showinfo
import time

root = Tk()
root.title('Timer')
root.eval('tk::PlaceWindow %s center' % root.winfo_pathname(root.winfo_id()))
root.resizable(width=False, height=False)
root.geometry('125x80')
time1 = 0
clock = Label(root, font='cambria 20 bold', fg='red', bg='white')

f=Frame(root)
f.pack()

s=Scale(f, from_=1, to=60, orient=HORIZONTAL, bd=3)
s.focus_set()
s.pack(anchor=CENTER)

b2=Button(root, text='Quit', command=lambda : quit(), bd=3)

def tick_again():
	global time1
	clock.config(text=str(time1))
	if time1:
		time1-=1
		if time1 < 5:
			clock.config(bg='red', fg='white')
		clock.after(1000, tick_again)
	else:
		showinfo('Time-up', 'Time Up')

def tick():
	global time1
	time1=int(s.get())
	clock.pack(fill=BOTH, expand=1)
	f.pack_forget()
	f.destroy()
	b2.pack(anchor=CENTER)
	tick_again()

b1=Button(f, text='Start Timer', command=tick, bd=3)
b1.pack()
	
root.mainloop(  )
