from os import chdir, listdir
from os.path import isfile, join
import math
from PIL import Image

lemnosLifeDir = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\"
pathCommon = lemnosLifeDir + "Map\\Common\\"
texturesPath = lemnosLifeDir + "Assets\\Downloads\\"
mapAssets = lemnosLifeDir + "Assets\\Pictures\\Map\\Ground\\"

pathStructures = pathCommon + "Structures\\"
pathItems = pathCommon + "Items\\"

path = pathStructures
#path = pathItems

chdir(path)

def getFiles(path):
    return [f for f in listdir(path) if isfile(join(path, f))]

files = getFiles(path)

def vectorialProduct(AB, AC):
    ABx, ABy, ABz = AB
    ACx, ACy, ACz = AC
    X = ABy * ACz - ABz * ACy
    Y = ABz * ACx - ABx * ACz
    Z = ABx * ACy - ABy * ACx
    return X, Y, Z

first = True
filePath = "../structureSizes.txt" if path == pathStructures else "../itemSizes.txt"

fW = open(filePath, 'w')

for file in files:
#file = pathItems + "petrol jerrycan.struc"

    if file[-6:] == ".struc":
        print(file)
        f = open(file)
        lines = f.readlines()
        f.close()

        inf = 10 ** 5
        mins = [inf] * 3
        maxs = [-inf] * 3

        texX, texY = 0, 0
        width, height = 0, 0

        quads = []
        for line in lines:
            if line[-1] == '\n':
                line = line[:-1]
            #print(line)
            lineParts = line.split()
            linePartsLen = len(lineParts)
            points = []
            if line[0] != '/' and line != "":
                if linePartsLen == 10:
                    #print(line)

                    minsTex, maxsTex = [inf] * 3, [-inf] * 3
                    for texPoint in lineParts[2:6]:
                        tT = [float(texPart) for texPart in texPoint.split(";")]
                        for tIndex in range(2):
                            tZ = tT[tIndex]
                            if tZ < minsTex[tIndex]:
                                minsTex[tIndex] = tZ
                            if tZ > maxsTex[tIndex]:
                                maxsTex[tIndex] = tZ
                    deltaTX = maxsTex[0] - minsTex[0] # is >= 0
                    deltaTY = maxsTex[1] - minsTex[1]
                    rSTX = deltaTX * width
                    rSTY = deltaTY * height
                    if rSTX > texX:
                        texX = rSTX
                    if rSTY > texY:
                        texY = rSTY

                    for point in lineParts[6:]:
                        #print(point)
                        coordinates = point.split(';')
                        coordinatesLen = len(coordinates)
                        for coordinatesIndex in range(coordinatesLen):
                            coordinate = coordinates[coordinatesIndex]
                            #if coordinate[-2:] == ".0": # doesn't solve useless ".0" bug
                            #    coordinate = coordinate[:-2]
                            coordinates[coordinatesIndex] = coordinate
                        newCoordinates = [float(coordinates[coordinatesIndex]) for coordinatesIndex in range(coordinatesLen)] # doesn't used to work with indexes but needed to remove useless ".0" end
                        for i in range(3):
                            coordinate = newCoordinates[i]
                            if coordinate < mins[i]:
                                mins[i] = coordinate
                            if coordinate > maxs[i]:
                                maxs[i] = coordinate
                        points.append(newCoordinates)
                else:
                    if line[-4:] != ".svg":
                        imagePath = texturesPath + line
                        if not os.path.isfile(imagePath):
                            imagePath = mapAssets + line
                        image = Image.open(imagePath)
                        width, height = image.size
            quads.append([points])

        #print(quads)

        #print("Mins, maxs", mins, maxs)
        realSize = [abs(ma - mi) for mi, ma in zip(mins, maxs)]
        #print("Real size", realSize)
        if not first:
            fW.write("\n")
        first = False
        id = file.split(".struc")[0].replace(" ", "_")
        realSizesStr = [str(round(s, 3)) for s in realSize]
        for i in range(3):
            realSizeStr = realSizesStr[i]
            if realSizeStr[-2:] == ".0":
                realSizeStr = realSizeStr[:-2]
            realSizesStr[i] = realSizeStr
        if path == pathStructures:
            realSizesStr = [realSizesStr[0], realSizesStr[1]] # altitude isn't important for top picture (but have take it in order to simulate a zBuffer)
            MAX_PIC_SIZE = 256
            l = []
            for realSizeStr in realSizesStr:
                parts = realSizeStr.split('.')
                partsLen = len(parts)
                l += [len(parts[1]) if partsLen >= 2 else 0] # doesn't used to be ternary

            decimals = max(l)
            x, y = [float(realSizeStr) for realSizeStr in realSizesStr]
            power = 10 ** decimals
            x, y = [int(z * power) for z in (x, y)]
            #print(x, y)
            currentGCD = math.gcd(x, y)
            while currentGCD != 1:
                x, y = [z // currentGCD for z in (x, y)]
                currentGCD = math.gcd(x, y)

            if texX > x:
                x = texX
            if texY > y:
                y = texY

            # no do while in python (such a shame)
            biggerThanMAX_PIC_SIZE = False
            for z in (x, y):
                if z > MAX_PIC_SIZE:
                    biggerThanMAX_PIC_SIZE = True
                    break
            if biggerThanMAX_PIC_SIZE:
                if x > y: # how to manage if there was more variables ?
                    y /= (x / MAX_PIC_SIZE) # order is important !
                    x = MAX_PIC_SIZE
                else:
                    x /= (y / MAX_PIC_SIZE)
                    y = MAX_PIC_SIZE # TODO: might need to round up in order to lost details like if (25001, 3) then (X, 0) so don't save
            x, y = [int(round(z, 0)) for z in (x, y)] # because int cast truncates and doesn't round
            for z in (x, y):
                if z == 0: # don't forget in C++ code to check if "key" (structure) found in file otherwise don't load any image and don't show it
                    continue
            realSizesStr = [str(z) for z in (x, y)]

        fW.write(id + " " + " ".join(realSizeStr for realSizeStr in realSizesStr))

        if path == pathStructures:
            continue

        maxVolume = 1
        for i in range(3):
            maxVolume *= realSize[i]

        #print("Max volume (L)", maxVolume * 1000)

        middle = [(maxs[i] + mins[i]) / 2 for i in range(3)]
        print(file, realSize, middle, maxs[2])

        #for quad in quads:
        #print(quad)


        #print()

fW.close()

##

"""
AB = (0, 1, 0)
AC = (1, 0, 0)

n = vectorialProduct(AB, AC)
print(n)
"""