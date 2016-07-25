def select():
    for i in possible:
        if i in s_possible: return i
    return possible[0]

n, l, e = [int(i) for i in input().split()]
links = [[int(j) for j in input().split()] for i in range(l)]
gates = [int(input()) for i in range(e)]

while True:
    si = int(input())
    s_possible = [i for i in links if si in i]
    possible = [i for gate in gates for i in links if gate in i]
    
    print("%s %s" % (select()[0], select()[1]))