import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\"

os.chdir(path)

"""

Output (example):

structuresShadow.txt

234 -1;-1|-1;1|1;1|1;-1 -2;-1|-2;1|-1;1|-1;-1

No let's use a single quadrilateral as per structure output for the moment (this output is like "Get Volume and size structure.py" but add a bit more informations)

234 minX;minY maxX;minY maxX;maxY maxX;minY - nop
234 minX maxX minY maxY and do the stuff as above in C++

"""

INFINITY = 10 ** 6
structures = []

for r, d, files in os.walk(path):
    filesLen = len(files)
    for filesIndex in range(filesLen):
        file = files[filesIndex]
        #print(file)

        minX, minY, maxX, maxY = INFINITY, INFINITY, -INFINITY, -INFINITY

        f = open(file)
        lines = f.readlines()
        f.close()

        linesLen = len(lines)
        for linesIndex in range(linesLen):
            line = lines[linesIndex]
            if line[0] == '/':
                continue
            lineParts = line.split()
            linePartsLen = len(lineParts)
            if linePartsLen >= 10: # id type tex tex tex tex coo coo coo coo
                for linePartsIndex in range(6, 10): # indexes 6 to 9 describe coordinates
                    linePart = lineParts[linePartsIndex]
                    linePartParts = linePart.split(';')
                    linePartPartsLen = len(linePartParts)
                    if linePartPartsLen >= 3:
                        x, y = float(linePartParts[0]), float(linePartParts[1])
                        if x > maxX:
                            maxX = x
                        if x < minX:
                            minX = x
                        if y > maxY:
                            maxY = y
                        if y < minY:
                            minY = y
        structures += [[int(file.split('.')[0]), minX, maxX, minY, maxY]]

f = open("../structuresShadow.txt", 'w')

structuresLen = len(structures)
for structuresIndex in range(structuresLen):
    structure = [str(round(f, 2)).replace(".0", "") for f in structures[structuresIndex]]
    f.write(" ".join(structure))
    if structuresIndex < structuresLen - 1:
        f.write('\n')

f.close()