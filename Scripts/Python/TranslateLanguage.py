from googletrans import Translator
import os

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\Language\\Languages\\"

os.chdir(path)

translator = Translator()

def lg(key):
    return translator.translate(key, dest='de', src="fr").text

f = open("FR_fr.lang")
lines = f.readlines()
f.close()

f = open("DE_de.lang", 'w')

linesLen = len(lines)

for linesIndex in range(linesLen):
    line = lines[linesIndex]
    newLine = line
    lineParts = line.split('=')
    linePartsLen = len(lineParts)
    if linePartsLen >= 2:
        translated = lg(lineParts[1])
        newLine = lineParts[0] + '=' + translated
    f.write(newLine)
    print(newLine)
    if linesIndex < linesLen - 1:
        f.write("\n")

# should translate even if <>
# what do with //comments ?
# how to deal with /commands ?
# should make if translated and lineParts[0] are the same, set as a comment
# how to deal is punktuation ? (not well managed with google translator) and ": " at the end ?
# one more return line after comments, why ?

f.close()