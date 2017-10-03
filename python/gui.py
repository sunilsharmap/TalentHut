from Tkinter import *


def pressed():
    print 'Button clicked'


root=Tk()
root.title('Python GUI')

first=Frame(root)
first.pack()

last=Frame(root)
last.pack(side=BOTTOM)

b1=Button(first, command=pressed, text='Click Me', bd=5, fg='Blue')
b1.pack(side=LEFT, fill=X)

root.mainloop()
