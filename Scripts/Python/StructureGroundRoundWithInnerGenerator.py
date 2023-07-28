from math import cos, sin, pi

faces = 10
radius = 0.1 # meter
radiusStr = str(radius)
radiusInner = 0.04
outZ, inZ = "0.05", "0.08" # could type variable name zIn, zOut instead of minZ, maxZ - even if logical, put weight in the center not the extremities # used to be respectively minZ, maxZ
idOffset = 10

# copied from StructureGroundRoundGenerator.py

lines = ""
commonFactor = 2 * pi / faces

def getPointNb(angle, r = radius):
    return [round(x, 3) for x in (r * cos(angle), r * sin(angle))]

def getPoint(angle, r = radius):
    l = [str(x) for x in getPointNb(angle, r)]
    for i in range(2):
        el = l[i]
        if el[-2:] == ".0":
            el = el[:-2]
        l[i] = el
    return l

def distance(x0, y0, x1, y1):
    return ((x0 - x1) ** 2 + (y0 - y1) ** 2) ** 0.5

def s(x, y, z):
    return x + ";" + y + ";" + z

xNb, yNb = getPointNb(commonFactor)
d = round(distance(radius, 0, xNb, yNb), 3)
oldD, newD = 0, d
oldZ, newZ = 0, radius - radiusInner

for facesIndex in range(faces):
    angle, nextAngle = facesIndex * commonFactor, (facesIndex + 1) * commonFactor
    x, y = getPoint(angle)
    xIn, yIn = getPoint(angle, radiusInner)
    xNb, yNb = getPointNb(angle)
    nextX, nextY = getPoint(nextAngle)
    nextXIn, nextYIn = getPoint(nextAngle, radiusInner)
    nextXNb, nextYNb = getPointNb(nextAngle)
    oldDS = str(round(oldD, 3))
    newDS = str(round(newD, 3))
    oldZS = str(round(oldZ, 3))
    newZS = str(round(newZ, 3))
    lines += str(facesIndex + idOffset) + " QUAD " + oldDS + ";" + oldZS + " " + oldDS + ";" + newZS + " " + newDS + ";" + newZS + " " + newDS + ";" + oldZS + " " + " ".join([s(xIn, yIn, inZ), s(x, y, outZ), s(nextX, nextY, outZ), s(nextXIn, nextYIn, inZ)])
    oldD = newD
    newD += d
    oldZ = newZ
    newZ += radius - radiusInner
    if facesIndex != faces - 1:
        lines += '\n'

print(lines)