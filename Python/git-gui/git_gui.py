#!/usr/bin/env python3
###########################################################
# git_gui.py
#
# author: Sunil Sharma P <sunilsharma.pv@gmail.com>
# date  : April 26, 2020
#
# copyright: All right reserved
###########################################################

import sys
from PyQt5.QtWidgets import *
from PyQt5 import QtCore, QtGui
from PyQt5.QtGui import QIcon

import time
from subprocess import Popen, PIPE, call, check_output

class App(QWidget):
    def __init__(self):
        super().__init__()
        self.title = 'Git GUI - By Sunil Sharma P'
        self.hex_file = ''
        self.password = ''
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setWindowIcon(QIcon('git.png'))
        self.center()
        self.setFixedSize(800, 480)

        font = QtGui.QFont()
        font.setPointSize(12)

        self.pb_1 = QPushButton(self)
        self.pb_1.setGeometry(QtCore.QRect(10, 20, 141, 41))
        self.pb_1.setFont(font)
        self.pb_1.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pb_1.setToolTip("")
        self.pb_1.setObjectName("pb_1")
        self.pb_1.setText("Git Status")
        self.pb_1.clicked.connect(self.pb1_click)

        self.pb_2 = QPushButton(self)
        self.pb_2.setGeometry(QtCore.QRect(10, 100, 141, 41))
        self.pb_2.setFont(font)
        self.pb_2.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pb_2.setToolTip("")
        self.pb_2.setObjectName("pb_2")
        self.pb_2.setText("Git Log")
        self.pb_2.clicked.connect(self.pb2_click)

        self.pb_3 = QPushButton(self)
        self.pb_3.setGeometry(QtCore.QRect(10, 180, 141, 41))
        self.pb_3.setFont(font)
        self.pb_3.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pb_3.setToolTip("")
        self.pb_3.setObjectName("pb_3")
        self.pb_3.setText("Git Diff")
        self.pb_3.clicked.connect(self.pb3_click)

        self.pb_4 = QPushButton(self)
        self.pb_4.setGeometry(QtCore.QRect(10, 260, 141, 41))
        self.pb_4.setFont(font)
        self.pb_4.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pb_4.setToolTip("")
        self.pb_4.setObjectName("pb_4")
        self.pb_4.setText("Git Add")
        self.pb_4.clicked.connect(self.pb4_click)

        self.pb_5 = QPushButton(self)
        self.pb_5.setGeometry(QtCore.QRect(10, 340, 141, 41))
        self.pb_5.setFont(font)
        self.pb_5.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pb_5.setToolTip("")
        self.pb_5.setObjectName("pb_5")
        self.pb_5.setText("Git Commit")
        self.pb_5.clicked.connect(self.pb5_click)

        self.pb_6 = QPushButton(self)
        self.pb_6.setGeometry(QtCore.QRect(10, 420, 141, 41))
        self.pb_6.setFont(font)
        self.pb_6.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.pb_6.setToolTip("")
        self.pb_6.setObjectName("pb_6")
        self.pb_6.setText("Git Push")
        self.pb_6.clicked.connect(self.pb6_click)

        self.le_1 = QTextEdit(self)
        self.le_1.setGeometry(QtCore.QRect(160, 20, 620, 441))
        self.le_1.setText("")
        self.le_1.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignTop)
        self.le_1.setReadOnly(True)
        self.le_1.setObjectName("le_1")

        self.le_2 = QLabel(self)
        self.le_2.setGeometry(QtCore.QRect(10, 0, 621, 20))
        self.le_2.setText("")
        self.le_2.setObjectName("le_2")

        self.show()


    def pb1_click(self):
        cmd = Popen('git status', stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
        stdout, stderr = cmd.communicate()
        result = cmd.returncode
        if not result:
            self.le_1.setText(str(stdout, 'utf-8'))
        else:
            self.le_1.setText(str(stderr, 'utf-8'))


    def pb2_click(self):
        cmd = Popen('git log', stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
        stdout, stderr = cmd.communicate()
        result = cmd.returncode
        if not result:
            self.le_1.setText(str(stdout, 'utf-8'))
        else:
            self.le_1.setText(str(stderr, 'utf-8'))


    def pb3_click(self):
        cmd = Popen('git diff', stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
        stdout, stderr = cmd.communicate()
        result = cmd.returncode
        if not result:
            self.le_1.setText(str(stdout, 'utf-8'))
        else:
            self.le_1.setText(str(stderr, 'utf-8'))


    def pb4_click(self):
        files, okPressed = QInputDialog.getText(self, "Enter files to be added", "Files ", QLineEdit.Normal, "Space separated file names")
        if okPressed and files != '':
            cmd = Popen('git add {}'.format(files), stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
            stdout, stderr = cmd.communicate()
            result = cmd.returncode
            if not result:
                self.le_1.setText(str(stdout, 'utf-8'))
            else:
                self.le_1.setText(str(stderr, 'utf-8'))

        self.pb1_click()


    def pb5_click(self):
        amend = ''
        reply = QMessageBox.question(self, 'Git Commit', "Do you want to amend?", QMessageBox.Yes | QMessageBox.No | QMessageBox.Cancel, QMessageBox.Cancel)
        if reply == QMessageBox.Yes:
            amend = '--amend'
        if reply == QMessageBox.No:
            pass
        if reply == QMessageBox.Cancel:
            return

        msg, okPressed = QInputDialog.getText(self, "Enter Commit Message","Commit Message ", QLineEdit.Normal, "Commit Message")
        if okPressed and msg != '':
            cmd = Popen('git commit {0} -m \"{1}\"'.format(amend, msg), stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True)
            stdout, stderr = cmd.communicate()
            result = cmd.returncode
            if not result:
                self.le_1.setText(str(stdout, 'utf-8'))
            else:
                self.le_1.setText(str(stderr, 'utf-8'))

        self.pb1_click()


    def pb6_click(self):
        self.le_1.setText("***** Not Currently Implemented *****")


    def center(self):
        # geometry of the main window
        qr = self.frameGeometry()
        # center point of screen
        cp = QDesktopWidget().availableGeometry().center()
        # move rectangle's center point to screen's center point
        qr.moveCenter(cp)
        # top left of rectangle becomes top left of window centering it
        self.move(qr.topLeft())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())
