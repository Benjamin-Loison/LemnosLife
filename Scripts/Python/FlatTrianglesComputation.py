import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Altis\\Ground\\"

os.chdir(path)

N = -100

def nb(x):
    if x == 'N':
        return N
    return float(x)

for r, d, files in os.walk(path):
    total, totalTotal = 0, 0
    for file in files:
        i = 0
        f = open(file)
        lines = f.readlines()
        linesLen = len(lines)
        matrix = [[nb(x) for x in line.split()] for line in lines]
        for y in range(1, linesLen):
            for x in range(1, linesLen):
                if matrix[y][x] != N and matrix[y][x] == matrix[y][x - 1] and matrix[y][x] == matrix[y - 1][x]: # manage one case on two, anyway it should show flat triangles
                    i += 1#print(matrix[y][x], matrix[y][x - 1], matrix[y - 1][x]) # last two arguments useless
        print(i, linesLen ** 2)
        total += i
        totalTotal += linesLen ** 2
        f.close()
    print(total, totalTotal)

# 500 000 flat triangles (prediction) for 29 millions of heights