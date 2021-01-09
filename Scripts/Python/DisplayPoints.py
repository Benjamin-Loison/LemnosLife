# instead of online Geogebra lol

import matplotlib.pyplot as plt

l = [(128, 128), (179, 128), (169, 97), (169, 97), (128, 128), (169, 97), (143, 79), (143, 79), (128, 128), (143, 79), (113, 79), (113, 79), (128, 128), (113, 79), (87, 97), (87, 97)] # also work with parenthesis ?

##

X, Y = [], []

for point in l: # or could use numpy notations
    X += [point[0]]
    Y += [point[1]]


for point in l:
    plt.scatter(X, Y)

plt.show()

##

objFile = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\ConverterMap\\Python\\Structures\\ModelATV.obj"

f = open(objFile)
lines = f.readlines()
f.close()

v, f, vr, vrs = [], [], [], []

linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex][:-1].replace(" #1", "")
    id = line[:2]
    data = line[2:]
    if data != '' and data[-1] == ' ':
        data = data[:-1]
    dataCell = [data]
    dataParts = data.split()
    dataPartsLen = len(dataParts)
    if id == "v ":
        vs = []
        for dataPartsIndex in range(dataPartsLen):
            dataPart = dataParts[dataPartsIndex]
            vs += [float(dataPart)]
            #print(dataPart)
        #print(vs)
        v += [vs]#dataCell
    if id == "f ":
        f += dataCell
        vr = []
        for dataPartsIndex in range(dataPartsLen):
            dataPart = dataParts[dataPartsIndex]
            dataPartParts = dataPart.split('/')
            vi = int(dataPartParts[0])
            vr += [v[vi - 1]]
        vrs += [vr]

##

l = []

vrs0Len = len(vrs[0])
for ptIndex in range(vrs0Len): # vrs0Len
    pt = vrs[0][ptIndex]
    l += [[pt[0], pt[1]]]