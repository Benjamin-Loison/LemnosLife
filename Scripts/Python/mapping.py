import os, random, math, datetime
import numpy as np
from shapely.geometry import Point
from shapely.geometry.polygon import Polygon
import matplotlib.pyplot as plt

#pathStructuresShadowsFile = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\structuresShadow.txt"
pathStructuresShadowsFile = "structuresShadowModified.txt"
# could do a perfect 3D collision ("perfect" because get shape of not transparent)

WSL = False
def WSLPath(path):
    if WSL:
        path = path.replace("C:\\", "/mnt/c/").replace("\\", "/")
    return path

pathObjectsFolder = WSLPath("C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Lemnos\\Objects\\")

path = WSLPath("C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Mess\\LemnosMap\\")

BEGIN_GRAVE_YARD = "<way " # is it really only grave ? DOUBT X
END_GRAVE_YARD = "</way>"
LINES_DEFAULT = -1
NODE = '<nd ref="'
NODE_LOCATION = '<node id="'
LAT_STR = ' lat="'
LON_STR = ' lon="'

# according to Lemnos' data.txt
LON_MIN = 25.00
LON_MAX = 25.50
LAT_MIN = 39.75
LAT_MAX = 40.07
X_MAX = 42740.0
Y_MAX = 35580.0
SUB_CHK_SIZE = 100
CHK_SIZE = 1000
SUB_CHK_PER_CHK = CHK_SIZE // SUB_CHK_SIZE
STRUC_DENSITY_GRAVE_YARD = 0.01#0.01 # per square meter
STRUC_TO_PLACE_ID = 35
MIN_DISTANCE_BETWEEN_STRUC = 3#1.2#3 # could also use perfect collision model (or at least with rectangle)
#WHITELIST_STRUC_COLLISION =

os.chdir(path)

f = open("OSM.xml", encoding="utf-8")
lines = f.readlines()
f.close()

linesLen = len(lines)

def getLines(linesIndexDefault):
    linesIndex = linesIndexDefault
    linesMin, linesMax = LINES_DEFAULT, LINES_DEFAULT
    #print("doing min")
    while linesIndex >= 0 and linesMin == LINES_DEFAULT:
        line = lines[linesIndex]
        if BEGIN_GRAVE_YARD in line:
            linesMin = linesIndex # could add a break ?
        linesIndex -= 1
    #print("doing max")
    linesIndex = linesIndexDefault
    while linesIndex < linesLen and linesMax == LINES_DEFAULT:
        line = lines[linesIndex]
        if END_GRAVE_YARD in line:
            linesMax = linesIndex
        linesIndex += 1
    return linesMin, linesMax

def getNodes(linesT):
    nodes = []
    linesTLen = len(linesT)
    for linesIndex in range(linesTLen):
        line = linesT[linesIndex]
        #print(line)
        if NODE in line:
            nodes += [line.split(NODE)[1].split('"/>')[0]]
    return nodes

def getNodesFromLine(linesIndex):
    linesMin, linesMax = getLines(linesIndex)
    linesLocal = lines[linesMin + 1: linesMax]
    return getNodes(linesLocal)

# could also look for only used nodes (are they all used ?)
lonLatTab = {}
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    #needle = NODE_LOCATION
    if NODE_LOCATION in line: # used to be needle lol
        nodeId = line.split(NODE_LOCATION)[1].split('"')[0]
        lon = float(line.split(LON_STR)[1].split('"')[0])
        lat = float(line.split(LAT_STR)[1].split('"')[0])
        lonLatTab[nodeId] = [lon, lat]

if False:
    fT = open("lonLat.txt", 'w')
    ll = len(lonLatTab)
    i = 0
    for nodeId in lonLatTab:
        lon, lat = lonLatTab[nodeId]
        fT.write(str(nodeId) + " " + str(lon) + " " + str(lat))
        if i != ll -1:
            fT.write('\n')
        i += 1
    fT.close()

def getLonLat(nodeId): # could make an array instead of such a complexity - done (was required for average OSM)
    return lonLatTab[nodeId]
    """for linesIndex in range(linesLen):
        line = lines[linesIndex]
        needle = NODE_LOCATION + nodeId + '"'
        #print(needle)
        if needle in line:
            lon = float(line.split(LON_STR)[1].split('"')[0])
            lat = float(line.split(LAT_STR)[1].split('"')[0])
            return lon, lat
    return None"""

LON_FACT = X_MAX / (LON_MAX - LON_MIN)
LAT_FACT = Y_MAX / (LAT_MAX - LAT_MIN)

def getCoordinates(lon, lat):
    x = (lon - LON_MIN) * LON_FACT
    y = (lat - LAT_MIN) * LAT_FACT
    return x, y

def getCoordinatesFromNodeId(nodeId):
    lon, lat = getLonLat(nodeId)
    return getCoordinates(lon, lat)

# https://stackoverflow.com/a/30408825
def getAreaOfPolygon(X, Y):
    return 0.5 * np.abs(np.dot(X, np.roll(Y, 1)) - np.dot(Y, np.roll(X, 1)))

def getPolygon(linesIndex):
    nodes = getNodesFromLine(linesIndex)
    X, Y = [], []
    for node in nodes:
        #print(node)
        x, y = getCoordinatesFromNodeId(node)
        X += [x]
        Y += [y]
    return X, Y

def getAreaFromLine(linesIndex):
    X, Y = getPolygon(linesIndex)
    return getAreaOfPolygon(X, Y)

def smallestRectangleContaining(X, Y):
    xMin, xMax, yMin, yMax = X[0], X[0], Y[0], Y[0]
    for x in X: # could avoid first number
        if x < xMin:
            xMin = x
        elif x > xMax: # elif always works (instead of if) because of this initizialition of xMin etc
            xMax = x
    for y in Y:
        if y < yMin:
            yMin = y
        elif y > yMax:
            yMax = y
    return xMin, xMax, yMin, yMax

# could use X, Y in order to optimize in the big loop to process whole map
def getAreaSmallestRectangleContaining(linesIndex):
    X, Y = getPolygon(linesIndex)
    xMin, xMax, yMin, yMax = smallestRectangleContaining(X, Y)
    return (yMax - yMin) * (xMax - xMin)

