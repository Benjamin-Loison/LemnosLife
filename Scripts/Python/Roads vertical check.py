import os

path0 = "C:\\Users\\Benjamin\\Desktop\\roads\\toLemnos\\"
path1 = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Lemnos\\Roads"

os.chdir(path1)

f = open("roads.txt", 'r')
lines = f.readlines()
f.close()

f = open("roads.txt", 'w')

## if multiple problems on the same road one after this other then should use "inc" ?

linesLen = len(lines)
i = 0
jGreatest = 0
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    lineHeaders = line.split('@')
    lineType = lineHeaders[1].replace('\n', "")
    lineParts = lineHeaders[0].split()
    inc = 0.01
    newLine = ""
    linePartsLen = len(lineParts)
    j = 0
    #pb = False
    for linePartsIndex in range(linePartsLen - 1):
        newPart = lineParts[linePartsIndex]
        firstCoordinates = newPart.split(',')
        secondCoordinates = lineParts[linePartsIndex + 1].split(',')
        if firstCoordinates[0] == secondCoordinates[0]:
            #pb = True
            print("fuck", linesIndex, linePartsIndex) # about 20~30 fuck (can be multiple fuck for the fucking same road)
            i += 1
            print(i)
            j += 1
            print(j)
            if j > jGreatest:
                jGreatest = j
            newPart = str(round(float(firstCoordinates[0]) + inc, 2)) + ',' + firstCoordinates[1]
            inc += 0.01 # best way to solve the problem ? seems to be useless - not for IRL Lemnos map let's don't bother with 6 cms offset
            if firstCoordinates[1] == secondCoordinates[1]:
                print("ultra fuck") # no ultra fuck
        newLine += newPart
        if linePartsIndex < linePartsLen - 1:
            newLine += " "
    newLine += lineParts[linePartsLen - 1]
    #if linePartsLen == 2:
     #   print(newLine)
    #if pb:
    #    print(lineParts)
    f.write(newLine + '@' + lineType) ## TODO: optimize with things like: .replace("0 ", "").replace(".0", "")
    if linesIndex < linesLen - 1:
        pass
        f.write('\n') # also work with '\n' ? not a good idea in general if I remember well

print(jGreatest)

f.close()