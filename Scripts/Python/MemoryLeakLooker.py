# memory graph live of LemnosLife
# with local derivative ?

import subprocess
import numpy as np
import matplotlib.pyplot as plt

def getRAMUsage(software):
    res = subprocess.check_output(["tasklist", "|", "findstr", software], shell=True)
    parts = res.split()
    parts[-2] = float(parts[-2].decode("utf-8").replace(',', '.'))
    sizeType = parts[-1].decode("utf-8")
    if sizeType == 'K':
        parts[-2] *= 1000
    elif sizeType == 'M':
        parts[-2] *= 1000000
    return parts[-2]

#print(getRAMUsage("LemnosLife"))

i = 0

while True:
    y = getRAMUsage("LemnosLife")
    plt.scatter(i, y)
    plt.pause(0.05)
    i += 1

plt.show()

##
