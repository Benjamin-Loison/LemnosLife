import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Altis\\Roads\\"

os.chdir(path)

f = open("roads.txt")
lines = f.readlines()
f.close()

# aim: filling these data structures
# vector<Vector2D> points;
# map<Vector2D, vector<Vector2D>> neighbors;
# may also be: map<unsigned int, vector<unsigned int>> neighbors;
# could 1. change algo for "unsigned int" version or 2. "recognize" point index from their value (is there unicity ?)

# let's store numeric values and not string in order to make easier computation
points = []
#neighbors = {}

segments = []

# can compute intersections without bruteforce ? #n²

def getCoo(pointStr):
    pointStrParts = pointStr.split(',')
    return float(pointStrParts[0]), float(pointStrParts[1])

linesLen = len(lines)

for linesIndex in range(linesLen):
    line = lines[linesIndex]
    lineParts = line.split('@')
    linePartsLen = len(lineParts)
    if linePartsLen >= 2: # could assume this
        pointsStr = lineParts[0].split() # default " "
        # could do 1. jump 2 by 2 and scan with pattern: (previous, current, next) /!\ next and previous are the same from an iteration to the other
        # 2. scan two points by two points fill segments and then fill points and neighbors (with intersection don't forget)
        # let's do method 2.
        workingPoints = [getCoo(pointStr) for pointStr in pointsStr]
        pointsStrLen = len(pointsStr)
        for pointsIndex in range(pointsStrLen - 1):
            point = workingPoints[pointsIndex]
            nextPoint = workingPoints[pointsIndex + 1]
            segments += [[point, nextPoint, int(lineParts[1]), linesIndex]]
            points += [point]#, nextPoint] # removing this optimize for segment loop ? - let's remove it otherwise nextPoint and point are the same from an iteration to the other - well let's manage here finally
        points += [workingPoints[-1]]
        #for pointStr in pointsStr:
        #    x, y = getCoo(pointStr)
            # how to deal with two points road (ow, not a problem I believe there was some with only one ^^)

def addIfNotIn(element, l): # don't use global in order to be useful for various global variables
    if not element in l:
        l.append(element)
    return l

# https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect/19550879#19550879
def find_intersection(p0, p1, p2, p3):
    s10_x = p1[0] - p0[0]
    s10_y = p1[1] - p0[1]
    s32_x = p3[0] - p2[0]
    s32_y = p3[1] - p2[1]

    denom = s10_x * s32_y - s32_x * s10_y

    if denom == 0: return None # collinear

    denom_is_positive = denom > 0

    s02_x = p0[0] - p2[0]
    s02_y = p0[1] - p2[1]

    s_numer = s10_x * s02_y - s10_y * s02_x

    if (s_numer < 0) == denom_is_positive: return None # no collision

    t_numer = s32_x * s02_y - s32_y * s02_x

    if (t_numer < 0) == denom_is_positive: return None # no collision

    if (s_numer > denom) == denom_is_positive or (t_numer > denom) == denom_is_positive: return None # no collision

    # collision detected

    t = t_numer / denom

    intersection_point = [p0[0] + (t * s10_x), p0[1] + (t * s10_y)]

    return intersection_point

# C++ code with counterClockWise etc just returns a bool and not coordinates
# don't hesitate to use QGis to view road by road from Arma III map
# TODO: doesn't work that good because road width isn't taken into account - is an improvement but isn't enough worth because end of road has already a "blue" point so don't mess on this - finally GPSDijkstraPb picture in this folder shows a problem two highways with not that much points are collided, but not enough to get a "red" point (not like on the picture) the link between roads won't be made, maybe considering real bounds of roads (with area) can be a solution (bigger in width or length could give interesting results with accurate order of magnitude with roads size)
def collision(segment0, segment1):
    return find_intersection(segment0[0], segment0[1], segment1[0], segment1[1])

ROADS_SIZES = [8, 6, 6, 8, 5]

def collisionRectangle(rectangle0, rectangle1):
    for i in range(4):
        for j in range(4):
            segment0, segment1 = rectangle0[i], rectangle1[j]
            intersection = collision(segment0, segment1)
            if intersection != None:
                return intersection
    return None

import math

piDiv2 = math.pi / 2
cosPiDiv2 = math.cos(piDiv2)
sinPiDiv2 = math.sin(piDiv2)

def rotate(origin, point, angle):
    """
    Rotate a point counterclockwise by a given angle around a given origin.
    The angle should be given in radians.
    """
    ox, oy = origin
    px, py = point

    #qx = ox + math.cos(angle) * (px - ox) - math.sin(angle) * (py - oy)
    #qy = oy + math.sin(angle) * (px - ox) + math.cos(angle) * (py - oy)

    qx = ox - angle * (py - oy)
    qy = oy + angle * (px - ox)
    return qx, qy

