###################################################
#                                                 #
#        DANGER: THIS CODE IS INCOMPLETE:         #
#        ONLY SOLVES 71% OF TESTS                 #
#                                                 #
###################################################


class Build:
    def __init__(self, _w, _h):
        self.x0 = 0
        self.x1 = _w
        self.y0 = 0
        self.y1 = _h

import sys

def jump(_x,_y):
    print(str(int(_x))+" "+str(int(_y)))

w, h = [int(i) for i in input().split()]
n = int(input())  # maximum number of turns before game over.
x, y = [int(i) for i in input().split()]

build = Build(w,h)

while True:
    d = input()  # the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)

    if d[0] == "U":
        build.y1 = y
        y -= int( (y - build.y0) / 2 )
    elif d[0] == "D":
        build.y0 = y
        y += int( (build.y1 - y) / 2 )
        
    if d.find("R") != -1:
        build.x0 = x
        x += int( (build.x1 - x) / 2 )
    elif d.find("L") != -1:
        build.x1 = x
        x -= int( (x - build.x0) / 2 )
    
    jump(x,y)