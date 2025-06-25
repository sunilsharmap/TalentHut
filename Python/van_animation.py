#!/usr/bin/env python3

"""
Van animation with running road and spinning wheels
Press space-bar to pause/resume the van
"""

import os
import time
import curses
import signal
import itertools

# Frames for animation
van_frames = [
[
r'''                    .------. ''',
r'''                    :|||"""`.`. ''',
r'''                    :|||     7.`. ''',
r''' .===+===+===+===+===||`----L7'-`7`---.._ ''',
r''' []                  || ==       |       """-. ''',
r''' []...._____.........||........../ _____ ____| ''',
r'''c\____/,---.\_       ||_________/ /,---.\_  _/ ''',
r'''  /_,-/ ,-. \ `._____|__________||/ ,-. \ \_[ ''',
r'''==== /\ `-' / ================== /\ `-' / ====== ''',
r'''       `---'                       `---' ''',
r'''#####          #####          #####          ### ''',
r'''                                                 ''',
r'''================================================ '''
],
[
r'''                    .------. ''',
r'''                    :|||"""`.`. ''',
r'''                    :|||     7.`. ''',
r''' .===+===+===+===+===||`----L7'-`7`---.._ ''',
r''' []                  || ==       |       """-. ''',
r''' []...._____.........||........../ _____ ____| ''',
r'''c\____/,---.\_       ||_________/ /,---.\_  _/ ''',
r'''  /_,-/ \/  \ `._____|__________||/  \/ \ \_[ ''',
r'''==== /\ /\  / ================== /\  /\ / ====== ''',
r'''       `---'                       `---' ''',
r'''##          #####          #####          ###### ''',
r'''                                                 ''',
r'''================================================ '''
],
[
r'''                    .------. ''',
r'''                    :|||"""`.`. ''',
r'''                    :|||     7.`. ''',
r''' .===+===+===+===+===||`----L7'-`7`---.._ ''',
r''' []                  || ==       |       """-. ''',
r''' []...._____.........||........../ _____ ____| ''',
r'''c\____/,---.\_       ||_________/ /,---.\_  _/ ''',
r'''  /_,-/ _/  \ `._____|__________||/ _/  \ \_[ ''',
r'''==== /\  \  /====================/\  \  / ====== ''',
r'''       `---'                       `---' ''',
r'''       #####          #####          ########    ''',
r'''                                                 ''',
r'''================================================ '''
],
[
r'''                    .------. ''',
r'''                    :|||"""`.`. ''',
r'''                    :|||     7.`. ''',
r''' .===+===+===+===+===||`----L7'-`7`---.._ ''',
r''' []                  || ==       |       """-. ''',
r''' []...._____.........||........../ _____ ____| ''',
r'''c\____/,---.\_       ||_________/ /,---.\_  _/ ''',
r'''  /_,-/  \_ \ `._____|__________||/  \_ \ \_[ ''',
r'''==== /\  /  / ================== /\  /  / ====== ''',
r'''       `---'                       `---' ''',
r'''  #####          #####          ########         ''',
r'''                                                 ''',
r'''================================================ '''
]
]

obj_frames = van_frames

# Ignore Ctrl+c
signal.signal(signal.SIGINT, signal.SIG_IGN)
if os.name != 'nt':
    signal.signal(signal.SIGTSTP, signal.SIG_IGN)

# pause the car by pressing space-bar
pause = False

def van_animation(std_scr):
    global pause
    curses.curs_set(0)
    std_scr.nodelay(True)

    max_y, max_x = std_scr.getmaxyx()
    height = len(obj_frames[0])
    width = max(len(line) for frame in obj_frames for line in frame)

    y_pos = max_y // 2 - height // 2
    x_pos = -width
    paused = False
    frame_cycle = itertools.cycle(obj_frames)

    while x_pos < max_x:
        if pause:
            key = std_scr.getch()
            if key == ord(' '):
                if pause:
                    pause = False
            continue

        std_scr.clear()

        frame = next(frame_cycle if not paused else itertools.repeat(next(frame_cycle)))

        for i, line in enumerate(frame):
            y = y_pos + i
            if 0 <= y < max_y:
                if x_pos < 0:
                    visible = line[-x_pos:]  # Clip the start if car is entering from left
                    if visible:
                        std_scr.addstr(y, 0, visible[:max_x])
                elif x_pos < max_x:
                    visible = line[:max_x - x_pos]  # Clip the end if it overflows right
                    if visible:
                        std_scr.addstr(y, x_pos, visible)

        std_scr.refresh()
        time.sleep(0.05)

        if not paused:
            x_pos += 1

        # pause car pressing space-bar
        key = std_scr.getch()
        if key == ord(' '):
            if not pause:
                pause = True

curses.wrapper(van_animation)
