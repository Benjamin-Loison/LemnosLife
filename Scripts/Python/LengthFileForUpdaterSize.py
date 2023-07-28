import os

path = "C:/Users/Benjamin/AppData/Roaming/TerraCraft/Games/LemnosLife/Game/"

res = ""

for r, d, files in os.walk(path):
    r = r.replace(path, "") + "\\"
    if files == []:
        res += r + '\n'
    else:
        for file in files:
            res += r + file + '\n'
    #print(r, d, files)


res = res.replace("\\", "/")
res = res[:-1]
f = open("out.txt", "w")
lines = res.split('\n')
for line in lines:
    f.write(line + '\n')
f.close()
print(res)
print(len(res))

