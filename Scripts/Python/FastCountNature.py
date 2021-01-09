#path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\nature.txt"
path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\strucIdDbPathOccurences.txt"

f = open(path)
lines = f.readlines()
f.close()

types = []
nature = ["plants_f", "rocks_f"]

total = 0
natureCount = 0

for line in lines:
    line = line.replace("\n", "")
    if len(line) == 0 or line[0] == '#':
        continue
    lineParts = line.split()
    linePartsLen = len(lineParts)
    if linePartsLen >= 3:
        count = int(lineParts[1])
        model = lineParts[2]
        modelParts = model.split('\\') # used to be '/' lol
        modelPartsLen = len(modelParts)
        #print(line)
        if modelPartsLen > 1:
            type = modelParts[1]
            if type in nature:
                natureCount += count
            else:
                if not type in types:
                    types += [type]
                    print(type)
            total += count

print(natureCount, total, total - natureCount)

