import os, filecmp

path = "C:\\Users\\Benjamin\\Desktop\\"

os.chdir(path)

oldPath = "C:\\Users\\Benjamin\\AppData\\Roaming\\TerraCraft\\Games\\LemnosLife\\Game\\"

newPath = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\Official\\"

# need to precise folders ?

res = ""

for r, d, files in os.walk(newPath):
    oldPathDir = r.replace(newPath, oldPath)
    #print("r", )
    for file in files:
        newPathFile = r + "\\" + file
        relativePathFile = newPathFile.replace(newPath, "")
        if relativePathFile[0] == '\\':
            relativePathFile = relativePathFile[1:]
        oldPathFile = oldPathDir + "\\" + file
        #print(oldPathFile)
        if os.path.isfile(oldPathFile):
            if not filecmp.cmp(newPathFile, oldPathFile):
                print(relativePathFile)
                res += relativePathFile + "&"
        else:
            res += relativePathFile + "&"

res = res[:-1].replace("\\", "/")

f = open(path + "outcome.txt", "w")
f.write(res)
f.close()

print(res)