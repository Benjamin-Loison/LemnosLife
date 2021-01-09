pathCommon = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\structuresShadow.txt"

f = open(pathCommon)
lines = f.readlines()
f.close()

linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex][:-1]
    #print(line)
    lineParts = line.split()
    linePartsLen = len(lineParts)
    if (lineParts[1] == lineParts[2]) or (lineParts[3] == lineParts[4]):
        print(lineParts[0])