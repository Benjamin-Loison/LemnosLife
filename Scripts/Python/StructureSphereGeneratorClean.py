from math import cos, sin, pi

# copied from StructuresSphereGenerator.py

polyRegSides = 12
topDownNb = 12 # 12
radius = 4.5 # meter
zOffset = 8.5
path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\577.struc"
texture = "whiteTile.jpg"
write = True

"""
b_ficusc1s_f.png
0 QUAD 1;0 1;1 0;1 0;0 -0.5;0;0 -0.5;0;1 0.5;0;1 0.5;0;0
1 QUAD 1;0 1;1 0;1 0;0 0;-0.5;0 0;-0.5;1 0;0.5;1 0;0.5;0
"""

lines = ""
commonFactorVertical = pi / (1.5 * topDownNb) # pi / (2 * topDownNb) # for demi-sphère

# 577 and 658 seem to have too many faces ? warning 658 is customized by hand

def getPointNb(angleVertical, angleHorizontal):
    #angleVertical = pi / 2 - angleVertical # for demi-sphère
    sinThetaRadius = radius * sin(angleVertical)
    return [round(x, 3) for x in (sinThetaRadius * cos(angleHorizontal), sinThetaRadius * sin(angleHorizontal), radius * cos(angleVertical))]

def getPoint(angleVertical, angleHorizontal):
    l = [str(x) for x in getPointNb(angleVertical, angleHorizontal)]
    l[2] = str(round(float(l[2]) + zOffset, 3))
    for i in range(3):
        el = l[i]
        if el[-2:] == ".0":
            el = el[:-2]
        if el == "-0":
            el = "0"
        l[i] = el
    return l

def s(x, y, z):
    return x + ";" + y + ";" + z

top = []
offset = 0
id = 0
for topDownIndex in range(0, topDownNb):
    angleDown, angleUp = topDownIndex * commonFactorVertical, (topDownIndex + 1) * commonFactorVertical
    horizontalSides = topDownNb #1 + (topDownNb - topDownIndex - 1)
    topOld = top[:]
    top = []
    for horizontalIndex in range(horizontalSides):
        commonFactorHorizontal = 2 * pi / (polyRegSides)
        angleCur, angleNext = horizontalIndex * commonFactorHorizontal + offset, (horizontalIndex + 1) * commonFactorHorizontal + offset

        xCur, yCur, zCur = getPoint(angleDown, angleCur)
        xNext, yNext, zNext = getPoint(angleDown, angleNext)

        #if len(topOld) == 0 or horizontalIndex == 0 or horizontalIndex == horizontalSides - 1:
        #angleBetween = angleCur
        """if horizontalIndex == horizontalSides - 1:
            angleBetween = angleNext
        elif horizontalIndex != 0:"""
        angleBetween = (angleCur + angleNext) / 2
        xTopBetween, yTopBetween, zTopBetween = getPoint(angleUp, angleBetween)
        """else:
            xTopBetween, yTopBetween, zTopBetween = topOld[1]
            topOld = [topOld[0]] + topOld[2:]"""

        angleCurNext, angleNextNext = (horizontalIndex + 1) * commonFactorHorizontal + offset, (horizontalIndex + 2) * commonFactorHorizontal + offset
        angleBetweenNext = (angleCurNext + angleNextNext) / 2
        xTopBetweenNext, yTopBetweenNext, zTopBetweenNext = getPoint(angleUp, angleBetweenNext)

        lines += str(id) + " QUAD 0;0 0;1; 1;1 1;0 " + " ".join([s(xTopBetween, yTopBetween, zTopBetween), s(xCur, yCur, zCur), s(xNext, yNext, zNext), s(xTopBetween, yTopBetween, zTopBetween)])
        id += 1

        a = s(xTopBetweenNext, yTopBetweenNext, zTopBetweenNext)
        b = s(xTopBetween, yTopBetween, zTopBetween)
        c = s(xNext, yNext, zNext)
        d = s(xTopBetween, yTopBetween, zTopBetween)
        if not (a == b and b == d):
            lines += "\n" + str(id) + " QUAD 0;0 0;1; 1;1 1;0 " + " ".join([a, b, c, d])
            id += 1
        top += [[xTopBetween, yTopBetween, zTopBetween]]
        if topDownIndex != topDownNb - 1 or horizontalIndex != horizontalSides - 1:
            lines += "\n"
    offset += commonFactorHorizontal / 2
    #break

print(lines)

f = open(path, 'w')

f.write(texture + "\n")

f.write(lines)

f.close()