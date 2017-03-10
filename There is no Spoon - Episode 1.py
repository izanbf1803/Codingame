width, height = (int(input()), int(input()))
lines = [input() for i in range(height)]
nodes = [[j,i] for i in range(len(lines)) for j in range(len(lines[i])) if lines[i][j] == '0']

for i in nodes:
    parentR, parentD = ([-1, -1], [-1, -1])
    for x in range(height, 0, -1):
        if [ i[0], i[1]+x ] in nodes: parentD = [ i[0], i[1]+x ] 
    for x in range(width, 0, -1):
        if [ i[0]+x, i[1] ] in nodes: parentR = [ i[0]+x, i[1] ]
    
    print(' '.join(map(str, i+parentR+parentD)))
