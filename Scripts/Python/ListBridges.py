# 27/08/20 Ben
# copied from ListGasStation.py
# this algorithm is used to patch broken roads graph where there are bridges
# no need currently to list all bridges IDs in a file because there is so few
import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Altis\\Objects\\"

os.chdir(path)

toWrite = ""
CHUNK_SIZE = 1000
SUB_CHUNK_SIZE = 100

def toCoo(xRelativeStr, chk, subChk):
    res = str(round(float(xRelativeStr) + chk * CHUNK_SIZE + subChk * SUB_CHUNK_SIZE, 2))
    if res[-2:] == ".0":
        res = res[:-2]
    return res

for r, d, files in os.walk(path):
    for file in files:
        if file[-8:] == ".objects":
            chk = file[:-8]
            chkParts = chk.split(" ")
            chkX, chkY = int(chkParts[0]), int(chkParts[1])
            f = open(file)
            for line in f.readlines():
                lineParts = line.split(" ")
                linePartsSize = len(lineParts)
                id = lineParts[0]
                if linePartsSize == 2:
                    subChkX, subChkY = int(lineParts[0]), int(lineParts[1])
                elif id in ["182", "548", "673", "808"]:
                    toWrite += toCoo(lineParts[1], chkX, subChkX) + " " + toCoo(lineParts[2], chkY, subChkY) + '\n'
            f.close()

toWrite = toWrite [:-1]
print(toWrite)