def structureNumber(linesIndex):
    return STRUC_DENSITY_GRAVE_YARD * getAreaFromLine(linesIndex)

def getHowManyRandomInSmallestRectangleContaining(linesIndex, wholeMap = False):
    if wholeMap:
        realArea = X_MAX * Y_MAX
        smallestRectangleArea = realArea
        realRandom = STRUC_DENSITY_GRAVE_YARD * realArea
    else:
        realArea = getAreaFromLine(linesIndex)
        smallestRectangleArea = getAreaSmallestRectangleContaining(linesIndex)
        # reminder, we always have: smallestRectangleArea >= realArea
        realRandom = structureNumber(linesIndex)
    rectangleRandom = math.ceil(realRandom * smallestRectangleArea / realArea)
    # two randomness: location and "real" number because if not in real area, structure not placed (+ min distance)
    return rectangleRandom

# https://stackoverflow.com/a/36400130
def isIn(x, y, X, Y):
    point = Point(x, y)
    points = [(x, y) for x, y in zip(X, Y)]
    polygon = Polygon(points)
    return polygon.contains(point)

def isNotInAnyCollisions(x, y):
    for collisionsIndex in range(collisionsLen):
        X, Y = [], []
        collision = collisions[collisionsIndex]
        for point in collision:
            x, y = point[0], point[1]
            X += [x]
            Y += [y]
        X += [collision[0][0]]
        Y += [collision[0][1]]
        if isIn(x, y, X, Y):
            return False
    return True

def distance(x0, y0, x1, y1):
    return (((x1 - x0) ** 2 + (y1 - y0) ** 2)) ** 0.5

def isEnoughlyFarAway(x, y, XR, YR, d):
    for xr, yr in zip(XR, YR):
        if distance(xr, yr, x, y) <= d:
            return False
    return True

# may need to use a blacklist or whitelist for this not superposing problem -> whitelist structures to test is the best way for the moment
f = open(pathStructuresShadowsFile)
shadowsLines = f.readlines()
f.close()

shadows = {}

shadowsLinesLen = len(shadowsLines)
for shadowsLinesIndex in range(shadowsLinesLen):
    shadowsLine = shadowsLines[shadowsLinesIndex]
    shadowsLineParts = shadowsLine.split() # don't check len in order to notice file corruption
    strucId = int(shadowsLineParts[0])
    shadows[strucId] = [float(shadowsLineParts[i]) for i in range(1, 5)]

collisions = []

# https://stackoverflow.com/a/34374437
def rotate(point, angle): # angle in rad
    px, py = point
    qx = math.cos(angle) * px - math.sin(angle) * py
    qy = math.sin(angle) * px + math.cos(angle) * py
    return [qx, qy] # otherwise it is a tuple

def rotateShadow(strucId, origin, angle):
    minX, maxX, minY, maxY = shadows[strucId]
    # is it x or y first ?
    points = [[minX, minY], [maxX, minY], [maxX, maxY], [minX, maxY]]
    for pointsIndex in range(4):
        point = points[pointsIndex]
        #points[pointsIndex] = rotate(point, angle) + origin # is '+' well defined here ? - it seems so - nop finally
        r = rotate(point, angle)
        points[pointsIndex] = [r[0] + origin[0], r[1] + origin[1]]
        #print(origin, points[pointsIndex])
    #collisions += [points]
    return points

for r, d, files in os.walk(pathObjectsFolder):
    filesLen = len(files)
    for filesIndex in range(filesLen):
        file = files[filesIndex]
        f = open(pathObjectsFolder + file)
        objectsLines = f.readlines()
        f.close()
        file = file.replace('.objects', '')
        fileParts = file.split()
        chkX , chkY, subChkX, subChkY = int(fileParts[0]), int(fileParts[1]), -1, -1
        objectsLinesLen = len(objectsLines)
        for objectsLinesIndex in range(objectsLinesLen):
            objectsLine = objectsLines[objectsLinesIndex]
            objectsLineParts = objectsLine.split()
            objectsLinePartsLen = len(objectsLineParts)
            if objectsLinePartsLen == 2:
                subChkX = int(objectsLineParts[0])
                subChkY = int(objectsLineParts[1])
            elif objectsLinePartsLen == 5:
                #instance = [barycenter, angle] # intermediary
                strucId = int(objectsLineParts[0]) # what happends if isn't an integer ?
                if strucId in shadows:
                    # reminder: we work in 2D (so no z) - for the moment at least
                    origin = [float(objectsLineParts[1]) + subChkX * SUB_CHK_SIZE + chkX * CHK_SIZE, float(objectsLineParts[2]) + subChkY * SUB_CHK_SIZE + chkY * CHK_SIZE]
                    angle = math.radians(-int(objectsLineParts[4]))
                    instance = rotateShadow(strucId, origin, angle)
                    # [[x0, y0], [x1, y1], [x2, y2], [x3, y3]]
                    collisions += [instance]
collisionsLen = len(collisions)

# should also consider roads
def isThereNoCollisions(points, wholeMap):
    p1 = Polygon(points)
    x0, y0 = points[0]
    for collisionsIndex in range(collisionsLen):
        collision = collisions[collisionsIndex]
        x1, y1 = collision[0]
        if wholeMap and (x1 - x0) ** 2 + (y1 - y0) ** 2 > 625: # 15 * 15 = 225 # 25 *25 = 625
            continue
        p2 = Polygon(collision)
        if p1.intersects(p2):
            return False
    return True

