from Tkinter import *


def pressed():
    print 'Button clicked'


root=Tk()
root.title('PY - GUI')
root.eval('tk::PlaceWindow %s center' % root.winfo_pathname(root.winfo_id()))
root.resizable(width=False, height=False)
root.geometry('125x50')

first=Frame(root)
first.pack()

last=Frame(root)
last.pack(side=BOTTOM)

b1=Button(first, command=pressed, text='Click Me', bd=5, fg='Blue')
b1.pack(side=LEFT, fill=X)

root.mainloop()
