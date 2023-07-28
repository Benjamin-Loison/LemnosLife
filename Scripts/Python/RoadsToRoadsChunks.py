# I lost (where is it ?) old py script/java program to do this, so here it is again

import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Lemnos\\Roads\\"

os.chdir(path)

chunks = {}
f = open("roads.txt")
lines = f.readlines()
f.close()

CHUNK_SIZE = 1000

linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    lineParts = line.split('@')[0].split()
    linePartsLen = len(lineParts)
    roadId = str(linesIndex)
    for linePartsIndex in range(linePartsLen):
        linePart = lineParts[linePartsIndex]
        linePartParts = linePart.split(',')
        x, y = [float(w) for w in linePartParts]
        chkX, chkY = [int(w // CHUNK_SIZE) for w in (x, y)]
        #print(chkX, chkY)
        chunk = str(chkX) + " " + str(chkY) # y, x or the reverse ? - should be in the first order (x, y)
        if chunk in chunks:
            if not (roadId in chunks[chunk]):
                chunks[chunk] += [roadId]
        else:
            chunks[chunk] = [roadId]

f = open("roadsChunks.txt", 'w')

chunksLen = len(chunks)
chunkIndex = 0
for chunk in chunks:
    f.write(chunk + '\n')
    l = chunks[chunk]
    lLen = len(l)
    for lIndex in range(lLen):
        lEl = l[lIndex]
        f.write(lEl)
        if lIndex != lLen - 1:
            f.write('\n')
    chunkIndex += 1
    if chunkIndex != chunksLen:
        f.write('\n') # '\n' which language for having troubles ?

f.close()
