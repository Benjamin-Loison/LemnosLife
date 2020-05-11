import os

os.chdir("C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Altis\\Biomes\\")

newFileBytes = [255] * 9923 # 0 - 255

f = open("test.bin", "wb")

a = bytearray(newFileBytes)
b = bytes(newFileBytes)

print(newFileBytes, a, b)

f.write(b)

f.close()

# can save 3 Mo likewise