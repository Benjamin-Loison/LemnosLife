import os, filecmp

path = "C:\\Users\\Benjamin\\Desktop\\"

os.chdir(path)

oldPath = "C:\\Users\\Benjamin\\AppData\\Roaming\\TerraCraft\\Games\\LemnosLife\\Game\\"

newPath = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\Official\\"

# need to precise folders ?

res = ""

for r, d, files in os.walk(newPath):
    oldPathDir = r.replace(newPath, oldPath)
    #print("r", )
    #print("hey")
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
    if d == [] and files == []:
        relativeFolder = r.replace(newPath, "")
        folder = oldPathDir + "\\"
        #print("e: " + folder)
        if not os.path.isdir(folder):
            res += relativeFolder + "\\&"

if res[-1] == '&':
    res = res[:-1]
#res = res.replace("%", "%25")
#res = res.replace(" ", "%20")
#res = res.replace("`", "%60") #otherwise file well downloaded but with an incorrect name...

"""
%s peach field`Kavala.plg
%25s%20peach%20field%60Kavala.plg

% -> %25
 -> %20
` -> %60
"""

res = res.replace("\\", "/")

f = open(path + "outcome.txt", "w")
f.write(res)
f.close()

print(res)

# TODO: should make a python script to check which assets are really used

# opus dlls really necessary ?