def generateRandom(linesIndex, renderPlot = False, wholeMap = False):
    rectangleRandom = getHowManyRandomInSmallestRectangleContaining(linesIndex, wholeMap)
    if wholeMap:
        X = [0, 0, X_MAX, X_MAX, 0] # is last component really necessary ?
        Y = [0, Y_MAX, Y_MAX, 0, 0]
    else:
        X, Y = getPolygon(linesIndex)
        #print(X, Y)
    xMin, xMax, yMin, yMax = smallestRectangleContaining(X, Y)
    if wholeMap:
        print("Generate random basics done")
    XR, YR, angles = [], [], []
    print("rectangleRandom: " + str(rectangleRandom))
    for i in range(rectangleRandom):
        if i % 10000 == 0:
            print(str(i) + " / " + str(rectangleRandom))
        x, y, angle = random.uniform(xMin, xMax), random.uniform(yMin, yMax), random.uniform(0, 2 * math.pi)
        #isFar = isEnoughlyFarAway(x, y, XR, YR, MIN_DISTANCE_BETWEEN_STRUC)
        if wholeMap or (isEnoughlyFarAway(x, y, XR, YR, MIN_DISTANCE_BETWEEN_STRUC) and isIn(x, y, X, Y)):#isIn(x, y, X, Y) and :# and isNotInAnyCollisions(x, y):
            points = rotateShadow(STRUC_TO_PLACE_ID, [x, y], angle)
            XC, YC = [], []
            for point in points:
                XC += [point[0]]
                YC += [point[1]]
            XC += [points[0][0]]
            YC += [points[0][1]]

            if isThereNoCollisions(points, wholeMap): # may also have to check if point is not in
                XR += [x]
                YR += [y]
                angles += [angle]
                if renderPlot:
                    plt.plot(XC, YC, color='blue')
    if renderPlot:
        plt.plot(X, Y, color='green')
        plt.scatter(XR, YR, color = 'blue')
    diagonal = distance(xMin, yMin, xMax, yMax)
    #print(diagonal)
    for collisionsIndex in range(collisionsLen):
        #print(collisionsIndex, collisionsLen)
        XT, YT = [], []
        collision = collisions[collisionsIndex]
        show = True
        for point in collision:
            x, y = point[0], point[1]
            XT += [x]
            YT += [y]
            #print(x, y)
            #return None
        XT += [collision[0][0]]
        YT += [collision[0][1]]
        dis = distance(x, y, X[0], Y[0])
        #print(dis)
        if dis < diagonal: # it is roughly this
            # otherwise it is very slow
        #if not isEnoughlyFarAway(x, y, X, Y, 100): # could consider diagonal length of the rectangle instead of constant 100
            #show = False
            #break
        #if show:
            if renderPlot:
                plt.plot(XT, YT, color='black')
    if renderPlot:
        plt.axis('equal')
        plt.show()
    return XR, YR, angles

# make blue dots not in black rectangle AND not considering only blue dot but real rectangle - done

def strInt(x):
    return str(int(x))

def rd(x):
    return round(x, 2)

# TODO: offset due to consideration that the planet is locally flat ?
# TODO: but first optimize ^^

underWater = 0

