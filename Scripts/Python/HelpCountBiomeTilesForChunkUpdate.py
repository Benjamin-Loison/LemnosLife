from os import chdir

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\Logger\\Logs\\"

chdir(path)

f = open("0.txt")
lines = f.readlines()
f.close()

nb = 0

for line in lines:
    nb += int(line.split()[-1])

print(nb)

# 2 250 000 (3)
# 750 000 (1)

# 1 500 000 (2)
# 2 250 000 (3)

# 750 000 (1)
# 2 250 000 (3)