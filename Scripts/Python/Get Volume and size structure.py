from os import chdir, listdir
from os.path import isfile, join

pathCommon = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\"

pathStructures = pathCommon + "Structures\\"
pathItems = pathCommon + "Items\\"

#path = pathStructures
path = pathItems

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

for file in files:
#file = pathItems + "petrol jerrycan.struc"

    print(file)
    f = open(file)
    lines = f.readlines()
    f.close()

    inf = 10 ** 5
    mins = [inf] * 3
    maxs = [-inf] * 3

    quads = []
    for line in lines:
        if line[-1] == '\n':
            line = line[:-1]
        #print(line)
        lineParts = line.split()
        linePartsLen = len(lineParts)
        if line != "" and line[0] != '/' and linePartsLen == 10:
            #print(line)
            points = []
            for point in lineParts[6:]:
                #print(point)
                coordinates = point.split(';')
                newCoordinates = [float(coordinate) for coordinate in coordinates]
                for i in range(3):
                    coordinate = newCoordinates[i]
                    if coordinate < mins[i]:
                        mins[i] = coordinate
                    if coordinate > maxs[i]:
                        maxs[i] = coordinate
                points.append(newCoordinates)
        quads.append([points])

    #print(quads)

    #print("Mins, maxs", mins, maxs)
    realSize = [abs(ma - mi) for mi, ma in zip(mins, maxs)]
    print("Real size", realSize)

    maxVolume = 1
    for i in range(3):
        maxVolume *= realSize[i]

    print("Max volume (L)", maxVolume * 1000)

    middle = [(maxs[i] + mins[i]) / 2 for i in range(3)]
    print(middle)

    for quad in quads:
       print(quad)


    print()

##

AB = (0, 1, 0)
AC = (1, 0, 0)

n = vectorialProduct(AB, AC)
print(n)
