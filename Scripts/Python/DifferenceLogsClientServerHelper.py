import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\Logger\\Logs\\"

os.chdir(path)

f = open("client.txt")
lines = f.readlines()
f.close()

f = open("clientClean.txt", 'w')
linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    f.write(line.split("rot: ")[1])
    #if linesIndex < linesLen - 1:
    #    f.write("\n")
f.close()

# same code for server

f = open("server.txt")
lines = f.readlines()
f.close()

f = open("serverClean.txt", 'w')
linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    f.write(line.split("rot: ")[1])
    #if linesIndex < linesLen - 1:
    #    f.write("\n")
f.close()