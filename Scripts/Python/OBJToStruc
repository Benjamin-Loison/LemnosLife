import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\ConverterMap\\Python\\Structures\\"
os.chdir(path)

objectName = "157" # output file need to be moved to "Extensions\LemnosLife\Map\Common\Structures\" in the game folder of "%appdata%\TerraCraft\Games\LemnosLife\Game" for instance (then a restart of the game is required if the structure is new otherwise just use button "Refresh from file" in GuiStructures in game (after selecting the correct structure))
switch = True
centimeters = True
downUp = False

objFile = open(objectName + ".obj")
lines = [line[:-1] for line in objFile.readlines()] # remove '\n'
objFile.close()

def switchYZ(txt):
    parts = txt.split(";")
    return ";".join([parts[0], parts[2], parts[1]])

def toCentimeters(txt):
    parts = txt.split(";")
    res = [str(float(x) / 100) for x in parts]
    return ";".join(res)

def reverse(txt):
    parts = txt.split(";")
    res = [parts[0], parts[1], str(-float(parts[2]))]
    return ";".join(res)

v, vt, f = [], [], []
for line in lines:
    if line[:2] == 'v ':
        res = line[2:].replace(' ', ';')
        if centimeters:
            res = toCentimeters(res)
        if downUp:
            res = reverse(res)
        if switch:
            res = switchYZ(res)
        v += [res]
    elif line[:2] == 'vt':
        vt += [line[2:]]
    elif line[:2] == 'f ':
        tmp = line[2:]
        new = ''
        tmpParts = tmp.split()
        for i in range(len(tmpParts)): # 4
            new += tmpParts[i].split('/')[0]
            if i != 3: # never achieved (used to be 3) - nop it is fine
                new += ' '
        f += [new]

"""maxi = 0
for triangle in f:
    for trianglePart in triangle.split():
        id = int(trianglePart)
        if id > maxi:
            maxi = id"""

fLen = len(f)
fLenMinus1 = fLen - 1
for triangleIndex in range(fLen):
    triangle = f[triangleIndex]
    newTriangle = '' # used to type ';' lol
    triangleParts = triangle.split()
    trianglePartsLen = len(triangleParts) # 3
    trianglePartsLenMinus1 = trianglePartsLen - 1 # 2
    for trianglePartIndex in range(trianglePartsLen):
        newTriangle += str(int(triangleParts[trianglePartIndex]) - 1)# - maxi + 1) # - 1 used to be done on each coordinates
        if trianglePartIndex != trianglePartsLenMinus1:
            newTriangle += ' '
    f[triangleIndex] = newTriangle

#print(v, f)

strucFile = open(objectName + ".struc", 'w')
strucFile.write("whiteNoise.jpg\n")

for triangleIndex in range(fLen):
    triangle = f[triangleIndex]
    parts = triangle.split()

    coordinates = v[int(parts[0])] + " " + v[int(parts[1])] + " " + v[int(parts[2])] + " "
    #if (len(parts) == 4): # doesn't seem useful - it is useful
    #    print("HEY")
    coordinates += (v[int(parts[3])] if (len(parts) == 4) else v[int(parts[2])]) # so last case is used

    strucFile.write(str(triangleIndex) + " QUAD 1;0 1;1 0;1 0;0 " + coordinates)

    if triangleIndex != fLenMinus1:
        strucFile.write('\n')

strucFile.close()

# barycentre