def length(point):
    return (point[0] ** 2 + point[1] ** 2) ** 0.5

def ope(point0, point1, symbol):
    return [point0[0] + point1[0] * symbol, point0[1] + point1[1] * symbol]

def resize(point, origin, size):
    #point -= origin
    point = ope(point, origin, -1)

    alpha = size / length(point);
    point[0] *= alpha;
    point[1] *= alpha;

    #point += origin
    point = ope(point, origin, 1)
    return point

def rotateAndResize(point, origin, angle, size):
    point = rotate(point, origin, angle)
    point = resize(point, origin, size)
    return point

import matplotlib.pyplot as plt

def dispRectangle(rectangle):
    X, Y = [], []
    X += [rectangle[0][0][0]]
    Y += [rectangle[0][0][1]]
    for i in range(4):
        X += [rectangle[i][1][0]]
        Y += [rectangle[i][1][1]]
    plt.plot(X, Y)

def rectangle(segment):
    roadSize = ROADS_SIZES[segment[2]]
    segments = []
    topLeft = rotateAndResize(segment[1], segment[0], 1, roadSize)
    topRight = rotateAndResize(segment[0], segment[1], -1, roadSize)
    bottomLeft = rotateAndResize(segment[1], segment[0], -1, roadSize)
    bottomRight = rotateAndResize(segment[0], segment[1], 1, roadSize)
    segments += [[topLeft, topRight], [topRight, bottomRight], [bottomRight, bottomLeft], [bottomLeft, topLeft]]
    return segments

def collisionRoad(segment0, segment1):
    rectangle0, rectangle1 = rectangle(segment0), rectangle(segment1)
    #plt.interactive(True)
    #dispRectangle(rectangle0)
    #dispRectangle(rectangle1)
    #plt.show(block=False)
    #input("Press Enter to continue...")
    return collisionRectangle(rectangle0, rectangle1)

def distanceSquare(point0, point1):
    return (point1[0] - point0[0]) ** 2 + (point1[1] - point0[1]) ** 2

# add bridges
bridges = [] # vector<vector<pair<double, double>>>
f = open("bridges.txt")
lines = f.readlines()
f.close()

linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    lineParts = line.split()
    linePartsLen = len(lineParts)
    if linePartsLen >= 2:
        x, y = [float(lineParts[i]) for i in range(2)]
        #x, y = [float(linePart) for linePart in lineParts]
        bridges += [[x, y]]

# check unicity of points and segments:
# TODO: problem unicity
pointsUnicity = {}
for point in points:
    pointsUnicity[point] = 0
print(len(points), len(pointsUnicity))

segmentsUnicity = {} # unicity
for segment in segments:
    segmentsUnicity[str(segment)] = 0 # unhashable type: "list" love python lol
print(len(segments), len(segmentsUnicity))

def distance(point0, point1):
    x0, y0 = point0
    x1, y1 = point1
    return ((x0 - x1) ** 2 + (y0 - y1) ** 2) ** 0.5

def findNearest(x, y, l):
    lLen = len(l)
    point0 = [x, y]
    point1 = l[0]
    bestPoint = point1
    bestDistance = distance(point0, point1)
    for lIndex in range(1, lLen):
        #xL, yL = l[lIndex]
        point1 = l[lIndex]
        d = distance(point0, point1)
        if d < bestDistance:
            bestDistance = d
            bestPoint = point1
    return bestPoint

def find2Nearest(x, y):
    pts = points[:] # otherwise problem with pointer
    pointNearest = findNearest(x, y, pts)
    pts.remove(pointNearest) # used to be [x, y] lol
    pointLessNear = findNearest(x, y, pts)
    return pointNearest, pointLessNear

# could do all the bridges job in a single big for loop
bridgesLen = len(bridges) # is there two bridges one after the other (not next to)
print("before bridges", len(points), len(segments))
for bridgesIndex in range(bridgesLen):
    x, y = bridges[bridgesIndex]
    bridgePoint = [x, y]
    # find two nearest different points
    pointNearest, pointLessNear = find2Nearest(x, y)
    points += [bridgePoint]
    roadType = 0 # maybe important !
    segments += [[bridgePoint, pointNearest, roadType, 0], [bridgePoint, pointLessNear, roadType, 0]] # last argument could be reconsidered
print("after bridges", len(points), len(segments))