def write(strucId, x, y, angle, z = None, wholeMap = False):
    global underWater
    #x, y = rd(x), rd(y) # doesn't work after % SUB_CHK_SIZE otherwise
    chkX, chkY = x // CHK_SIZE, y // CHK_SIZE
    file = pathObjectsFolder + strInt(chkX) + " " + strInt(chkY) + ".objects"
    subChkX, subChkY = (x // SUB_CHK_SIZE) % SUB_CHK_PER_CHK, (y // SUB_CHK_SIZE) % SUB_CHK_PER_CHK
    #print(subChkX, strInt(subChkX), type(subChkX), type(strInt(subChkX)))
    subChkHeader = strInt(subChkX) + " " + strInt(subChkY)
    if z is None:
        z = getGroundAltitude(x, y)
        if wholeMap and z <= 1:
            underWater += 1
            #print("Abort because under the sea")
    line = str(strucId) + " " + str(rd(x % SUB_CHK_SIZE)) + " " + str(rd(y % SUB_CHK_SIZE)) + " " + str(rd(z)) + " " + str(angle) # is there useless .0 generate here ? # altitude used to be a constant ^^

    if os.path.isfile(file):
        #print("exists")
        f = open(file, 'r')
        fLines = f.readlines()
        f.close()
    else:
        #print("doesn't exist")
        fLines = []
    fLinesLen = len(fLines)

    subChkHeaderPresent = False
    for fLinesIndex in range(fLinesLen):
        fLine = fLines[fLinesIndex]
        if fLine[:-1] == subChkHeader:
            subChkHeaderPresent = True
            subChkHeaderIndex = fLinesIndex
            break
        #print(fLine)

    f = open(file, 'w')
    if subChkHeaderPresent: # a logical order is also to reverse order of if/else
        for fLinesIndex in range(fLinesLen):
            fLine = fLines[fLinesIndex]
            f.write(fLine)
            if fLinesIndex == subChkHeaderIndex:
                #f.write(subChkHeader + '\n')
                f.write(line + '\n')
    else:
        for fLinesIndex in range(fLinesLen): # could also do this in one line
            fLine = fLines[fLinesIndex]
            f.write(fLine)
        if fLinesLen != 0:
            f.write('\n')
        f.write(subChkHeader + '\n')
        f.write(line)
        #if fLines != []: # this doesn't make sens !
        #    f.write('\n')

    f.close()

def writeFromLinesIndex(linesIndex, wholeMap = False):
    XR, YR, angles = generateRandom(linesIndex, False, wholeMap)
    qt = len(XR)
    print(qt)
    print("Gonna write !")
    for x, y, angle in zip(XR, YR, angles):
        write(STRUC_TO_PLACE_ID, x, y, int(math.degrees(angle)), wholeMap)

# make a getZ function (don't rely on C++) - done

CHUNK_GROUND_SIZE = 1000.0
SEA_BOTTOM = -100.0
SUB_CHUNK_GROUND_SIZE = 10.0

pathToHeightFolder = WSLPath("C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Lemnos\\Ground\\")

def toFloat(s):
    return SEA_BOTTOM if s == 'N' else float(s)

mapChunkHeights = {}

for r, d, files in os.walk(pathToHeightFolder):
    filesLen = len(files)
    for filesIndex in range(filesLen):
        file = files[filesIndex]
        #print(str(filesIndex) + " / " + str(filesLen))
        chunkName = file.split('.')[0]
        chunkNameParts = chunkName.split()
        chkXThousand, chkYThousand = int(chunkNameParts[0]) * CHUNK_GROUND_SIZE, int(chunkNameParts[1]) * CHUNK_GROUND_SIZE
        f = open(pathToHeightFolder + file)
        linesF = f.readlines()
        f.close()

        linesFLen = len(linesF) - 1
        lineChunksHeights = []

        for lineIndex in range(linesFLen):
            #partsCurrentLine, partsNextLine = linesF[lineIndex].split(), linesF[lineIndex + 1].split()
            partsCurrentLine = linesF[lineIndex].split()

            partsCurrentLineLen = len(partsCurrentLine) - 1
            columnChunksHeights = []
            for columnIndex in range(partsCurrentLineLen):
                chkYThousandPlusChunkGroundSize = chkYThousand + CHUNK_GROUND_SIZE
                #xMin, yMin, xMax, yMax = chkXThousand + columnIndex * SUB_CHUNK_GROUND_SIZE, chkYThousandPlusChunkGroundSize - lineIndex * SUB_CHUNK_GROUND_SIZE, chkXThousand + (columnIndex + 1) * SUB_CHUNK_GROUND_SIZE, chkYThousandPlusChunkGroundSize - (lineIndex + 1) * SUB_CHUNK_GROUND_SIZE
                xMin, yMin = chkXThousand + columnIndex * SUB_CHUNK_GROUND_SIZE, chkYThousandPlusChunkGroundSize - lineIndex * SUB_CHUNK_GROUND_SIZE

                z0 = toFloat(partsCurrentLine[columnIndex])
                #z0, z1, z2, z3 = toFloat(partsCurrentLine[columnIndex]), toFloat(partsCurrentLine[columnIndex + 1]), toFloat(partsNextLine[columnIndex + 1]), toFloat(partsNextLine[columnIndex])
                vertex = [xMin, yMin, z0]
                """
                    ,
                    xMax, yMin, z1,
                    xMax, yMax, z2,
                    xMin, yMax, z3]
                """

                columnChunksHeights += [vertex]
            lineChunksHeights += [columnChunksHeights]
        mapChunkHeights[chunkName] = lineChunksHeights

# mapChunkHeights: map<vector<vector<vector<double>>>> here

#for key in mapChunkHeights:
#    print(key)

def getChunk1kName(coordinates):
    coo = [-1, -1]
    for i in [0, 1]:
        coo[i] = math.floor(coordinates[i]) // CHUNK_GROUND_SIZE
    return strInt(coo[0]) + " " + strInt(coo[1])

def indexInMatrix(coordinate):
    return int((coordinate % CHUNK_GROUND_SIZE) // SUB_CHUNK_GROUND_SIZE)

def getGroundAltitude(x, y):
    coordinates, coordinatesRight, coordinatesTop, coordinatesTopRight = [x, y], [x + CHUNK_GROUND_SIZE, y], [x, y - CHUNK_GROUND_SIZE], [x + CHUNK_GROUND_SIZE, y - CHUNK_GROUND_SIZE]

    chkName, chkNameRight, chkNameTop, chkNameTopRight = getChunk1kName(coordinates), getChunk1kName(coordinatesRight), getChunk1kName(coordinatesTop), getChunk1kName(coordinatesTopRight)

    #print(chkName, chkNameRight, chkNameTop, chkNameTopRight)

    if not chkName in mapChunkHeights:
        return SEA_BOTTOM

    matrix = mapChunkHeights[chkName]

    indexX, indexY, matrixSize = indexInMatrix(x), indexInMatrix(y) + 1, int(CHUNK_GROUND_SIZE / SUB_CHUNK_GROUND_SIZE)

    matrixSizeMinusIndexY = matrixSize - indexY
    indexXPlusOne = indexX + 1
    if len(matrix) <= matrixSizeMinusIndexY:
        return 0
    A = matrix[matrixSizeMinusIndexY][indexX]

    if indexX + 1 >= matrixSize:
        if not chkNameRight in mapChunkHeights:
            return SEA_BOTTOM
        matrixRight = mapChunkHeights[chkNameRight]
        B = matrixRight[matrixSizeMinusIndexY][0]
    else:
        B = matrix[matrixSizeMinusIndexY][indexXPlusOne]

    if indexY == 1:
        if not chkNameTop in mapChunkHeights:
            return SEA_BOTTOM
        matrixTop = mapChunkHeights[chkNameTop]
        C = matrixTop[0][indexX]
    else:
        C = matrix[matrixSizeMinusIndexY + 1][indexX]

    if indexXPlusOne >= matrixSize:
        if indexY == 1:
            if not chkNameTopRight in mapChunkHeights:
                return SEA_BOTTOM
            matrixTopRight = mapChunkHeights[chkNameTopRight]
            D = matrixTopRight[0][0]
        else:
            D = matrixRight[matrixSizeMinusIndexY + 1][0]
    else:
        D = matrixTop[0][indexXPlusOne] if indexY == 1 else matrix[matrixSizeMinusIndexY + 1][indexXPlusOne]

    P = [x, y, 0]

    groundAltitude = groundAltitudePoints(A, B, C, D, P)
    return groundAltitude

def Vector3D(A, B):
    return [B[i] - A[i] for i in range(3)]

def Vector2D(A, B):
    return [B[i] - A[i] for i in range(2)]

def groundAltitudeTopLeft(A, AB, AD, P):
    abZ, adZ = AB[2] * ((SUB_CHUNK_GROUND_SIZE - P[0]) / SUB_CHUNK_GROUND_SIZE), AD[2] * ((SUB_CHUNK_GROUND_SIZE - P[1]) / SUB_CHUNK_GROUND_SIZE)
    return A[2] + abZ + adZ

def groundAltitudeTopRight(B, DC, BC, P):
    dcZ, bcZ = DC[2] * ((P[0]) / SUB_CHUNK_GROUND_SIZE), BC[2] * ((P[1]) / SUB_CHUNK_GROUND_SIZE)
    return B[2] + dcZ + bcZ

def moduloVector(vec, modulo):
    return [vec[0] % modulo, vec[1] % modulo, vec[2]]

def groundAltitudePoints(A, B, C, D, P):
    AN, BN, CN, DN, PN = [0, SUB_CHUNK_GROUND_SIZE, A[2]], [SUB_CHUNK_GROUND_SIZE, SUB_CHUNK_GROUND_SIZE, B[2]], [SUB_CHUNK_GROUND_SIZE, 0, C[2]], [0, 0, D[2]], moduloVector(P, SUB_CHUNK_GROUND_SIZE)
    return groundAltitudeTopLeft(BN, Vector3D(BN, AN), Vector3D(BN, DN), PN) if pointIsInTriangle(PN, AN, BN, CN) else groundAltitudeTopRight(CN, Vector3D(CN, DN), Vector3D(CN, AN), PN)

def determinant2(AB, AP):
    return AB[0] * AP[1] - AB[1] * AP[0]

def determinant(A, B, P):
    return determinant2(Vector2D(A, B), Vector2D(A, P))

def pointIsInTriangle(P, A, B, C):
    return determinant(A, B, P) <= 0 and determinant(B, C, P) <= 0 and determinant(C, A, P) <= 0

"""def groundAltitudePoints(A, B, D, P):
    AB, AD = [B[0] - A[0], B[1] - A[1], B[2] - A[2]], [D[0] - A[0], D[1] - A[1], D[2] - A[2]]
    return groundAltitude(A, AB, AD, P)

def groundAltitude(A, AB, AD, P):
    abZ, adZ = AB[2] * (SUB_CHUNK_GROUND_SIZE - P[0]) / SUB_CHUNK_GROUND_SIZE, AD[2] * (SUB_CHUNK_GROUND_SIZE - P[1]) / SUB_CHUNK_GROUND_SIZE
    return A[2] + abZ + adZ"""

def shortEl(el):
    return round(el, 2)

def short(l):
    return [shortEl(el) for el in l]

if True:
    myPosition = [5469.67, 14409.62]

    for linesIndex in range(linesLen):
        line = lines[linesIndex]
        if "grave_yard" in line:# and linesIndex == 531157:#603473:
            nodeId = getNodesFromLine(linesIndex)[0]
            lon, lat = getLonLat(nodeId)
            coo = short(getCoordinates(lon, lat))
            alt = shortEl(getGroundAltitude(coo[0], coo[1]))
            if alt > 0:
                d = shortEl(distance(myPosition[0], myPosition[1], coo[0], coo[1]))
                area = getAreaFromLine(linesIndex)
                latLon = str(lat) + "," + str(lon)
                tpCmd = "'/TP " + str(coo[0]) + "," + str(coo[1]) + "," + str(alt) + "'"
                print(linesIndex, coo, d, alt, tpCmd, latLon, shortEl(area))
                writeFromLinesIndex(linesIndex)

#writeFromLinesIndex(-1, True)
#print("Total underwater: " + str(underWater))
#exit(0)

##

CST_F = '.'
CST_T = '#'

from PIL import Image
import time, _thread # threading,

beginTime = time.time()
def getTime():
    return time.time() - beginTime

FACTOR = 100
MAX_SIZE = 256
GTX, GTY = 4600, 4770

def getPicStr(pic):
    picY, picX = len(pic), len(pic[0])
    s = ""
    for y in range(picY):
        for x in range(picX):
            s += str(pic[y][x])
        if y != picY - 1:
            s += '\n'
    return s

def printPic(pic):
    print(getPicStr(pic))

def savePic(pic, path):
    s = getPicStr(pic)
    f = open(path, 'w')
    f.write(s)
    f.close()

def similarityOneToOther(pic0, pic1):
    pic0Y, pic0X = len(pic0), len(pic0[0])
    pic1Y, pic1X = len(pic1), len(pic1[0])
    #print("pic0Y, pic0X: " + str(pic0Y) + " " + str(pic0X))
    #print("pic1Y, pic1X: " + str(pic1Y) + " " + str(pic1X))
    if pic0Y > pic1Y or pic0X > pic1X: ## this statement is a temporary one, it ejects every building which is bigger than in the real world, to avoid but currently have bugs with big structure which absorb little ones
        #print("too small guys !")
        return 0 # this happends sometimes when a building is bigger than all of mine :/
    yMax, xMax = min(pic0Y, pic1Y), min(pic0X, pic1X)

    """print("pic0 start")
    printPic(pic0)
    print("pic0 stop")"""

    """print("pic1 start")
    printPic(pic1)
    print("pic1 stop")"""

    s, total = 0, max(pic0Y, pic1Y) * max(pic0X, pic1X) #yMax * xMax # sure ?
    #print("yMax, xMax: " + str(yMax) + " " + str(xMax))
    for y in range(yMax):
        for x in range(xMax):
            if pic0[y][x] == pic1[y][x]:
                s += 1
    #print("res: " + str(s) + " " + str(total))
    res = 100 * s / total
    #print(res, s, total, yMax, xMax)
    return res

def tab(x, y):
    pic = []
    l = [CST_F] * x
    for y in range(y):
        pic += [l[:]]
    return pic

def extract(pic):
    y, x = len(pic), len(pic[0])
    xMin, xMax, yMin, yMax = 0, 0, 0, 0
    yI, notBreak = 0, True # used also to initilize xI here :')
    while yI < y and notBreak:
        xI = 0
        while xI < x and notBreak:
            if pic[yI][xI] == CST_T:
                yMin = yI
                notBreak = False
            xI += 1
        yI += 1

    xI, notBreak = 0, True
    while xI < x and notBreak:
        yI = 0
        while yI < y and notBreak:
            if pic[yI][xI] == CST_T:
                xMin = xI
                notBreak = False
            yI += 1
        xI += 1

    yI, notBreak = y - 1, True
    while yI >= 0 and notBreak:
        xI = 0
        while xI < x and notBreak:
            if pic[yI][xI] == CST_T:
                yMax = yI
                notBreak = False
            xI += 1
        yI -= 1

    xI, notBreak = x - 1, True
    while xI >= 0 and notBreak:
        yI = 0
        while yI < y and notBreak:
            if pic[yI][xI] == CST_T:
                xMax = xI
                notBreak = False
            yI += 1
        xI -= 1
    """for yI in range(s):
        for xI in range(s):
            if pic[yI][xI] == CST_T:
                yMin = yI

    for xI in range(s):
        for yI in range(s):
            if pic[yI][xI] == CST_T:
                xMin = xI

    for yI in range(s + 1, -1, -1):
        for xI in range(s):
            if pic[yI][xI] == CST_T:
                yMax = yI

    for xI in range(s + 1, -1, -1):
        for xI in range(s):
            if pic[yI][xI] == CST_T:
                xMax = xI"""
    #print(xMax, xMin, yMax, yMin)
    #return pic
    extracted = tab(xMax - xMin + 1, yMax - yMin + 1)
    for yI in range(yMin, yMax + 1):
        for xI in range(xMin, xMax + 1):
            #print(xI, yI, yI - yMin, xI - xMin, xMax - xMin + 1, yMax - yMin + 1, y, x)
            extracted[yI - yMin][xI - xMin] = pic[yI][xI]
    return extracted

dbgIndex = 0

def myRound(x):
    if x % 1 == 0.5:
        return x - 0.5
    return round(x)

def redim(pic, x, y):
    global dbgIndex # face (pile ou face)
    #return pic
    picY, picX = len(pic), len(pic[0])
    res = tab(x, y)
    #print("pic start")
    #printPic(pic)
    #print("pic stop")
    factFX, factFY = (picX - 1) / (x - 1), (picY - 1) / (y - 1)
    """print("x, y: " + str(x) + " " + str(y))
    print("picX, picY: " + str(picX) + " " + str(picY))
    print("factFX, factFY: " + str(factFX) + " " + str(factFY))"""
    for yT in range(y):
        for xT in range(x):
            xI = int(myRound(xT * factFX)) # round(0.5) = 0 en Python et 1 en C++ :raging:
            yI = int(myRound(yT * factFY))
            """if xT == x - 1 and dbgIndex == 360: # using # here and triple quotes for indented block doesn't work, love it python !
                print("dbgIndex: " + str(dbgIndex))
                print("xI, yI: " + str(xI) + " " + str(yI))
                print("xT, factFX: " + str(xT) + " " + str(factFX))
                print("yT, factFY: " + str(yT) + " " + str(factFY))
                if yT == 39:
                    print("yT == 39 ok")
                if xT == 0.5:
                    print("xT == 0.5 ok")
                if yT == 39 and xT == 0.5:
                    print("I like rounding down but sometimes up for a half")"""
            res[yT][xT] = pic[yI][xI]
        #break
    #printPic(res)
    #exit(0)
    #dbgIndex += 1
    return res

def rotates(x, y, angle):
    angleRad = math.radians(angle)
    xMin, xMax, yMin, yMax = None, None, None, None
    points = [[x, 0], [x, y], [0, 0], [0, y]]
    for point in points:
        x, y = rotate(point, angleRad)
        if xMax is None or x > xMax:
            xMax = x
        if xMin is None or x < xMin:
            xMin = x
        if yMax is None or y > yMax:
            yMax = y
        if yMin is None or y < yMin:
            yMin = y
    #print(xMin, xMax, yMin, yMax)
    return math.ceil(xMax - xMin), math.ceil(yMax - yMin)

DBG = 2

def toString(pic):
    return str(len(pic)) + " " + str(len(pic[0]))

def rotatePic(pic, angle):
    #angle = 0
    #print("pic: " + toString(pic))
    angleRad = math.radians(angle)
    y, x = len(pic), len(pic[0])
    d = (y * y + x * x) ** 0.5
    #print([x, y], angle)
    rot = rotates(x, y, angle)
    #print(x, y, rot)
    #rot = rotate([x, y], angleRad)
    #print(rot)
    #rot[0] = abs(int(round(rot[0], 0)))
    #rot[1] = abs(int(round(rot[1], 0)))
    #print(rot)
    #s = math.ceil(d) # used to be * 2
    #sX, sY = s, s
    sX, sY = rot
    factX, factY = (x - 1) / (sX - 1), (y - 1) / (sY - 1)
    """print("pic start")
    printPic(pic)
    print("pic stop")"""
    rotatedBig = tab(sX, sY)
    # rotated (balayage) to original is better than the reverse
    xC, yC = x // 2, y // 2
    for yT in range(sY):
        for xT in range(sX):
            verbose = False#yT == sY - 1 and xT == sX - 1
            xI = xT * factX
            yI = yT * factY
            if verbose:
                print(xT, yT, xI, yI)
            #xI /= 2
            #yI /= 2
            xI -= xC
            yI -= yC

            # I can't think about this problem anymore so I cheat sorry bro', but here we loose in structure quality
            xI *= DBG
            yI *= DBG

            if verbose:
                print(xI, yI, xC, yC)
            point = [xI, yI]
            point = rotate(point, angleRad)
            #if verbose:
            #    print(point)
            #point[0] = abs(point[0])
            #point[1] = abs(point[1])
            if verbose:
                print(point)
            point[0] += xC
            point[1] += yC
            if verbose:
                print(point)
            point[0] = int(myRound(point[0]))
            point[1] = int(myRound(point[1]))
            if verbose:
                print(point)
            #print(yT, xT, point)
            if point[1] < y and point[1] >= 0 and point[0] < x and point[0] >= 0:
                rotatedBig[yT][xT] = pic[point[1]][point[0]]
    """print("rotatedBig start")
    printPic(rotatedBig)
    print("rotatedBig stop")
    print("rotatedBig: " + toString(rotatedBig))"""
    rotated = extract(rotatedBig) # using numpy could make it faster ?
    """print("rotated start")
    printPic(rotated)
    print("rotated stop")"""
    #printPic(rotated)
    #exit(0)
    #print("rotated: " + toString(rotated))
    res = redim(rotated, sX, sY)
    """print("res start")
    printPic(res)
    print("res stop")"""
    #print("res: " + toString(res))
    return res # used to be rot[0/1]

buildings = {}

buildingsFolder = WSLPath("C:\\Users\\Benjamin\\Desktop\\map\\buildings\\blackOrWhiteWellSized\\")
buildingsSizedFolder = WSLPath(buildingsFolder + "sized\\")
buildingsAverageX, buildingsAverageY = 0, 0
for r, d, files in os.walk(buildingsSizedFolder):
    filesLen = len(files)
    for filesIndex in range(filesLen):
        file = files[filesIndex]
        strucId = file.split('.')[0]
        #print(strucId)
        im = Image.open(buildingsSizedFolder + file)
        imX, imY = im.size
        pixels = list(im.getdata())
        pixels = [pixels[i * imX:(i + 1) * imX] for i in range(imY)]
        #print(pixels)
        #printPic(pixels)
        buildingsAverageX += imX
        buildingsAverageY += imY
        for y in range(imY):
            for x in range(imX):
                pixels[y][x] = CST_F if pixels[y][x] else CST_T
        #pixels = rotatePic(pixels, 0)
        savePic(pixels, WSLPath(buildingsFolder + "OSM\\" + strucId + ".txt"))
        strucIdInt = int(strucId)
        #print(strucIdInt)
        buildings[strucIdInt] = getPicStr(pixels).split('\n')
        #break
    buildingsAverageX /= filesLen
    buildingsAverageY /= filesLen
#print(buildingsAverageX, buildingsAverageY) # 86.95 83.42, product = 7253.36

def similarity(pic0, pic1): # makes it return a value between 0 and 100
    #print("a")
    sim0, bestAngle = 0, 0
    """print("pic0 start")
    printPic(pic0)
    print("pic0 stop")
    print("pic1 start")
    printPic(pic1)
    print("pic1 stop")
    exit(0)"""
    for angle in range(0, 360): # used to be 1 instead of 0, why ??
        pic0Tmp = rotatePic(pic0, angle) # TODO: could optimize by rotating the smallest in average (need to compute average size for buildings and polygons on map)
        """print("pic0Tmp start")
        printPic(pic0Tmp)
        print("pic0Tmp stop")"""
        sim0Tmp = similarityOneToOther(pic0Tmp, pic1)
        #print("sim: " + str(angle) + " " + str(sim0Tmp))
        """if sim0Tmp > 0:
            exit(0)"""
        #break
        #print(angle, sim0Tmp, bestAngle, sim0) # coudl avoid 360 0
        if sim0Tmp > sim0:
            sim0 = sim0Tmp
            bestAngle = angle
    #print("b")
    #if sim0 > 0:
    #    exit(0)
    sim1 = 100#similarityOneToOther(pic1, pic0) # why isn't it used anymore ? - should give a shot again
    return min(sim0, sim1), bestAngle # warning angle might be wrong if use one or another similarity point of view

#def addStructure(strucId, x, y, angle): # already coded (see write function)

def barycenter(X):
    return sum(X) / len(X)

#addStructureMax = 1000
tooBigNb, buildingsTreated, buildingsNb, underWaterNb = 0, 0, 0, 0

for linesIndex in range(linesLen):
    line = lines[linesIndex]
    if 'k="building" v="yes"' in line:
        buildingsNb += 1

#mutex = threading.Lock()
threads = []
threaded = False
strucs, sims, angles = [], [], []

def workOnInstance(xDelta, yDelta, xD, yD, X, Y, threadId):
    #print("Gonna work: " + str(threadId))
    pic = tab(xDelta, yDelta)
    #print(yDelta, xDelta)
    for yT in range(yDelta):
        for xT in range(xDelta):
            x = xMin + (xT / xDelta) * xD
            y = yMin + (yT / xDelta) * yD
            #print(x, y, X, Y)
            if isIn(x, y, X, Y):
                pic[yT][xT] = CST_T
    bestSim, bestSimStrucId, bestAngle = 0, 0, 0
    buildingsId = 0
    for strucId in buildings:
        #print(threadId, buildingsId)
        #print("a0:", getTime())
        building = buildings[strucId]
        sim, angle = similarity(building, pic) # dichotomy doesn't seem exact
        #print(bestSim, bestSimStrucId, bestAngle, sim, strucId, angle)
        if sim > bestSim:
            bestSim = sim
            bestSimStrucId = strucId
            bestAngle = angle
        buildingsId += 1
        #print("a1:", getTime())
    if threaded:
        """mutex.acquire()
        try:
            strucs += [bestSimStrucId]
            sims += [bestSim]
            angles += [angle]
            #print("h4")
            #addStructure(bestSimStrucId, x, y, angle)
            write(bestSimStrucId, x, y, bestAngle)
            #print(bestSimStrucId, bestSim, angle)
        finally:
            mutex.release()"""
    else:
        strucs += [bestSimStrucId]
        sims += [bestSim]
        angles += [angle]
        write(bestSimStrucId, x, y, bestAngle)
        #print(bestSimStrucId, bestSim, angle)

threadId = 0
justMeasureOSMAverage = False
justWriteNodesIdsAndPolygonFiles = False
preComputedFact = FACTOR * MAX_SIZE
preComputedFactX = preComputedFact / GTX
preComputedFactY = preComputedFact / GTY

dontCheckAltitude = False
ABORT_UNDER_WATER = "ABORT: UNDER WATER"
# in order not to check altitude for measuring average
notToTreat = [] # is smaller than "toTreat" ^^ (here at least)
ff = open(WSLPath("C:\\Users\\Benjamin\\Desktop\\map\\buildings\\treats.txt"))
ffLines = ff.readlines()
ff.close()
ffLinesLen = len(ffLines)
for ffLinesIndex in range(ffLinesLen - 1):
    ffLine, ffLineNext = ffLines[ffLinesIndex][:-1], ffLines[ffLinesIndex + 1][:-1]
    if ffLineNext == ABORT_UNDER_WATER:
        notToTreat += [int(ffLine)]

linesBeginIndex = 0 # 295717 # 537558 # 483937 # 0

##

if True:
    OSMAverageX, OSMAverageY = 0, 0
    countedForOSM = 0
    if justWriteNodesIdsAndPolygonFiles:
        ffT = open("nodesIds.txt", 'w')
    for linesIndex in range(linesBeginIndex, linesLen):
        #if linesIndex < 318276:
        #    continue
        #if linesIndex > linesBeginIndex:
        #    break
        line = lines[linesIndex]
        if 'k="building" v="yes"' in line:#and linesIndex == 532034:
            print(linesIndex, linesLen, "DOING")
            buildingsTreated += 1
            nodes = getNodesFromLine(linesIndex)
            if justWriteNodesIdsAndPolygonFiles:
                ffT.write(" ".join(nodes) + '\n')
                continue
            lonLat = [getLonLat(node) for node in nodes]
            coo = [getCoordinates(lon, lat) for lon, lat in lonLat]
            xMin, xMax, yMin, yMax = coo[0][0], coo[0][0], coo[0][1], coo[0][1]
            nodesLen = len(nodes)
            for nodesIndex in range(nodesLen):
                #node = nodes[nodesIndex]
                x, y = coo[nodesIndex][0], coo[nodesIndex][1]
                if x < xMin:
                    xMin = x
                if x > xMax:
                    xMax = x
                if y < yMin:
                    yMin = y
                if y > yMax:
                    yMax = y
            #print("h1")
            # let say no size limit for OSM pictures
            #print(xMin, xMax, yMin, yMax)
            xD, yD = xMax - xMin, yMax - yMin
            xDelta = int(xD * preComputedFactX)
            yDelta = int(yD * preComputedFactY)
            #print(xDelta, yDelta)
            # don't use binary file but text file with two characters
            #pic, l = [], []
            #for x in range(xDelta):
            #    l += [0]
            #l = [0 for x in range(xDelta)]
            #print("h2")
            #pic[0][0] = 42
            #print(pic)
            #breakT = False
            if yDelta * xDelta >= 50000000:
                print("ABORT: TOO BIG")
                tooBigNb += 1
                continue
            z = None
            if dontCheckAltitude:
                if linesIndex in notToTreat:
                    print(ABORT_UNDER_WATER, "alpha")
                    underWaterNb += 1
                    continue
            else:
                if linesIndex in notToTreat:
                    print(ABORT_UNDER_WATER, "beta")
                    underWaterNb += 1
                    continue
                X, Y = getPolygon(linesIndex)
                x, y = barycenter(X), barycenter(Y) ## THIS MIGHT BE NOT THE RIGHT LOCATION !
                #print(x, y, X, Y)
                z = getGroundAltitude(x, y)
                if z <= 0: # might not be correct for some basements ?
                    print(ABORT_UNDER_WATER, "charlie")
                    underWaterNb += 1
                    continue
            if justMeasureOSMAverage:
                OSMAverageX += xDelta
                OSMAverageY += yDelta
                countedForOSM += 1
                continue
            if not threaded:
                pic = tab(xDelta, yDelta)
                #print(yDelta, xDelta)
                for yT in range(yDelta):
                    for xT in range(xDelta):
                        xAI = xMin + (xT / xDelta) * xD
                        yAI = yMin + (yT / yDelta) * yD # used to be xDelta lol
                        #print(x, y, X, Y)
                        if isIn(xAI, yAI, X, Y): #x, y seems to overwrite on barycenter position otherwise
                            pic[yT][xT] = CST_T
                    #breakT = True
                    #break

                #if breakT:
                #    break
                #print("X: " + str(X))
                #print("Y: " + str(Y))
            #print("h3")
            """x = xMin + xD / 2
            y = yMin + yD / 2
            #print(isIn(x, y, X, Y))
            if isIn(x, y, X, Y):
                print("yes")
                pic[y][x] = 1
            XT = X[:] + [x]
            YT = Y[:] + [y]
            plt.plot(XT, YT)
            plt.show()"""
            #printPic(pic)
            #break
            # TODO: this approach one thread by one instance might be too expensive, should instead do %CPU cores% threads and give them food, modèle "producteur consommateur" (merci l'ENS ^^)
            # TODO: could also make this algo run on the server while my computer also work on it
            if threaded:
                print("thread launched !")
                """th = threading.Thread(target=workOnInstance, args=(pic,)) # might need to wait all threads at the end, see: realpython.com/intro-to-python-threading/
                threads.append(th)
                th.start()"""
                _thread.start_new_thread(workOnInstance, (xDelta, yDelta, xD, yD, X, Y, threadId,)) # pic[:] ? # "Thread-" + str(threadId)
                threadId += 1
            else:
                #print("no thread :(")
                #workOnInstance(pic) # ahgaga je suis python je ne connais pas strucs dans workOnInstance - stupide serpent !
                """print("PICTURE START")
                printPic(pic)
                print("PICTURE STOP")"""
                bestSim, bestSimStrucId, bestAngle = 0, 0, 0
                for strucId in buildings:
                    building = buildings[strucId]
                    """print("BUILDING START")
                    printPic(building)
                    print("BUILDING STOP")"""
                    """print("PICTURE START")
                    printPic(pic)
                    print("PICTURE STOP")"""
                    #exit(0)
                    sim, angle = similarity(building, pic)
                    #print(strucId, sim, angle)
                    #exit(0)
                    #if strucId == 640:
                    #    exit(0)
                    if sim > bestSim:
                        bestSim = sim
                        bestSimStrucId = strucId
                        bestAngle = (angle + 90) % 360 # see firstFull map at 39.8766,25.2667 and on OSM
                strucs += [bestSimStrucId]
                sims += [bestSim]
                angles += [angle]
                t = datetime.datetime.now().strftime("%H:%M:%S")
                print(t, bestSimStrucId, round(x, 2), round(y, 2), bestAngle, round(z, 2))
                #if bestSimStrucId == 640:
                #    exit(0)
                #if bestSimStrucId == 0:
                #    exit(0)
                if bestSimStrucId != 0:
                    write(bestSimStrucId, x, y, bestAngle, z)
                #exit(0)

            #print(linesIndex, linesLen, "DONE")

    """for index, thread in enumerate(threads):
        print("Thread " + str(index) + " joined !")
        thread.join()"""
    if justWriteNodesIdsAndPolygonFiles:
        ffT.close()
    print("FINISHED ALL", tooBigNb, buildingsTreated)
    if justMeasureOSMAverage:
        OSMAverageX /= countedForOSM # used to be filesLen
        OSMAverageY /= countedForOSM

if justMeasureOSMAverage:
    print(OSMAverageX, OSMAverageY) # 84.44 78.15, product = 6598.99 < 7253.37 so shouldn't rotate building but OSM but that's not a hude difference so let's dont care for the moment
# 2 327 under water and 4 too big and 9 174 buildingsTreated
