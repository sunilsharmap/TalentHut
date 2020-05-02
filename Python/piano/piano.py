#! /usr/bin/env python3
################################################################################
# piano.py
#
# author: Sunil Sharma P <sunilsharma.pv@gmail.com>
#   date: May 01, 2020
################################################################################
import os
import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtMultimedia import *
from PyQt5.QtWidgets import *


class Piano(QWidget):
    def __init__(self):
        super().__init__()
        self.title = 'Py Piano - Sunil Sharma P'
        self.setWindowTitle(self.title)
        self.setWindowIcon(QIcon('resources/piano.jpg'))
        self.setGeometry(0, 0, 1000, 300)

        # Member variables
        self.btn_c = QPushButton(self)
        self.btn_d = QPushButton(self)
        self.btn_e = QPushButton(self)
        self.btn_f = QPushButton(self)
        self.btn_g = QPushButton(self)
        self.btn_a = QPushButton(self)
        self.btn_b = QPushButton(self)
        # self.btn_cs = QPushButton(self)
        # self.btn_ds = QPushButton(self)
        # self.btn_fs = QPushButton(self)
        # self.btn_gs = QPushButton(self)
        # self.btn_as = QPushButton(self)
        self.audio_player = QMediaPlayer()

        self.create_piano()
        self.center()
        self.show()

    def create_piano(self):
        names = ['C', 'D', 'E', 'F', 'G', 'A', 'B']
        buttons = [self.btn_c, self.btn_d, self.btn_e, self.btn_f, self.btn_g, self.btn_a, self.btn_b]
        k = 300
        for i, j in zip(names, buttons):
            j.setText(i)
            j.setGeometry(k, 80, 50, 200)
            j.setStyleSheet(
                '''
                QPushButton:pressed {
                    border: 2px solid #8f8f91;
                    background-color: grey   ;
                }
                QPushButton {
                    background-color: white;
                    border-width: 1px;
                    border-style: solid;
                    border-color: black
                }
                '''
            )
            k += 55
            j.clicked.connect(self.piano_key_pressed)

    def keyPressEvent(self, key_pressed):
        path = os.getcwd()
        key = key_pressed.key()
        if chr(key) in ['C', 'D', 'E', 'F', 'G', 'A', 'B']:
            self.music_player(path + '/resources/{}.wav'.format(chr(key)))

    def piano_key_pressed(self):
        path = os.getcwd()
        sender = self.sender()
        self.music_player(path + '/resources/{}.wav'.format(sender.text()))

    def music_player(self, note):
        media = QUrl.fromLocalFile(note)
        content = QMediaContent(media)
        self.audio_player.setMedia(content)
        self.audio_player.play()

    def center(self):
        qr = self.frameGeometry()
        cp = QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Piano()
    sys.exit(app.exec_())

