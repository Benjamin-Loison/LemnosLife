import os

path = "/home/lemnoslife/DEV/C++/Server/Compiled/Extensions/LemnosLife/Map/Altis/Farms/"
geoCoords = True

MIN_X, MAX_X = 0, 30720
MIN_LON, MAX_LON = 25.0089582633, 25.4827062382

MIN_Y, MAX_Y = 0, 30720
MIN_LAT, MAX_LAT = 39.7155070496, 40.0959350219

# don't need MAX_X/Y lol - ah si

def lon(x):
    return MIN_LON + ((x - MIN_X) / (MAX_X - MIN_X)) * (MAX_LON - MIN_LON)

def lat(y):
    return MIN_LAT + ((y - MIN_Y) / (MAX_Y - MIN_Y)) * (MAX_LAT - MIN_LAT)

for r, d, files in os.walk(path):
    #filesLen = len(files) # otherwise pb counting not plg files (like the py script)
    filesCount = 0
    for file in files:
        if file[-4:]== ".plg":
            filesCount += 1
            x, y = 0, 0
            f = open(file)
            lines = f.readlines()
            linesSize = len(lines)
            for linesIndex in range(1, linesSize):
                line = lines[linesIndex]
                lineParts = line.split() # can't trust size 2 (iron ore)
                linePartsSize = len(lineParts)
                if linePartsSize >= 2:
                    #print(line)
                    xTmp, yTmp = float(lineParts[0]), float(lineParts[1])
                    x += xTmp
                    y += yTmp
            f.close()
            x /= (linesSize - 1)
            y /= (linesSize - 1)
            rounding = 1
            if geoCoords:
                x = lon(x)
                y = lat(y)
                rounding = 4
			x = round(x, rounding)
            y = round(y, rounding)
            xStr = str(x)
            yStr = str(y)
            if not geoCoords:
                xStr = xStr.replace(".0", "")
                yStr = yStr.replace(".0", "")
            fileName = file[:-4]
            fileNameParts = fileName.split('`')
            fileNamePartsLen = len(fileNameParts)
            if fileNamePartsLen >= 2:
                fileName = fileNameParts[0].replace("%s", fileNameParts[1])
            print(fileName + " " + xStr + " " + yStr)