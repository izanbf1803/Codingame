MIME = {}
n, q = int(input()), int(input())

for i in range(n):
    ext, mt = input().split()
    MIME[ext.lower()] = mt
    
for i in range(q):
    f = input().lower().split(".")
    ext = f[-1] if len(f) != 1 else None
    print(MIME[ext] if ext in MIME else "UNKNOWN")