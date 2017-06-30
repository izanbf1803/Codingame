LX, LY, TX, TY = [int(i) for i in input().split()]

while True:
    d=""
    if TY < LY:
        TY+=1
        d="S"
    elif TY > LY:
        TY-=1
        d="N"
    if TX < LX:
        TX+=1
        d+="E"
    elif TX > LX:
        TX-=1
        d+="W"
    print(d)