from math import cos, sin, pi

# inspired from StructuresRoundGenerator.py

polyRegSides = 5
topDownNb = 7 # 12
radius = 23 # meter
path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\658.struc"
texture = "whiteTile.jpg"
write = True

"""
b_ficusc1s_f.png
0 QUAD 1;0 1;1 0;1 0;0 -0.5;0;0 -0.5;0;1 0.5;0;1 0.5;0;0
1 QUAD 1;0 1;1 0;1 0;0 0;-0.5;0 0;-0.5;1 0;0.5;1 0;0.5;0
"""

lines = ""
commonFactorVertical = pi / topDownNb

def getPointNb(angleVertical, angleHorizontal):
    sinThetaRadius = radius * sin(angleVertical)
    return [round(x, 3) for x in (sinThetaRadius * cos(angleHorizontal), sinThetaRadius * sin(angleHorizontal), radius * cos(pi - angleVertical))]

def getPoint(angleVertical, angleHorizontal):
    l = [str(x) for x in getPointNb(angleVertical, angleHorizontal)]
    for i in range(3):
        el = l[i]
        if el[-2:] == ".0":
            el = el[:-2]
        l[i] = el
    return l

def s(x, y, z):
    return x + ";" + y + ";" + z

"""tops = []
nexts = []"""
id = 0
for topDownIndex in range(topDownNb // 2 - 1, topDownNb - 1):
    angleDown, angleUp = (topDownIndex + 1) * commonFactorVertical, (topDownIndex + 2) * commonFactorVertical
    horizontalSides = 1 + 5 * (topDownNb - 1 - topDownIndex)
    """lastTops = tops[:]
    tops = []
    lastNexts = nexts[:]
    nexts = []"""
    for horizontalIndex in range(horizontalSides):
        commonFactorHorizontal = 2 * pi / horizontalSides
        """commonFactorHorizontalTest = 2 * pi / (horizontalSides + 1)
        commonFactorHorizontalNext = 2 * pi / (horizontalSides + 5)
        commonFactorHorizontalNextNext = 2 * pi / (horizontalSides + 10)

        angleCur, angleNext = horizontalIndex * commonFactorHorizontal, (horizontalIndex + 1) * commonFactorHorizontal

        angleCurNext, angleNextNext = (horizontalIndex * 2) * commonFactorHorizontalNext, (horizontalIndex * 2 + 1) * commonFactorHorizontalNext

        ang0 = (angleCurNext + angleNextNext) / 2 - commonFactorHorizontalNext # angleCur # (angleCur + angleNext) / 2
        xCur, yCur, zCur = getPoint(angleDown, ang0) # zCur == zNext
        xCurB, yCurB, zCurB = getPoint(angleDown, angleCur * commonFactorHorizontalNext / commonFactorHorizontal)

        ang = (angleCurNext + angleNextNext) / 2 + commonFactorHorizontalNext
        xNext0, yNext0, zNext0 = getPoint(angleDown, ang) # angleNext

        xNext, yNext, zNext = getPoint(angleDown, angleNext) # angleNext

        xNextB, yNextB, zNextB = getPoint(angleDown, angleNext * commonFactorHorizontalNext / commonFactorHorizontal)

        xBottomBetween, yBottomBetween, zBottomBetween = getPoint(angleDown, (angleCur + angleNext) * commonFactorHorizontalNext / (2 * commonFactorHorizontal))

        #xTopBetween, yTopBetween, zTopBetween = getPoint(angleUp, (angleCur + angleNext) / 2)
        xTopBetween, yTopBetween, zTopBetween = getPoint(angleUp, (ang + ang0) / 2)
        xTopNextBetween, yTopNextBetween, zTopNextBetween = getPoint(angleUp, (angleCur + angleNext) / 2 + commonFactorHorizontal)

        xTopBetweenB, yTopBetweenB, zTopBetweenB = getPoint(angleUp, (angleCur + angleNext) * commonFactorHorizontalNext / (commonFactorHorizontalNext * 2))
        xTopNextBetweenB, yTopNextBetweenB, zTopNextBetweenB = xTopNextBetween, yTopNextBetween, zTopNextBetween
        #xTopNextBetweenB, yTopNextBetweenB, zTopNextBetweenB = getPoint(angleUp, (angleCur + angleNext) * commonFactorHorizontalNext / (commonFactorHorizontal * 2) + commonFactorHorizontal)

        # could also get id from computing with topDownIndex and horizontalSides and horizontalIndex
        #lines += str(id) + " QUAD 0;0 0;1; 1;1 1;0 " + " ".join([s(xCur, yCur, zCur), s(xNext, yNext, zNext), s(xTopBetween, yTopBetween, zTopBetween), s(xNext, yNext, zNext)]) + '\n'
        #zNext = str(float(zNext) + 1)

        #lines += str(id) + " QUAD 0;0 0;1; 1;1 1;0 " + " ".join([s(xCur, yCur, zCur), s(xTopBetween, yTopBetween, zTopBetween), s(xNext0, yNext0, zNext0), s(xTopBetween, yTopBetween, zTopBetween)]) + '\n'
        #fill = str(id + 1) + " QUAD 0;0 0;1; 1;1 1;0 " + " ".join([s(xBottomBetween, yBottomBetween, zBottomBetween), s(xTopBetween, yTopBetween, zTopBetween), s(xTopNextBetween, yTopNextBetween, zTopNextBetween), s(xTopBetween, yTopBetween, zTopBetween)])
        #lines += fill
        #zTopNextBetweenB = str(float(zTopNextBetweenB) + 1)
        tops += [[xTopBetweenB, yTopBetweenB, zTopBetweenB], [xTopNextBetweenB, yTopNextBetweenB, zTopNextBetweenB]]
        lines += str(id + 1) + " QUAD 0;0 0;1; 1;1 1;0 " + " ".join([s(xNext, yNext, zNext), s(xTopBetweenB, yTopBetweenB, zTopBetweenB), s(xTopNextBetweenB, yTopNextBetweenB, zTopNextBetweenB), s(xTopBetweenB, yTopBetweenB, zTopBetweenB)])
        #print(fill)
        id += 2"""
        # don't bother with triangles by just displaying triangles like in Arma 3
        if topDownIndex != topDownNb - 1 or horizontalIndex != horizontalSides - 1:
            lines += '\n'
        # don't do absorbing triangles !

print(lines)

f = open(path, 'w')

f.write(texture + '\n')

"""linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    f.write(line)
    if linesIndex != linesLen:
        f.write('\n')"""

f.write(lines)

f.close()