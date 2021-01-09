import os
from PIL import Image

path = "C:\\Users\\Benjamin\\Desktop\\map\\buildings\\blackOrWhiteWellSized\\"

os.chdir(path)

shadowFilePath = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\structuresShadow.txt"

f = open(shadowFilePath)
lines = f.readlines()
f.close()
linesLen = len(lines)

structuresShadows = {}

MAX_SIZE = 256
GTX, GTY = 4600, 4770
FACTOR = 100

def f(x, y):
    x *= FACTOR
    y *= FACTOR

    x *= MAX_SIZE / GTX
    y *= MAX_SIZE / GTY

    return int(x), int(y)

for linesIndex in range(linesLen):
    line = lines[linesIndex][:-1]
    lineParts = line.split()
    structureId = int(lineParts[0])
    coo = [float(el) for el in lineParts[1:]]
    structuresShadows[structureId] = f(coo[3] - coo[2], coo[1] - coo[0])

gtX, gtY = 0, 0
for structureId in structuresShadows:
    if os.path.exists(str(structureId) + ".png"):
        x, y = structuresShadows[structureId]
        if x > gtX:
            gtX = x
        if y > gtY:
            gtY = y

for r, d, files in os.walk(path):
    filesLen = len(files)
    for filesIndex in range(filesLen):
        file = files[filesIndex]
        structureIdStr = file.split('.')[0]
        structureId = int(structureIdStr)
        size = structuresShadows[structureId]
        print(file, size)
        im = Image.open(file)
        im = im.resize(size, Image.ANTIALIAS) # thumbnail
        im.save("sized/" + file, "PNG")