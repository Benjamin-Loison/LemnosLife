import os

# could also do such a precise log within the C++ code
#logFileName = "08-11-20#17-35-39-444"
path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\Logger\\Logs\\"
stopAt = "Game launched (and connected to in game) in " #" a rejoint l'île."

def getTime(line): # let for the moment consider minutes, seconds and ms (not hours ^^ - say yes in order not to have troubles from an hour to the next one) - let no work across new day
    lineParts = line.split(']')[0].split('#')
    linePartsLen = len(lineParts)
    if linePartsLen < 2:
        return None
    lineParts = lineParts[1].split('-')
    # don't check length as new usual in order to warn dev if problem and not got more complex problem later on - well good job because need to for vector<string> printed in logs
    hours, minutes, seconds, ms = [int(linePart) for linePart in lineParts]
    secondsMs = 1000
    minutesMs = 60 * secondsMs
    hoursMs = 60 * minutesMs
    return hours * hoursMs + minutes * minutesMs + seconds * secondsMs + ms

def logP(fileName):
    logFileName = fileName.split('.')[0]
    times = []

    f = open(path + logFileName + ".log")
    lines = f.readlines()
    f.close()

    linesLen = len(lines)
    f = open(path + logFileName + ".logp", 'w')
    for linesIndex in range(linesLen - 1):
        line, nextLine = lines[linesIndex], lines[linesIndex + 1]
        #if stopAt in line:
        #    break
        f.write(line)
        if stopAt in nextLine:
            break
        currentMs, nextMs = getTime(line), getTime(nextLine)
        if currentMs != None and nextMs != None:
            if nextMs > currentMs + 1: # likewise say ok if go from a ms to the other
                deltaMs = nextMs - currentMs
                if not deltaMs in times:
                    times += [deltaMs]
                f.write(str(deltaMs) + " ms\n")
    f.write(nextLine[:-1])
    times = sorted(times, reverse = True)
    print(logFileName, times)
    f.close()

for r, d, files in os.walk(path):
    filesLen = len(files)
    for filesIndex in range(filesLen):
        file = files[filesIndex]
        if file[-4:] == ".log":
            logP(file)