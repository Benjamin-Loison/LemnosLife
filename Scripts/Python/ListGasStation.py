# 28/07/20 Ben
# this code outcome can be used on server side for security checks
import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Altis\\Objects\\"

os.chdir(path)

toWrite = ""
CHUNK_SIZE = 1000
SUB_CHUNK_SIZE = 100

def toCoo(xRelativeStr, chk, subChk):
    return str(round(float(xRelativeStr) + chk * CHUNK_SIZE + subChk * SUB_CHUNK_SIZE, 2)) # otherwise Python precision cal

for r, d, files in os.walk(path):
    for file in files:
        if file[-8:] == ".objects":
            chk = file[:-8]
            chkParts = chk.split(" ")
            chkX, chkY = int(chkParts[0]), int(chkParts[1])
            f = open(file)
            #subChkX, subChkY = 0, 0 # really need (for "compiler") to fake initialize if assume initialized in lines below ?
            for line in f.readlines():
                lineParts = line.split(" ")
                linePartsSize = len(lineParts)
                if linePartsSize == 2:
                    subChkX, subChkY = int(lineParts[0]), int(lineParts[1])
                elif lineParts[0] == "448": # GAS STATION FEED ID
                    toWrite += toCoo(lineParts[1], chkX, subChkX) + " " + toCoo(lineParts[2], chkY, subChkY) + " " + lineParts[3] + "\n"
            f.close()

toWrite = toWrite [:-1]
print(toWrite) # could make a file saver