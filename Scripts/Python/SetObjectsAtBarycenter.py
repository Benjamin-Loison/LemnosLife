import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\"

os.chdir(path)

def isATexture(s):
    return ".jpg" in s or ".png" in s or ".svg" in s

def strRd(x):
    res = str(round(x, 3))
    if res[-2:] == ".0":
        res = res[:-2]
    return res

for r, d, files in os.walk(path):
    filesLen = len(files)
    for filesIndex in range(filesLen):
        file = files[filesIndex]
        #print(file)

        f = open(file)
        lines = f.readlines()
        f.close()
        linesLen = len(lines)

        #barycenterX, barycenterY = 0, 0
        #barycenterLen = 0
        minX, minY, maxX, maxY = None, None, None, None

        for linesIndex in range(linesLen):
            line = lines[linesIndex]
            if line[0] == '/':
                continue
            #print("!" + line + "!")
            lineParts = line.split()
            linePartsLen = len(lineParts)
            if not isATexture(line):#linePartsLen > 1:
                for linePartsIndex in range(6, 10):
                    linePart = lineParts[linePartsIndex]
                    linePartParts = linePart.split(';')
                    linePartPartsFloat = [float(linePartPart) for linePartPart in linePartParts]
                    x, y = linePartPartsFloat[0], linePartPartsFloat[1]
                    #barycenterX += linePartPartsFloat[0]
                    if minX is None or x < minX:
                        minX = x
                    if minY is None or y < minY:
                        minY = y
                    if maxX is None or x > maxX:
                        maxX = x
                    if maxY is None or y > maxY:
                        maxY = y
                    #barycenterY += linePartPartsFloat[1]
                    #barycenterLen += 1
        """barycenterX /= barycenterLen
        barycenterY /= barycenterLen"""
        #print(file, barycenterX, barycenterY)
        #continue
        barycenterX = (minX + maxX) / 2
        barycenterY = (minY + maxY) / 2

        f = open(file, 'w')
        for linesIndex in range(linesLen):
            line = lines[linesIndex]
            if line[0] == '/':
                continue # stop using comments here...
            lineParts = line.split()
            linePartsLen = len(lineParts)
            if not isATexture(line):#linePartsLen > 1:
                for linePartsIndex in range(6, 10):
                    linePart = lineParts[linePartsIndex]
                    linePartParts = linePart.split(';')
                    linePartPartsFloat = [float(linePartPart) for linePartPart in linePartParts]
                    lineParts[linePartsIndex] = strRd(linePartPartsFloat[0] - barycenterX) + ";" + strRd(linePartPartsFloat[1] - barycenterY) + ";" + strRd(linePartPartsFloat[2])
                line = ' '.join(lineParts) #pre [:6]
                f.write(line)
                if linesIndex < linesLen - 1:
                    f.write('\n')
            else:
                f.write(line)
        f.close()
