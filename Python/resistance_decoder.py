#!/usr/bin/python3

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class combodemo(QWidget):
   def __init__(self, parent = None):
      super(combodemo, self).__init__(parent)
 
      self.setFixedSize(400, 100)
      self.center()

      self.b1 = -1;
      self.b2 = -1;
      self.b3 = -1;
     
      self.Band1 = { 'Black':0, 'Brown':1, 'Red':2,'Orange':3, 'Yellow':4, 'Green':5,'Blue':6,
			         'Violet':7,'Gray':8, 'White':9, 'None':-5}
      self.Band2 = { 'Black':0, 'Brown':1, 'Red':2,'Orange':3, 'Yellow':4, 'Green':5,'Blue':6,
			         'Violet':7,'Gray':8, 'White':9, 'None':-5}
      self.Band3 = { 'Black':0, 'Brown':1, 'Red':2,'Orange':3, 'Yellow':4, 'Green':5,'Blue':6,
			         'Violet':7,'Gray':8, 'White':9, 'None':-5}

      self.cb1 = QComboBox()
      self.cb1.addItems(['None', 'Black', 'Brown', 'Red', 'Orange', 'Yellow', 'Green', 'Blue', 'Violet', 'Gray', 'White'])
      self.cb1.activated.connect(lambda:self.selectionchange(self.cb1))
		
      self.cb2 = QComboBox()
      self.cb2.addItems(['None', 'Black', 'Brown','Red', 'Orange', 'Yellow', 'Green', 'Blue', 'Violet', 'Gray', 'White'])
      self.cb2.activated.connect(lambda:self.selectionchange(self.cb2))

      self.cb3 = QComboBox()
      self.cb3.addItems(['None', 'Black', 'Brown', 'Red', 'Orange', 'Yellow', 'Green', 'Blue', 'Violet', 'Gray', 'White'])
      self.cb3.activated.connect(lambda:self.selectionchange(self.cb3))

      self.cb4 = QPushButton('Calculate')
      self.cb4.setToolTip('Click to compute the Resister Value')
      self.cb4.setStyleSheet("font: bold")
      self.cb4.clicked.connect(self.calculate_value)

      self.cb5 = QPushButton('How to...!')
      self.cb5.setToolTip('Usage...!')
      self.cb5.clicked.connect(self.show_readme)

      self.line = QLineEdit()
      self.line.setAlignment(Qt.AlignCenter)
      self.line.setReadOnly(True)
      self.line.setStyleSheet("font: bold; color: green; background-color: white")
      self.line.setText('Resistor Value')

      self.lb1 = QLabel()
      self.lb1.setText('Band-1')

      self.lb2 = QLabel()
      self.lb2.setText('Band-2')

      self.lb3 = QLabel()
      self.lb3.setText('Band-3')

      box1 = QHBoxLayout()
      box2 = QHBoxLayout()
      box3 = QHBoxLayout()
      box4 = QVBoxLayout()
      box5 = QHBoxLayout()
      vbox = QVBoxLayout()
      hbox = QHBoxLayout()

      box1.addWidget(self.lb1)
      box1.addWidget(self.lb2)
      box1.addWidget(self.lb3)
      box2.addWidget(self.cb1)
      box2.addWidget(self.cb2)
      box2.addWidget(self.cb3)
      box3.addWidget(self.cb5)
      box3.addWidget(self.cb4)
      box4.addWidget(self.line)

      vbox.addLayout(box1)
      vbox.addLayout(box2)
      vbox.addLayout(box3)
      vbox.addLayout(box5)
      hbox.addLayout(vbox)
      hbox.addLayout(box4)

      self.setLayout(hbox)

      self.setWindowTitle('Resistance Decoder')

   def show_readme(self):
        str1 = "This is to calculate the Resister value by the color-coding.\
		Here you can find the 3-Band color value of a resister.\
		Select the proper colors as it is there on resister.\
		Clilck 'Calculate' to see the Human Readable resister value.\
		The tolerance band is currently not implemented.\
		Ex: Brown Black Red = 1K Ohms"
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Information)
        msg.setWindowTitle("How to...!")
        msg.setText(str1)
        msg.setStandardButtons(QMessageBox.Ok)
        msg.exec_()

   def selectionchange(self, obj):
	   if obj == self.cb1:
               self.b1 = self.Band1[str(obj.currentText())]
	   if obj == self.cb2:
               self.b2 = self.Band2[str(obj.currentText())]
	   if obj == self.cb3:
               self.b3 = self.Band3[str(obj.currentText())]

   def human_readable(self, num, suffix=' Ohms'):
      for unit in ['','K','M','G','T']:
          if (abs(num) < 1000.0):
              return '%3.1f%s%s' % (num, unit, suffix)
          num /= 1000.0
      return '%.1f%s%s' % (num, 'Yi', suffix)
	  
   def calculate_value(self):
      self.line.setStyleSheet("font: bold; color: green; background-color: white")
      res = ((self.b1*10) + self.b2) * pow(10, self.b3)
      if res >= 0:
          self.line.setText(self.human_readable(res))
      else:
          self.line.setStyleSheet("font: bold; color: red; background-color: white")
          self.line.setText('Error. . .')

   def center(self):
        screen = QDesktopWidget().screenGeometry()
        mysize = self.geometry()
        hpos = ( screen.width() - mysize.width() ) / 2
        vpos = ( screen.height() - mysize.height() ) / 2
        self.move(hpos, vpos)



def main():
   app = QApplication(sys.argv)
   ex = combodemo()
   ex.show()
   sys.exit(app.exec_())

if __name__ == '__main__':
   main()
