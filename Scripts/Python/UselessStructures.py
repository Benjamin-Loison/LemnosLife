import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\"

def startsOnceWithNot(lines, start):
    startLen = len(start)
    for line in lines:
        if line[:startLen] != start:
            #print(line[:startLen])
            return True
    return False

for r, d, files in os.walk(path):
    for fileName in files:
        file = path + fileName
        #print(file)
        f = open(file)
        lines = f.readlines()
        f.close()
        if len(lines) == 0:
            print("0: " + fileName)
            continue
        if lines[0] == "\n":
            print("1: " + fileName)
            continue
        if not startsOnceWithNot(lines, "/"):
            print("2: " + fileName)
            continue