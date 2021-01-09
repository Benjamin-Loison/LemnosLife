from math import cos, sin, pi

faces = 10
radius = 0.1 # meter
minZ, maxZ = "0", "0.03"
idOffset = 0
perpendicular = False

"""
b_ficusc1s_f.png
0 QUAD 1;0 1;1 0;1 0;0 -0.5;0;0 -0.5;0;1 0.5;0;1 0.5;0;0
1 QUAD 1;0 1;1 0;1 0;0 0;-0.5;0 0;-0.5;1 0;0.5;1 0;0.5;0
"""

lines = ""
commonFactor = 2 * pi / faces # 2 * pi / faces for whole circle, just pi / faces for a demi one

def getPointNb(angle):
    return [round(x, 3) for x in (radius * cos(angle), radius * sin(angle))]

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

def cleanStr(s):
    if s[-2:] == ".0":
        s = s[:-2]
    return s

def cleanNb(x):
    return cleanStr(str(round(x, 3)))

deltaZ = cleanNb(float(maxZ) - float(minZ))

def distance(x0, y0, x1, y1):
    return ((x0 - x1) ** 2 + (y0 - y1) ** 2) ** 0.5

def s(x, y, z):
    return x + ";" + y + ";" + z

xNb, yNb = getPointNb(commonFactor)
d = round(distance(radius, 0, xNb, yNb), 3)
oldD, newD = 0, d # should go back to 0 or negative values when too high ?

for facesIndex in range(faces):
    angle, nextAngle = facesIndex * commonFactor, (facesIndex + 1) * commonFactor
    x, y = getPoint(angle)
    xNb, yNb = getPointNb(angle)
    #print(angle)
    nextX, nextY = getPoint(nextAngle)
    nextXNb, nextYNb = getPointNb(nextAngle)
    #d = str(round(distance(xNb, yNb, nextXNb, nextYNb), 3))
    #lines += str(facesIndex) + " QUAD " + d + ";0 " + d + ";" + deltaZ + " 0;" + deltaZ + " 0;0 " + " ".join([s(x, y, minZ), s(x, y, maxZ), s(nextX, nextY, maxZ), s(nextX, nextY, minZ)])  # add texture normal size and continuous from a part to the other - done
    oldDS = cleanNb(oldD)
    newDS = cleanNb(newD)
    if perpendicular:
        textureCoords = "0;" + oldDS + " " + deltaZ + ";" + oldDS + " " + deltaZ + ";" + newDS + " " + "0;" + newDS + " "
    else:
        textureCoords = oldDS + ";0 " + oldDS + ";" + deltaZ + " " + newDS + ";" + deltaZ + " " + newDS + ";0 "
    lines += str(facesIndex + idOffset) + " QUAD " + textureCoords + " ".join([s(x, y, minZ), s(x, y, maxZ), s(nextX, nextY, maxZ), s(nextX, nextY, minZ)])
    oldD = newD
    newD += d
    if facesIndex != faces - 1:
        lines += "\n"

print(lines)