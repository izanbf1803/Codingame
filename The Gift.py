import sys

n = int(input())
price = int(input())
wallets = [int(input()) for i in range(n)]
wallets.sort()
to_pay = price
queue = []

if sum(wallets) < price:
    print("IMPOSSIBLE")
    sys.exit(0)

for i in range(n):
    portion = int(to_pay / (n - i))
    
    if wallets[i] < portion:
        to_pay -= wallets[i]
        queue.append(wallets[i])
        wallets[i] = 0
    elif wallets[i] >= portion:
        to_pay -= portion
        queue.append(portion)
        wallets[i] -= portion

if to_pay > 0:
    for i in reversed(range(len(wallets))):
        if wallets[i] >= to_pay:
            queue[i] += to_pay
            to_pay = 0

for i in range(len(queue)):
    print(queue[i])