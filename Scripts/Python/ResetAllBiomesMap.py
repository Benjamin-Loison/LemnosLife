import os

biomesFolder = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Lemnos\\Biomes\\"

SIZE = 51
content = ((SIZE * '2' + '\n') * SIZE)[:-1]

# doesn't really reset because destroy beach and bottom of sea biomes too...

for r, d, files in os.walk(biomesFolder):
    for file in files:
        #print(file)
        filePath = biomesFolder + file
        f = open(filePath, 'w')
        f.write(content)
        f.close()