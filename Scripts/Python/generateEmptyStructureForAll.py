import os
from shutil import copyfile

path = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\"

os.chdir(path)

STRUCTURE_FILE_EXTENSION = ".struc"

for i in range(924):
    dst = str(i) + STRUCTURE_FILE_EXTENSION
    if not os.path.isfile(dst):
        copyfile(path + "450" + STRUCTURE_FILE_EXTENSION, dst)