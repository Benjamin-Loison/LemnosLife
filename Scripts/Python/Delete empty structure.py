import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\"

os.chdir(path)

for r, d, files in os.walk(path):
    for file in files:
        filePath = r + file
        f = open(filePath, "r")
        lines = f.readlines()
        f.close()
        if len(lines) == 2 and lines[0] == "cargo.jpg\n" and lines[1] == "0 QUAD 1;0 1;1 0;1 0;0 -0.5;0;0 -0.5;0;1 0.5;0;1 0.5;0;0":
            os.remove(filePath)
            print("deleted:", file)