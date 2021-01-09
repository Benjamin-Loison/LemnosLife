# copied from ComputeMax3DDiagonalStructure.py

import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\"
os.chdir(path)

def distance(coordinates):
    coordinatesParts = coordinates.split(';')
    coordinatesPartsLen = len(coordinatesParts)
    if coordinatesPartsLen == 3: # cool to check but don't manage the other case u_u (could raise an exception)
        x, y, z = [float(coordinatesPart) for coordinatesPart in coordinatesParts]
        return (x ** 2 + y ** 2) ** 0.5

precision = 4
maxD = 0
maxDFile = ""

for r, d, files in os.walk(path):
    for file in files:
        #print("Working on: " + file)
        d = 0 # distance to 0, 0, 0 not any kind of barycenter

        f = open(file)
        lines = f.readlines()
        f.close()

        for line in lines:
            if line[0] == '/':
                continue
            lineParts = line.split()
            linePartsLen = len(lineParts)
            if linePartsLen >= 10:
                for linePartsIndex in range(6, 10):
                    linePart = lineParts[linePartsIndex]
                    d0 = distance(linePart)
                    if d0 > d:
                        d = d0


        d += 10 ** (-precision)
        d = round(d, precision)
        structure = file.replace(".struc", "")
        print(structure + " " + str(d))
        if d > maxD:
            maxD = d
            maxDFile = structure

print()
print("maxD: " + maxDFile + " " + str(maxD))