#! /usr/bin/env python3
# -*- coding: utf-8 -*-
######################################################
# ludo.py
#
# author: Sunil Sharma P <sunilsharma.pv@gmail.com>
#   date: May 08, 2020
######################################################


import sys
import random
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtMultimedia import *


class Ludo(QWidget):

    def __init__(self):
        super().__init__()
        self.title = 'Ludo - Sunil Sharma P'
        self.setWindowTitle(self.title)
        self.setGeometry(0, 0, 1000, 750)

        self.center_lbl = QLabel(self)
        self.red_home = QLabel(self)
        self.blue_home = QLabel(self)
        self.yellow_home = QLabel(self)
        self.green_home = QLabel(self)

        self.initUI()
        self.board()
        self.showMaximized()
        self.show()

    def initUI(self):
        pass

    def board(self):
        self.center_lbl.setGeometry(300, 300, 150, 150)
        self.center_lbl.setPixmap(QPixmap('resources/center.png'))

        self.red_home.setGeometry(0, 0, 300, 300)
        self.red_home.setPixmap(QPixmap('resources/red.png'))

        self.blue_home.setGeometry(0, 448, 300, 300)
        self.blue_home.setPixmap(QPixmap('resources/blue.png'))

        self.green_home.setGeometry(450, 0, 300, 300)
        self.green_home.setPixmap(QPixmap('resources/green.png'))

        self.yellow_home.setGeometry(450, 450, 300, 300)
        self.yellow_home.setPixmap(QPixmap('resources/yellow.png'))

        v = 0
        z = 0
        while v != 300:  # Drawing White boxes for green
            z = 0
            while z != 150:
                lbl = QLabel(self)
                lbl.setGeometry(300 + z, 0 + v, 50, 50)
                lbl.setPixmap(QPixmap('resources/whitebox.png'))
                z = z + 50
            v = v + 50

        z = 0
        v = 0
        while v != 300:  # Drawing White boxes for red
            z = 0
            while z != 150:
                lbl = QLabel(self)
                lbl.setGeometry(0 + v, 300 + z, 50, 50)
                lbl.setPixmap(QPixmap('resources/whitebox.png'))
                z = z + 50
            v = v + 50

        v = 0
        z = 0
        while v != 300:  # Drawing White boxes blue
            z = 0
            while z != 150:
                lbl = QLabel(self)
                lbl.setGeometry(300 + z, 450 + v, 50, 50)
                lbl.setPixmap(QPixmap('resources/whitebox.png'))
                z = z + 50
            v = v + 50

        z = 0
        v = 0
        while v != 300:  # Drawing White boxes for yellow
            z = 0
            while z != 150:
                lbl = QLabel(self)
                lbl.setGeometry(450 + v, 300 + z, 50, 50)
                lbl.setPixmap(QPixmap('resources/whitebox.png'))
                z = z + 50
            v = v + 50

        v = 0
        while v != 250:     #Drawing Green boxes
            lbl = QLabel(self)
            lbl.setGeometry(350, 50 + v, 49, 49)
            lbl.setPixmap(QPixmap('resources/greenbox.png'))
            v = v + 50

        lbl = QLabel(self)
        lbl.setGeometry(400, 50, 49, 49)
        lbl.setPixmap(QPixmap('resources/greenbox.png'))

        lbl = QLabel(self)
        lbl.setGeometry(300, 100, 49, 49)
        lbl.setPixmap(QPixmap('resources/green_star.png'))

        v = 0
        while v != 250:  # Drawing yellow boxes
            lbl = QLabel(self)
            lbl.setGeometry(450 + v, 350, 49, 49)
            lbl.setPixmap(QPixmap('resources/yellowbox.png'))
            v = v + 50

        lbl = QLabel(self)
        lbl.setGeometry(650, 400, 49, 49)
        lbl.setPixmap(QPixmap('resources/yellowbox.png'))

        lbl = QLabel(self)
        lbl.setGeometry(600, 300, 49, 49)
        lbl.setPixmap(QPixmap('resources/yellow_star.png'))

        v = 0
        while v != 250:  # Drawing red boxes
            lbl = QLabel(self)
            lbl.setGeometry(50 + v, 350, 49, 49)
            lbl.setPixmap(QPixmap('resources/redbox.png'))
            v = v + 50

        lbl = QLabel(self)
        lbl.setGeometry(50, 300, 49, 49)
        lbl.setPixmap(QPixmap('resources/redbox.png'))

        lbl = QLabel(self)
        lbl.setGeometry(100, 400, 49, 49)
        lbl.setPixmap(QPixmap('resources/red_star.png'))

        v = 0
        while v != 250:  # Drawing blue boxes
            lbl = QLabel(self)
            lbl.setGeometry(350, 450 + v, 49, 49)
            lbl.setPixmap(QPixmap('resources/bluebox.png'))
            v = v + 50

        lbl = QLabel(self)
        lbl.setGeometry(300, 650, 49, 49)
        lbl.setPixmap(QPixmap('resources/bluebox.png'))

        lbl = QLabel(self)
        lbl.setGeometry(400, 600, 49, 49)
        lbl.setPixmap(QPixmap('resources/blue_star.png'))

        lbl = QLabel(self)  # Drawing blue arrow boxes
        lbl.setGeometry(350, 700, 49, 49)
        lbl.setPixmap(QPixmap('resources/blue_arrow.png'))

        lbl = QLabel(self)  # Drawing red arrow boxes
        lbl.setGeometry(0, 350, 49, 49)
        lbl.setPixmap(QPixmap('resources/red_arrow.png'))

        lbl = QLabel(self)  # Drawing green arrow boxes
        lbl.setGeometry(350, 0, 49, 49)
        lbl.setPixmap(QPixmap('resources/green_arrow.png'))

        lbl = QLabel(self)  # Drawing yellow arrow boxes
        lbl.setGeometry(700, 350, 49, 49)
        lbl.setPixmap(QPixmap('resources/yellow_arrow.png'))


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Ludo()
    sys.exit(app.exec_())

