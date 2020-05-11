import os
from math import log, ceil

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Altis\\Biomes\\"

os.chdir(path)

BIOMES_FILE_EXTENSION = ".biomes"

f = open("15 15" + BIOMES_FILE_EXTENSION, "r")

lines = f.readlines()
#print(lines)

allLines = ''.join(lines)

##

def longest(string, char): # assume char is in string
    index, tmpIndex = 0, 0
    long, tmpLong = 0, 0
    for i in range(len(string)):
        c = string[i]
        if c == char:
            if tmpLong == 0:
                tmpIndex = i
            tmpLong += 1
        else:
            if tmpLong > long:
                long, index = tmpLong, tmpIndex
            tmpLong, tmpIndex = 0, 0
    if tmpLong > long: # if longest array is at the end
        long = tmpLong
        index = tmpIndex
    return long, index # seems to work fine

def longestAlphabet(string, alphabet):
    index, tmpIndex = 0, 0
    long, tmpLong = 0, 0
    for char in alphabet:
        tmpLong, tmpIndex = longest(string, char)
        if tmpLong > long:
            long, index = tmpLong, tmpIndex
    return long, index

txt = "abracadrbbbra"
allLines = "001010210210212021021200"

print(longest(txt, "b"))
print(longest(txt, "a"))
print(longest(txt, "r"))
print(longest(allLines, "0"))

def representation(n,b):
    c = []
    while n != 0:
        c.append(str(n % b))
        n = n // b
    return ''.join(reversed(c))

print(representation(8, 3))

def phabet():
    return ''.join(set(allLines))

def getBuffer():
    return buffer[i:j]

##

i = 0
j = n - Ls
allLines = "001010210210212021021200"

alphabet = phabet()
alpha = len(alphabet)
#print(alpha)

allLinesLength = len(allLines)
#print(allLinesLength)

n = 18#allLinesLength * 2
Ls = 9 # bruteforce to take the best one ?
buffer = ['0'] * (n - Ls)
Lc = ceil(log(n - Ls, alpha)) + ceil(log(Ls, alpha)) + 1

buffer += allLines[:Ls]
allLines = allLines[Ls:]
#print(buffer)
#print(allLines)

C = ""

for i in range(1):
    p1 = longestAlphabet(buffer[n - Ls:], alphabet)
    print(n - Ls + p1[1], p1[0])
    S1 = getBuffer()[n - Ls + p1[1]: n - Ls + p1[0] + 1] # narmol 0 and 1 for p1 ?
    L1 = len(S1)

    print(S1)

    #print(p1[0], L1)
    C11 = representation(n - Ls + p1[1] - 1, alpha)
    C12 = representation(L1 - 1, alpha)
    C2Len = 2 # computation TODO
    C12 = (C2Len - len(C12)) * '0' + C12
    C13 = S1[-1]

    C1 = C11 + C12 + C13

    print(C1)

    C += C1

#buffer = buffer[L1:]
#buffer += S1
i += L1
j += L1

bufferStr = ''.join(getBuffer())

print(bufferStr)

print("results")

print(C)
correct = "22021211022021202220"
print(correct)

##

# TODO: with binary

f.close()

"""for r, d, files in os.walk(path):
    for file in files:
        print(files)"""