INFINITY = 10000000
pointsLenBefore = len(points)
intersectionCounter = 0
segmentsLen = len(segments)
for segments0Index in range(segmentsLen):
    print("Working on first segment: " + str(segments0Index) + " / " + str(segmentsLen))
    for segments1Index in range(segmentsLen):
        #if segments0Index != segments1Index and segments0Index != segments1Index - 1 and segments0Index != segments1Index + 1: # TODO: this condition is not the best one, should instead just not same road (may explain missing intersections)
        segment0, segment1 = segments[segments0Index], segments[segments1Index]
        if(segment0[3] == segment1[3]):
            continue
        d = distanceSquare(segment0[0], segment1[0])
        if d > 2560000: # 1 600² (800 max length)
            continue
        intersection = collisionRoad(segment0, segment1) # used to be collision, find_intersection
        if intersection != None: #[INFINITY, INFINITY]: # None is better than INFINITY lol
            print("intersection: " + str(intersectionCounter))
            intersectionCounter += 1
            points += [intersection] # assume no intersection on already treated points (otherwise don't break the algorithm, sure ?) otherwise use addIfNotIn function
            segments += [[intersection, segment0[0], 0, INFINITY], [intersection, segment0[1], 0, INFINITY], [intersection, segment1[0], 0, INFINITY], [intersection, segment1[1], 0, INFINITY]] # no intersection on intersection please god <3

# points: 41 972 -> 63 675 (delta = 21 703)
# segments: 20 986 -> 107 798
# ok maybe add 4 segments on each collisions but that should makes ‭21 748 intersections (quite good ‬order of magnitude)

# nop without left, right collision:
# points: 41 972 -> 63 675 (delta = ‭21 793‬)
# segments: 20 986 -> 28 930

# finally:
# points: 22 400 -> 24 386 (delta = 1 986)
# segments: 20 986 -> 28 930

# 2 354 new points

## plots points on a graph to check

# little test

point0 = [100, 100]
point1 = [1000, 1000]
segmentsBis = rectangle([point0, point1, 0])
X, Y = [], []
X += [segmentsBis[0][0][0]]
Y += [segmentsBis[0][0][1]]
for i in range(4):
    X += [segmentsBis[i][1][0]]
    Y += [segmentsBis[i][1][1]]

plt.plot(X, Y)
plt.show()
#while True:
#    print("test") # displayed and graph bugged

#

xRoads = [points[pointsIndex][0] for pointsIndex in range(pointsLenBefore)]
yRoads = [points[pointsIndex][1] for pointsIndex in range(pointsLenBefore)]

plt.scatter(xRoads, yRoads, color='blue')

pointsLenAfter = len(points)
xIntersection = [points[pointsIndex][0] for pointsIndex in range(pointsLenBefore, pointsLenAfter)]
yIntersection = [points[pointsIndex][1] for pointsIndex in range(pointsLenBefore, pointsLenAfter)]

plt.scatter(xIntersection, yIntersection, color='red')

# could display road segments

plt.show()

#def toKey(l):
#    return " ".join([str(el) for el in l])

def addIfNotIn(key, element, d): # sure good syntax ?
    #key = toKey(key) # can't have a "list" as a key, but it seems to already have some --' ?!
    #print(key, len(d))
    if key in d:
        d[key].append(element)
    else:
        d[key] = [element]
    return d

neighbors = {}

# do this after segments is well computed, then points and neighbors will be perfect
for segment in segments:
    point, nextPoint, roadType, roadIndex = segment
    #points = addIfNotIn(point, points) # sure useful could do it directly in intersection computation...
    #points = addIfNotIn(nextPoint, points)
    point = (point[0], point[1])
    nextPoint = (nextPoint[0], nextPoint[1])
    neighbors = addIfNotIn(point, nextPoint, neighbors)
    neighbors = addIfNotIn(nextPoint, point, neighbors)

## write - seems correct

def rd(x):
    return round(x, 2)

def string(s):
    s = str(s)
    if s[-2:] == ".0":
        s = s[:-2]
    return s

def toString(point, delimiter = ","): # Vector2D, used to have delimiter = " "
    return string(rd(point[0])) + delimiter + string(rd(point[1]))

# points

# TODO: use neighbors keys otherwise some points might not even be on the graph
pointsLen = len(points)

f = open("points.txt", 'w')

for pointsIndex in range(pointsLen):
    point = points[pointsIndex]
    f.write(toString(point))
    if pointsIndex != pointsLen - 1:
        f.write("\n") # still bug if use '\n' instead of "\n" ? or it is a C++ bug ?

f.close()

# neighbors

neighborsLen = len(neighbors) # identical to pointsLen no ?

f = open("neighbors.txt", 'w')

#for neighborsIndex in range(neighborsLen): # it is a dict Ben !
#    neighbor = neighbors[neighbors]

keyIndex = 0
for key in neighbors:
    neighborsStr = ""
    localNeighbors = neighbors[key]
    localNeighborsLen = len(localNeighbors)
    for localNeighborsIndex in range(localNeighborsLen):
        neighborsStr += toString(localNeighbors[localNeighborsIndex])
        if localNeighborsIndex != localNeighborsLen - 1:
            neighborsStr += " "
    f.write(toString(key) + " " + neighborsStr)
    if keyIndex != neighborsLen - 1:
        f.write("\n")
    keyIndex += 1

