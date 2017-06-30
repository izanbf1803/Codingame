n = int(input())  # the number of temperatures to analyse (IGNORED)
temps = map(int, input().split())  # the n temperatures expressed as integers ranging from -273 to 5526

if n > 0:
    result = min(temps, key=lambda x: abs(x-0.1)) # abs(x-0.1) -> set priority to positive value
else:
    result = 0

print(result)