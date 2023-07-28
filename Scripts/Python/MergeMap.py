import os

# priority map in Extension folder (put in path1 the less heavy map)
# TODO: don't add those colliding - make less dataset have the priority !

path0 = "C:\\Users\\Benjamin\\Desktop\\map\\Kemist\\Map0\\"
path1 = "C:\\Users\\Benjamin\\Desktop\\map\\Kemist\\Map1\\"

for r, d, files in os.walk(path1):
    filesLen = len(files)
    for filesIndex in range(filesLen):
        file = files[filesIndex]
        f = open(path1 + file)
        lines = f.readlines()
        f.close()
        if os.path.exists(path0 + file):
            linesLen = len(lines)
            #chks = file.split('.')[0].split()
            #chkX, chkY = int(chks[0]), int(chks[1])
            #subChkX, subChkY = -1, -1
            header = ""
            for linesIndex in range(linesLen):
                line = lines[linesIndex]
                lineParts = line.split()
                linePartsLen = len(lineParts)
                if linePartsLen == 2:
                    header = line
                    #subChkX, subChkY = int(lineParts[0]), int(lineParts[1])
                else:
                    f = open(path0 + file)
                    fLines = f.readlines()
                    f.close()
                    toWrite = ""
                    fLinesLen = len(fLines)
                    found = False
                    for fLinesIndex in range(fLinesLen):
                        fLine = fLines[fLinesIndex]
                        toWrite += fLine
                        if fLine == header:
                            found = True
                            if line[-1] != '\n':
                                line += '\n'
                            toWrite += line
                    if not found:
                        if line[-1] == '\n':
                            line = line[:-1]
                        toWrite += '\n' + header + line
                    f = open(path0 + file, 'w')
                    f.write(toWrite)
                    f.close()
        else:
            f = open(path0 + file, 'w')
            f.write(''.join(lines))
            f.close()