f.close()

## debugging again

pointsToDraw = []

for key in neighbors:
    localNeighbors = neighbors[key]
    pointsToDraw += [localNeighbors]
    #localNeighborsLen = len(localNeighbors)
    #for localNeighborsIndex in range(localNeighborsLen):
    #    localNeighbor = localNeighbors[localNeighborsIndex]
    #pointsToDraw = addIfNotIn(localNeighbor, pointsToDraw)

# numpy can optimize to just execute a single plot ? and should manage unicity to optimize cf: https://stackoverflow.com/questions/24329693/how-to-make-matplotlib-draw-discontinuous-line-segments/24332470#24332470
pointsToDrawLen = len(pointsToDraw)
for pointsToDrawIndex in range(pointsToDrawLen):
    print(str(pointsToDrawIndex) + " / " + str(pointsToDrawLen))
    localPoints = pointsToDraw[pointsToDrawIndex]
    localPointsLen = len(localPoints)
    X = [localPoints[localPointsIndex][0] for localPointsIndex in range(localPointsLen)]
    Y = [localPoints[localPointsIndex][1] for localPointsIndex in range(localPointsLen)]

    plt.plot(X, Y)

plt.show()

# are some points excluded from the main graph ?

## optimizing file

# instead of writing all: u, v and v, u just write once and do the other in C++ code

f = open("neighbors.txt")
lines = f.readlines()
f.close()

links = {}

linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    #toWrite = ""
    points = line.split()
    key = points[0]
    pointsLen = len(points)
    for pointsIndex in range(pointsLen):
        point = points[pointsIndex]
        if point in links:
            linked = links[point]
            if key in linked:
                continue
            if not key in links[point]: # because seems to have duplicated entries
                links[point] += [key]
        else:
            if key in links:
                if not point in links[key]:
                    links[key] += [point]
            else:
                links[key] = [point]
    #if toWrite != "":
    #    f.write(toWrite)


f = open("neighbors.txt", 'w') # used to be: Optimized

linksLen = len(links)
linksIndex = 0
for key in links:
    linked = links[key]
    linkedLen = len(linked)
    if linkedLen > 1:
        f.write(' '.join(linked))
        if linksIndex != linksLen - 1:
            f.write("\n") # why still having last empty line ?
    linksIndex += 1

f.close()

# could even optimize links list in order to minimize writing of lenghtest keys

# second optimization

f = open("neighbors.txt")
lines = f.readlines()
f.close()

# write multiple times same neighbor - problem seems solved if copy content of neighborsOptimized in neighbors before second optimization

pts, rev = {}, {}
ptsIndex = 0

linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    points = line.split()
    pointsLen = len(points)
    for pointsIndex in range(pointsLen):
        point = points[pointsIndex]
        if not point in pts:
            pts[ptsIndex] = point
            rev[point] = ptsIndex
            ptsIndex += 1

f = open("neighbors.txt", 'w') # TODO: seems to work but some indexes are weirdly skipped... MAYBE BRIDGES ALSO HAVE PROBLEMS - bridges done
# used to be: Optimized

ptsLen = len(pts)
f.write(str(ptsLen) + " ")
for ptsIndex in range(ptsLen):
    f.write(pts[ptsIndex])
    if ptsIndex != ptsLen - 1:
        f.write(" ")
f.write("\n")

def rep(line):
    for ptsIndex in range(ptsLen):
        line = line.replace(pts[ptsIndex], str(ptsIndex))
    return line

linesLen = len(lines)
for linesIndex in range(linesLen):
    print(linesIndex, linesLen)
    line = lines[linesIndex]
    f.write(rep(line)) # compared to this the following is obviously better ^^ # wow print was taking almost all time with this new version ^^
    continue # TODO: the following doesn't to work as the previous code...
    lineParts = line.split()
    linePartsLen = len(lineParts)
    for linePartsIndex in range(linePartsLen):
        linePart = lineParts[linePartsIndex]
        lineParts[linePartsIndex] = str(rev[linePart])
    f.write(' '.join(lineParts))
    if linesIndex != linesLen - 1: # not required for commented version
        f.write("\n")

f.close()

# could also make a relative index depending on key like:
# 6001 6002 becoming 6001 1
#  Kb ->  Kb
# could also make absolute relative:
# 0 1
# 1 2 3
# 3 4
# would become: (comparing to last written index) this is the best in comparaison with the previous technic
# 0 1
# 0 1 1
# 0 1

# default technic doesn't pay the bill because indexes are written with approximatively the same numbers of characters than coordinates themselves lol 800 Kb -> 1 100 Kb (let's take this in order to be as near as possible from the internet code for Dijksta)