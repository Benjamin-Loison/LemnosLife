from math import cos, sin, pi

faces = 10
radius = 0.04 # meter
radiusStr = str(radius)
outZ, inZ = "0.08", "0.08"
idOffset = 20

# copied from StructureRoundGenerator.py

lines = ""
commonFactor = 2 * pi / faces

def getPointNb(angle):
    return [round(x, 3) for x in (radius * cos(angle), radius * sin(angle))]

def cleanStr(s):
    if s[-2:] == ".0":
        s = s[:-2]
    return s

def cleanNb(x):
    return cleanStr(str(round(x, 3)))

def getPoint(angle):
    l = [str(x) for x in getPointNb(angle)]
    for i in range(2):
        el = l[i]
        if el[-2:] == ".0":
            el = el[:-2]
        if el == "-0":
            el = "0"
        l[i] = el
    return l

def distance(x0, y0, x1, y1):
    return ((x0 - x1) ** 2 + (y0 - y1) ** 2) ** 0.5

def s(x, y, z):
    return x + ";" + y + ";" + z

xNb, yNb = getPointNb(commonFactor)
d = round(distance(radius, 0, xNb, yNb), 3)
oldD, newD = 0, d
oldZ, newZ = 0, radius

for facesIndex in range(faces):
    angle, nextAngle = facesIndex * commonFactor, (facesIndex + 1) * commonFactor
    x, y = getPoint(angle)
    xNb, yNb = getPointNb(angle)
    nextX, nextY = getPoint(nextAngle)
    nextXNb, nextYNb = getPointNb(nextAngle)
    oldDS = cleanNb(oldD)
    newDS = cleanNb(newD)
    oldZS = cleanNb(oldZ)
    newZS = cleanNb(newZ)
    #oldZS, newZS = "0", "0"
    lines += str(facesIndex + idOffset) + " QUAD " + oldDS + ";" + oldZS + " " + oldDS + ";" + newZS + " " + newDS + ";" + newZS + " " + newDS + ";" + oldZS + " " + " ".join([s("0", "0", inZ), s(x, y, outZ), s(nextX, nextY, outZ), s(nextX, nextY, outZ)])
    oldD = newD
    newD += d
    oldZ = newZ
    newZ += radius
    if facesIndex != faces - 1:
        lines += "\n"

print(lines)