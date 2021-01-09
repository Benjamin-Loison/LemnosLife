import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Lemnos\\Roads\\"

os.chdir(path)

f = open("roads.txt")
lines = f.readlines()
f.close()

# that's funny to define a kind of infinity here because of 1. Python convention and 2. really crazy data in roads.txt (which kiss the infinity)
INFINITY = 10 ** 10
minX, minY, maxX, maxY = INFINITY, INFINITY, -INFINITY, -INFINITY

rMinX, rMinY, rMaxX, rMaxY = 0, 0, 42740, 35580

f = open("roadsClean.txt", 'w')

linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    lineParts = line.split('@')[0].split()
    linePartsLen = len(lineParts)
    for linePartsIndex in range(linePartsLen):
        linePart = lineParts[linePartsIndex]
        linePartParts = linePart.split(',')
        # assume len(linePartParts) == 2
        x, y = [float(w) for w in linePartParts]
        if x < rMinX or y < rMinY or x > rMaxX or y > rMaxY:
            print(x, y)
            break
        if x < minX:
            minX = x
        if y < minY:
            minY = y
        if x > maxX:
            maxX = x
        if y > maxY:
            maxY = y
        #if y < 0:
        #    print(line)
    if linePartsIndex == linePartsLen - 1:
        f.write(line)

print(minX, minY, maxX, maxY)
# logical result (for Lemnos map): 3842.36 3626.93 38137.32 31661.91

f.close()