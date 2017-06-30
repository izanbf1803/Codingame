l = int(input())
h = int(input())
t = str(input())

alphabet = [str(input()) for i in range(h)]

for i in range(h):
    for char in t.lower():
        if char >= 'a' and char <= 'z':
            x = ord(char) - ord('a')
        else:
            x = ord('z') - ord('a') + 1

        print(alphabet[i][x*l : x*l+l], end='') # print from X*L, to X*L+L    
    print('')