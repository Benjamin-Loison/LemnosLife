import os
from shutil import copyfile

commonPath = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\"

pathTopPreviews = commonPath + "Assets\\Pictures\\Gui\\Gui\\Mapping\\TopPreviews\\"

commonFolder = commonPath + "Map\\Common\\"

# could also do it in "Mapping" folder
pathTopPreviewsNamed = commonFolder + "TopPreviewsNamed\\"
pathStrucIdDb = commonFolder + "strucIdDb.txt"

#os.chdir(path)

f = open(pathStrucIdDb)
lines = f.readlines()
f.close()

structureNames = []

for line in lines:
    structureNames += [line.split()[1]]

res = ""

if not os.path.isdir(pathTopPreviewsNamed):
    os.mkdir(pathTopPreviewsNamed)

os.chdir(pathTopPreviews)
for r, d, files in os.walk(pathTopPreviews):
    #print(files)
    for file in files:
        fileParts = file.split('.')
        structureIdStr = fileParts[0]
        structureId = int(structureIdStr)
        resTmp = structureIdStr + " " + structureNames[structureId]
        res += resTmp
        copyfile(file, pathTopPreviewsNamed + resTmp + '.' + fileParts[1])

# could also make a folder with just id name for file name picture
#f = open(commonFolder + "topPreview", 'w')