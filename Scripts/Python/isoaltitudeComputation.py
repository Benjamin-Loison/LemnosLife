import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Altis\\Ground\\"

os.chdir(path)

N = -100
MAX_ALTITUDE = 400
HEIGHT_INTERVAL = 10
GROUND_SIZE = 4

altitudesToTest = range(N + HEIGHT_INTERVAL, MAX_ALTITUDE + HEIGHT_INTERVAL, HEIGHT_INTERVAL)

def nb(x):
    if x == 'N':
        return N
    return float(x)

for r, d, files in os.walk(path):
    for file in files:
        w = open(file.replace(".height", ".isoalt"))
        f = open(file)
        lines = f.readlines()
        linesLen = len(lines)
        matrix = [[nb(x) for x in line.split()] for line in lines]
        # let first manage top left triangle in the figure given in a PDF associated to theory to the ground
        for y in range(linesLen - 1):
            for x in range(linesLen - 1):
                current, right, down = matrix[y][x], matrix[y][x + 1], matrix[y + 1][x]
                if current != right:
                    a = (right - current) / GROUND_SIZE
                    b = current
                    maxi = max(current, right)
                    mini = min(current, right)
                    for altitude
                    ### TODO: to finish
                    # y = ax + b <=> x = (y - b) / a
        f.close()
        w.close()