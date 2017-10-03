#! /usr/bin/python
from Tkinter import *

def clrDisply():
	display.delete(0, END)
	return

def clrDisplayOne():
	value = display.get()[:-1]
	display.delete(0, END)
	display.insert(0, value)



def action(arg):
	display.insert(END, arg)
	return

def evaluate():
	expression = display.get()
	try:
		value = eval(expression)
	except SyntaxError or NameError:
		display.delete(0, END)
		display.insert(0, "Syntax Error !")
	else:
		display.delete(0, END)
		display.insert(0, value)
	return


master = Tk()
master.title("Calculator")

frame = Frame(master)
frame.pack()

frame1 = Frame(master)
frame1.pack(side = TOP)

display = Entry(frame, bd = 10, insertwidth = 1, font = 30)
display.pack(side = TOP)

but1 = Button(frame1, padx = 16, pady = 16, bd = 8, text = "1", fg = "blue", command = lambda:action(1))
but1.pack(side = LEFT)

but1 = Button(frame1, padx = 16, pady = 16, bd = 8, text = "2", fg = "blue", command = lambda:action(2))
but1.pack(side = LEFT)

but1 = Button(frame1, padx = 16, pady = 16, bd = 8, text = "3", fg = "blue", command = lambda:action(3))
but1.pack(side = LEFT)

but1 = Button(frame1, padx = 16, pady = 16, bd = 8, text = "4", fg = "blue", command = lambda:action(4))
but1.pack(side = LEFT)

but1 = Button(frame1, padx = 16, pady = 16, bd = 8, text = "(", fg = "blue", command = lambda:action('('))
but1.pack(side = LEFT)

frame2 = Frame(master)
frame2.pack(side = TOP)

but1 = Button(frame2, padx = 16, pady = 16, bd = 8, text = "5", fg = "blue", command = lambda:action(5))
but1.pack(side = LEFT)

but1 = Button(frame2, padx = 16, pady = 16, bd = 8, text = "6", fg = "blue", command = lambda:action(6))
but1.pack(side = LEFT)

but1 = Button(frame2, padx = 16, pady = 16, bd = 8, text = "7", fg = "blue", command = lambda:action(7))
but1.pack(side = LEFT)

but1 = Button(frame2, padx = 16, pady = 16, bd = 8, text = "8", fg = "blue", command = lambda:action(8))
but1.pack(side = LEFT)

but1 = Button(frame2, padx = 16, pady = 16, bd = 8, text = ")", fg = "blue", command = lambda:action(')'))
but1.pack(side = LEFT)

frame3 = Frame(master)
frame3.pack(side = TOP)

but1 = Button(frame3, padx = 16, pady = 16, bd = 8, text = "9", fg = "blue", command = lambda:action(9))
but1.pack(side = LEFT)

but1 = Button(frame3, padx = 16, pady = 16, bd = 8, text = "0", fg = "blue", command = lambda:action(0))
but1.pack(side = LEFT)

but1 = Button(frame3, padx = 16, pady = 16, bd = 8, text = "/", fg = "blue", command = lambda:action('/'))
but1.pack(side = LEFT)

but1 = Button(frame3, padx = 16, pady = 16, bd = 8, text = "AC", fg = "blue", command = lambda:clrDisplayOne())
but1.pack(side = LEFT)

but1 = Button(frame3, padx = 16, pady = 16, bd = 8, text = "C", fg = "blue", command = lambda:clrDisply())
but1.pack(side = LEFT)

frame4 = Frame(master)
frame4.pack(side = TOP)

but1 = Button(frame4, padx = 16, pady = 16, bd = 8, text = "*", fg = "blue", command = lambda:action('*'))
but1.pack(side = LEFT)

but1 = Button(frame4, padx = 16, pady = 16, bd = 8, text = "-", fg = "blue", command = lambda:action('-'))
but1.pack(side = LEFT)

but1 = Button(frame4, padx = 16, pady = 16, bd = 8, text = "+", fg = "blue", command = lambda:action('+'))
but1.pack(side = LEFT)

but1 = Button(frame4, padx = 16, pady = 16, bd = 8, text = ".", fg = "blue", command = lambda:action('.'))
but1.pack(side = LEFT)

but1 = Button(frame4, padx = 16, pady = 16, bd = 8, text = "=", fg = "blue", command = lambda:evaluate())
but1.pack(side = LEFT)



if __name__=='__main__':
	master.mainloop()
