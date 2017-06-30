import math

minimum = math.inf
n = int(input())
numbers = sorted(int(input()) for i in range(n)) 

for i in range(n-1):
    difference = numbers[i+1] - numbers[i]
    minimum = min(minimum, difference)

print(minimum)