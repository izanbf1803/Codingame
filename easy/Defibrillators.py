import math

lon = float(input().replace(",","."))
lat = float(input().replace(",","."))

def distance(lonA, latA, lonB, latB):
    x = (lonB - lonA) * math.cos((lonA + lonB) / 2)
    y = latB - latA
    return math.sqrt(x*x + y*y) * 6371
    

n = int(input())
defibs = None
prox = math.inf
d = ""

for i in range(n):
    defibs = input().replace(",", ".").split(";")
    lon_d, lat_d = (float(defibs[4]), float(defibs[5]))
    dist = distance(lon, lat, lon_d, lat_d)
    if dist < prox:
        prox = dist
        d = defibs[1]

print(d)