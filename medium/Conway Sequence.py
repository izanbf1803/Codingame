#By izanbf1803
r, l = int(input()), int(input())
seq = str(r)

for h in range(1, l):
    nums = list(map(int, seq.split(" ")))
    
    data = []
    last = nums[0]
    count = 0
    for i in nums:
        if last == i:
            count += 1
        else:
            data.append((count, last))
            count = 1
            last = i
    data.append((count, last))
    
    new = ""
    for i in data:
        new += str(i[0]) + " " + str(i[1]) + " "
    
    seq = new[:-1]

print(seq)
