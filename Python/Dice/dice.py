#! /usr/bin/env python3
######################################################
# dice.py
#
# author: Sunil Sharma P <sunilsharma.pv@gmail.com>
#   date: April 28, 2020
######################################################
import sys
import os
import random
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtMultimedia import *


class Dice(QWidget):
    def __init__(self):
        super().__init__()
        self.title = 'Dice Rolling - Sunil Sharma P'
        self.setWindowTitle(self.title)
        self.setWindowIcon(QIcon('resources/rgby.png'))
        self.setGeometry(0, 0, 800, 600)

        # Member variables
        self.player = ['green', 'red', 'blue', 'yellow']
        self.Winner = False
        self.Runner = False
        self.Third = False
        self.btn_dice = QPushButton(self)
        self.green_pbar = QProgressBar(self)
        self.red_pbar = QProgressBar(self)
        self.blue_pbar = QProgressBar(self)
        self.yellow_pbar = QProgressBar(self)
        self.pbars = [self.green_pbar, self.red_pbar, self.blue_pbar, self.yellow_pbar]
        self.turn = 0
        self.g_score = 0
        self.r_score = 0
        self.b_score = 0
        self.y_score = 0

        # Media player setup Win
        self.win_tone = QMediaPlayer()
        self.path = os.getcwd()
        self.win_media = QUrl.fromLocalFile(self.path + '/resources/music.mp3')
        self.win_content = QMediaContent(self.win_media)
        self.win_tone.setMedia(self.win_content)

        # Media player setup Dice Roll
        self.mouse_tone = QMediaPlayer()
        self.mouse_media = QUrl.fromLocalFile(self.path + '/resources/dice_roll.mp3')
        self.mouse_content = QMediaContent(self.mouse_media)
        self.mouse_tone.setMedia(self.mouse_content)

        self.center()
        self.initUI()
        self.show()

    def initUI(self):
        self.btn_dice.setGeometry(10, 10, 100, 90)
        self.btn_dice.setStyleSheet("background-color: white")
        self.btn_dice.setIcon(QIcon('./1.png'))
        self.btn_dice.setIconSize(QSize(100, 100))
        self.btn_dice.setToolTip('Click to roll the DICE !!')
        self.btn_dice.move(330, 10)
        self.btn_dice.setIcon(QIcon('resources/rgby.png'))
        self.btn_dice.clicked.connect(self.on_click_dice)

        self.green_pbar.setAlignment(Qt.AlignCenter)
        self.green_pbar.setFormat("%p")
        self.green_pbar.setStyleSheet("QProgressBar::chunk {background : #39da0d }")
        self.green_pbar.setGeometry(25, 150, 750, 50)

        self.red_pbar.setAlignment(Qt.AlignCenter)
        self.red_pbar.setFormat("%p")
        self.red_pbar.setStyleSheet("QProgressBar::chunk {background : #f41e14 }")
        self.red_pbar.setGeometry(25, 250, 750, 50)

        self.blue_pbar.setAlignment(Qt.AlignCenter)
        self.blue_pbar.setFormat("%p")
        self.blue_pbar.setStyleSheet("QProgressBar::chunk {background : #1839f2 }")
        self.blue_pbar.setGeometry(25, 350, 750, 50)

        self.yellow_pbar.setAlignment(Qt.AlignCenter)
        self.yellow_pbar.setFormat("%p")
        self.yellow_pbar.setStyleSheet("QProgressBar::chunk {background : #ffff1a }")
        self.yellow_pbar.setGeometry(25, 450, 750, 50)

    def win_music_player(self):
        self.win_tone.play()

    def mouse_music_player(self):
        self.mouse_tone.play()

    def next_player(self):
        if (self.turn == len(self.player) - 1) or (self.turn == len(self.player)):
            self.turn = 0
        else:
            self.turn += 1

    def winner_runner(self, scr):
        if scr == 100 and self.Winner == False:
            self.Winner = True
            self.pbars[self.turn].setFormat("*** Winner ***")
            del (self.player[self.turn])
            del (self.pbars[self.turn])
        elif scr == 100 and self.Runner == False:
            self.Runner = True
            self.pbars[self.turn].setFormat("*** Runner ***")
            del (self.player[self.turn])
            del (self.pbars[self.turn])
        elif scr == 100 and self.Third == False:
            self.Third = True
            self.pbars[self.turn].setFormat("*** 3rd Place ***")
            del (self.player[self.turn])
            del (self.pbars[self.turn])

            if 1 == len(self.player):
                self.pbars[0].setFormat("*** Looser ***")

            self.btn_dice.setIcon(QIcon('resources/rgby.png'))
            self.btn_dice.setDisabled(True)
            self.win_music_player()

    def on_click_dice(self):
        self.mouse_music_player()
        i = random.randint(1, 6)
        score = 0
        if self.player[self.turn] == 'green':
            self.btn_dice.setIcon(QIcon('resources/g{}.png'.format(i)))
            self.g_score += i
            if self.g_score <= 100:
                self.green_pbar.setValue(self.g_score)
            else:
                self.g_score -= i
            score = self.g_score

        if self.player[self.turn] == 'red':
            self.btn_dice.setIcon(QIcon('resources/r{}.png'.format(i)))
            self.r_score += i
            if self.r_score <= 100:
                self.red_pbar.setValue(self.r_score)
            else:
                self.r_score -= i
            score = self.r_score

        if self.player[self.turn] == 'blue':
            self.btn_dice.setIcon(QIcon('resources/b{}.png'.format(i)))
            self.b_score += i
            if self.b_score <= 100:
                self.blue_pbar.setValue(self.b_score)
            else:
                self.b_score -= i
            score = self.b_score

        if self.player[self.turn] == 'yellow':
            self.btn_dice.setIcon(QIcon('resources/y{}.png'.format(i)))
            self.y_score += i
            if self.y_score <= 100:
                self.yellow_pbar.setValue(self.y_score)
            else:
                self.y_score -= i
            score = self.y_score
        if i < 6:
            self.winner_runner(score)
            self.next_player()

    def center(self):
        qr = self.frameGeometry()
        cp = QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Dice()
    sys.exit(app.exec_())

