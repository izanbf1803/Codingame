def generateCode(digit, n):
    result = '0 ' if last == '1' else '00 '
    result += '0' * count
    return result

message = input()
binary = ''.join(format(ord(char), '07b') for char in message) # Generate string of 8 bit chars as binary

output = ''
last = None
count = 0

for digit in binary:
    if digit == last:
        count += 1
    else:
        if last != None:
            output += generateCode(last, count) + ' '
        count = 1
        last = digit

output += generateCode(last, count)

print(output)