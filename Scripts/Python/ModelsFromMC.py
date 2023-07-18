from os import chdir
from math import cos, sin

path = "C:\\Users\\Benjamin\\Desktop"

chdir(path)

fileName = "Zodiac.java"
forceTextureName = "dayz_vehicle_chevroletsuburban2010_2"
modelName = ""
textureX, textureY = 0, 0
idStr = "24" # could make an auto-id found

PREFIX_MODEL_NAME = "public class "

ADD_BOX = "addBox"
SET_ROTATION_POINT = "setRotationPoint"
ADD_SHAPE_BOX = "addShapeBox"

THIS = ""

debugging = False

additionnalPath = "C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Common\\Structures\\"
directApply = True

MINECRAFT_BLOCK_SIZE = 16

# offset is first three arguments of addBox

PREFIX_DIM = ADD_BOX + "("
PREFIX_TEX = "new ModelRendererTurbo(this, "
PREFIX_NB = "new ModelRendererTurbo["
BODY_MODEL_REAL = "bodyModel"
BODY_MODEL = "bodyModel"
DOOR_OPEN_MODEL = "bodyDoorOpenModel"
DOOR_CLOSE_MODEL = "bodyDoorCloseModel"
LEFT_FRONT_WHEEL_MODEL = "leftFrontWheelModel"
RIGHT_FRONT_WHEEL_MODEL = "rightFrontWheelModel"
LEFT_BACK_WHEEL_MODEL = "leftBackWheelModel"
RIGHT_BACK_WHEEL_MODEL = "rightBackWheelModel"
FRONT_WHEEL_MODEL = "frontWheelModel"
BACK_WHEEL_MODEL = "backWheelModel"
LEFT_TRACK_WHEEL_MODEL = "leftTrackWheelModels" # what is it ? moteur ifrit ?
LEFT_TRACK_MODEL = "leftTrackModel"
RIGHT_TRACK_MODEL = "rightTrackModel"
TRAILER_MODEL = "trailerModel"
STEERING_WHEEL_MODEL = "steeringWheelModel"

ZERO_F = ", 0F);"
PREFIX_ROTATION_X = "rotateAngleX"
PREFIX_ROTATION_Y = "rotateAngleY"
PREFIX_ROTATION_Z = "rotateAngleZ"

isCompiled = False

if isCompiled:
    ADD_BOX = "func_78790_a"
    SET_ROTATION_POINT = "func_78793_a"
    THIS = "this."
    PREFIX_DIM = ADD_BOX + "("
    PREFIX_TEX = "new ModelRendererTurbo((ModelBase)this, "
    PREFIX_NB = "new ModelRendererTurbo["
    ZERO_F = ", 0.0F);"

    PREFIX_ROTATION_X = "field_78795_f"
    PREFIX_ROTATION_Y = "field_78796_g" # increment too albatard
    PREFIX_ROTATION_Z = "field_78808_h"

PREFIX_POS = SET_ROTATION_POINT + "("

def tex(str):
    return int(str.split("=")[1].replace(";", ""))

def getRot(PREFIX_ROTATION, line):
    return float(line.split(PREFIX_ROTATION + " = ")[1].replace("F;", ""))

def rotate(origin, point, angle):

    ox, oy = origin
    px, py = point

    qx = ox + cos(angle) * (px - ox) - sin(angle) * (py - oy)
    qy = oy + sin(angle) * (px - ox) + cos(angle) * (py - oy)

    return qx, qy

f = open(fileName)
lines = f.readlines()
f.close()

GLOBAL_OFFSET = 0

def workOn(BODY_MODEL, isLast):
    global GLOBAL_OFFSET
    # why required here ?

    bodyModels = [] # [texX, texY, dimX, dimY, dimZ, posX, posY, posZ, rotX, rotY, rotZ, offsetX, offsetY, offsetZ]
    BODY_MODELS_LEN = 0

    PREFIX_BODY_MODEL = BODY_MODEL + "["

    for line in lines:
        line = line.replace("\n", "")
        k = line.find("//")
        if k != -1:
            #print(line)
            line = line[:k]
            #print(line)
        if line.startswith(PREFIX_MODEL_NAME):
            modelName = line.replace(PREFIX_MODEL_NAME, "").replace("Model", "").split()[0]
        elif "textureX = " in line:
            textureX = tex(line)
        elif "textureY = " in line: # two cases because not same destination variable
            textureY = tex(line)
        elif BODY_MODEL in line:
            if PREFIX_NB in line:
                BODY_MODELS_LEN = int(line.split(PREFIX_NB)[1].replace("];", ""))
                bodyModels = [[0] * 14 for i in range(BODY_MODELS_LEN)] # used to be [0 for i in range(8)]
            else:
                index = int(line.split(PREFIX_BODY_MODEL)[1].split("]")[0])
                if PREFIX_TEX in line:
                    texs = line.split(PREFIX_TEX)[1].replace(", " + THIS + "textureX, " + THIS + "textureY);", "")
                    texs = texs.split(",")
                    for i in range(len(texs)):
                        currentTex = texs[i]
                        bodyModels[index][i] = int(currentTex)
                elif PREFIX_DIM in line:
                    #print(line)

                    #dims = ",".join(line.split(PREFIX_DIM)[1].split(",")[3:]).replace(ZERO_F, "")
                    dims = line.replace("F", "").split(PREFIX_DIM)[1].replace(ZERO_F, "")
                    dims = dims.split(",")

                    for i in range(3):
                        bodyModels[index][i + 2] = float(dims[3 + i])
                        bodyModels[index][i + 11] = float(dims[i]) ## WARNING CAN USE FLOAT AND NOT INT !

                        #print(bodyModels[index])
                elif PREFIX_POS in line:
                    #print(line)
                    poss = line.replace("F", "").split(PREFIX_POS)[1].replace(");", "")
                    poss = poss.split(",")
                    #print(poss)
                    for i in range(len(poss)):
                        bodyModels[index][i + 5] = int(float(poss[i]))
                elif PREFIX_ROTATION_X in line:
                    #print(line)
                    bodyModels[index][8] = getRot(PREFIX_ROTATION_X, line)
                elif PREFIX_ROTATION_Y in line:
                    bodyModels[index][9] = getRot(PREFIX_ROTATION_Y, line)
                elif PREFIX_ROTATION_Z in line:
                    bodyModels[index][10] = getRot(PREFIX_ROTATION_Z, line)
                elif ADD_SHAPE_BOX in line:
                    print("Go: " + line)

                else:
                    print("Not treating: " + line)

    # make another format which use triangles or quadrilaterals to remove all quadrilaterals in common...

    #print(modelName, textureX, textureY)

    #for bodyModel in bodyModels:
    #    print(" ".join(map(str, bodyModel)))

    def translate(partsStr, i):
        #return partsStr
        partsStr = partsStr.replace("--", "")
        #for j in range(5, 8):
        #    bodyModels[i][j] = 0
        #print(partsStr)
        parts = partsStr.split()
        partsLen = len(parts)
        if partsLen == 4:
            for partsIndex in range(partsLen):
                part = parts[partsIndex]
                partParts = part.split(";")
                x = float(partParts[0])
                y = -float(partParts[1])
                z = float(partParts[2])
                oX = bodyModels[i][5] / MINECRAFT_BLOCK_SIZE
                oY = bodyModels[i][6] / MINECRAFT_BLOCK_SIZE
                oZ = bodyModels[i][7] / MINECRAFT_BLOCK_SIZE
                ofX = bodyModels[i][11] / MINECRAFT_BLOCK_SIZE
                ofY = bodyModels[i][12] / MINECRAFT_BLOCK_SIZE
                ofZ = bodyModels[i][13] / MINECRAFT_BLOCK_SIZE
                x = x + oX
                y = y - oY
                z = - z + oZ
                y, z = rotate([-oY, oZ], [y, z], -bodyModels[i][8])
                x, z = rotate([oX, oZ], [x, z], bodyModels[i][9])
                x, y = rotate([oX, -oY], [x, y], bodyModels[i][10])
                x += ofX
                y -= ofY
                z += ofZ
                #print(parts[partsIndex])
                parts[partsIndex] = str(x) + ";" + str(z) + ";" + str(y)
                #print(parts[partsIndex])
                #print(bodyModels[i][5:])
                #print()
                #print()
                #print(parts[partsIndex])
            return " ".join(parts)
        else:
            print("def translate(str i): this should never happened")
            exit()

    def tX(i, x):
        res = (bodyModels[i][0] + x)
        if not debugging:
            res /= textureX
        return str(res)

    def tY(i, y):
        res = (bodyModels[i][1] + y)
        if not debugging:
            res /= textureY
            res = 1 - res
        return str(res) # how to know that we need to use 1 - ? lol 030520 00:32 AM best dancing

    def strFromMCPart(i):
        res = ""
        x, y, z = bodyModels[i][2], bodyModels[i][3], bodyModels[i][4]
        xS, yS, zS = str(x / MINECRAFT_BLOCK_SIZE), str(-y / MINECRAFT_BLOCK_SIZE), str(z / MINECRAFT_BLOCK_SIZE)
        minTX, maxTX, maxTY, minTY = bodyModels[i][4] + bodyModels[i][2] + bodyModels[i][4], bodyModels[i][4] + bodyModels[i][2] + bodyModels[i][2] + bodyModels[i][4], bodyModels[i][4], bodyModels[i][4] + bodyModels[i][3]
        minTX = tX(i, minTX)
        maxTX = tX(i, maxTX)
        minTY = tY(i, minTY)
        maxTY = tY(i, maxTY)
        res += str(6 * i + GLOBAL_OFFSET) + " QUAD " + maxTX + ";" + maxTY + " " + minTX + ";" + maxTY + " " + minTX + ";" + minTY + " " + maxTX + ";" + minTY + " " \
            + translate("0;0;-" + zS + " " \
            + xS + ";0;-" + zS + " " \
            + xS + ";-" + yS + ";-" + zS + " " \
            + "0;-" + yS + ";-" + zS, i) + "\n"
        maxTX, minTX, maxTY, minTY = bodyModels[i][4], bodyModels[i][4] + bodyModels[i][2], bodyModels[i][4], bodyModels[i][4] + bodyModels[i][3]
        minTX = tX(i, minTX)
        maxTX = tX(i, maxTX)
        minTY = tY(i, minTY)
        maxTY = tY(i, maxTY)
        res += str(6 * i + 1 + GLOBAL_OFFSET) + " QUAD " + maxTX + ";" + maxTY + " " + minTX + ";" + maxTY + " " + minTX + ";" + minTY + " " + maxTX + ";" + minTY + " " \
            + translate("0;0;0" + " " \
            + xS + ";0;0" + " " \
            + xS + ";-" + yS + ";0" + " " \
            + "0;-" + yS + ";0", i) + "\n" # HERE (below)
        # used to be: minTX, maxTX, minTY, maxTY # new: maxTX, minTX, maxTY, minTY
        maxTX, minTX, maxTY, minTY = bodyModels[i][4], bodyModels[i][4] + bodyModels[i][2], 0, bodyModels[i][4]
        #print(i, minTX, maxTX, minTY, maxTY)
        minTX = tX(i, minTX)
        maxTX = tX(i, maxTX)
        minTY = tY(i, minTY)
        maxTY = tY(i, maxTY)
        #print(i, minTX, maxTX, minTY, maxTY)
        #print()
        res += str(6 * i + 2 + GLOBAL_OFFSET) + " QUAD " + maxTX + ";" + maxTY + " " + minTX + ";" + maxTY + " " + minTX + ";" + minTY + " " + maxTX + ";" + minTY + " " \
            + translate("0;0;-" + zS + " " \
            + xS + ";0;-" + zS + " " \
            + xS + ";0;0" + " " \
            + "0;0;0", i) + "\n"
        minTX, maxTX, minTY, maxTY = bodyModels[i][4] + bodyModels[i][2], bodyModels[i][4] + bodyModels[i][2] + bodyModels[i][2], 0, bodyModels[i][4]
        minTX = tX(i, minTX)
        maxTX = tX(i, maxTX)
        minTY = tY(i, minTY)
        maxTY = tY(i, maxTY)
        res += str(6 * i + 3 + GLOBAL_OFFSET) + " QUAD " + maxTX + ";" + maxTY + " " + minTX + ";" + maxTY + " " + minTX + ";" + minTY + " " + maxTX + ";" + minTY + " " \
            + translate("0;-" + yS + ";-" + zS + " " \
            + xS + ";-" + yS + ";-" + zS + " " \
            + xS + ";-" + yS + ";0" + " " \
            + "0;-" + yS + ";0", i) + "\n"
        maxTX, minTX, minTY, maxTY = 0, bodyModels[i][4], bodyModels[i][4], bodyModels[i][4] + bodyModels[i][3]
        minTX = tX(i, minTX)
        maxTX = tX(i, maxTX)
        minTY = tY(i, minTY)
        maxTY = tY(i, maxTY)
        res += str(6 * i + 4 + GLOBAL_OFFSET) + " QUAD " + maxTX + ";" + minTY + " " + maxTX + ";" + maxTY + " " + minTX + ";" + maxTY + " " + minTX + ";" + minTY + " " \
            + translate("0;0;-" + zS + " " \
            + "0;-" + yS + ";-" + zS + " " \
            + "0;-" + yS + ";0" + " " \
            + "0;0;0", i) + "\n"
        minTX, maxTX, minTY, maxTY = bodyModels[i][4] + bodyModels[i][2], bodyModels[i][4] + bodyModels[i][2] + bodyModels[i][4], bodyModels[i][4], bodyModels[i][4] + bodyModels[i][3]
        minTX = tX(i, minTX)
        maxTX = tX(i, maxTX)
        minTY = tY(i, minTY)
        maxTY = tY(i, maxTY)
        #print(i, minTX, maxTX, minTY, maxTY)
        # should clean code by using functions
        res += str(6 * i + 5 + GLOBAL_OFFSET) + " QUAD " + maxTX + ";" + minTY + " " + maxTX + ";" + maxTY + " " + minTX + ";" + maxTY + " " + minTX + ";" + minTY + " " \
            + translate(xS + ";0;-" + zS + " " \
            + xS + ";-" + yS + ";-" + zS + " " \
            + xS + ";-" + yS + ";0" + " " \
            + xS + ";0;0", i)
        return res

    finalPath = (additionnalPath + idStr if directApply else modelName) + ".struc"

    fileArgument = "a"
    if BODY_MODEL == BODY_MODEL_REAL:
        fileArgument = "w"
    w = open(finalPath, fileArgument)
    if BODY_MODEL == BODY_MODEL_REAL:
        textureName = modelName.lower()
        if forceTextureName != "":
            textureName = forceTextureName
        w.write(textureName + ".png\n")
    for i in range(BODY_MODELS_LEN):
        toWrite = strFromMCPart(i)
        w.write(toWrite) # used ot be str(i) + " QUAD 1;0 1;1 0;1 0;0 " + " ".join(map(str, bodyModels[i])) # .replace(".0;", "").replace(".0 ", "")
        #print(toWrite)
        if isLast or i != BODY_MODELS_LEN - 1:
            w.write("\n")
    w.close()
    GLOBAL_OFFSET += 6 * BODY_MODELS_LEN

#l = [LEFT_FRONT_WHEEL_MODEL]
l = [BODY_MODEL_REAL, DOOR_CLOSE_MODEL, DOOR_OPEN_MODEL, LEFT_FRONT_WHEEL_MODEL, RIGHT_FRONT_WHEEL_MODEL, LEFT_BACK_WHEEL_MODEL, RIGHT_BACK_WHEEL_MODEL, FRONT_WHEEL_MODEL, BACK_WHEEL_MODEL, LEFT_TRACK_WHEEL_MODEL, LEFT_TRACK_MODEL, RIGHT_TRACK_MODEL, TRAILER_MODEL, STEERING_WHEEL_MODEL]
#
#

lLen = len(l)
for modelIndex in range(lLen):
    model = l[modelIndex]
    workOn(model, modelIndex < lLen - 1)

# TODO:

"""

addShape3D
addShapeBox
addTrapezoid
addFlexBox
addFlexTrapezoid

later: make a good format to store this kind of vehicles (cubes)

could make stats about only vehicles which function is used in how many models

and then work firstly on the less new function used ?

"""

# DONE:

"""

rotX, rotY, rotZ
offset (depends of rot)

doors: open, closed
wheels: front left, front right, back left, back right
steering wheel

"""

"""

Could be useful: https://github.com/Demitto/Flan-s-Mod-Plus/blob/master/src/main/java/com/flansmod/client/tmt/ModelRendererTurbo.java

Manus permission: https://pastebin.com/2ise9067

/Structure 11 3691 13132 12 0

rotX:

X cst
Y
Z cos

Notepad++:

(func_78790_a)|(func_78793_a)|(field_78795_f)|(field_78796_g)|(field_78808_h)
(?1addBox)(?2setRotationPoint)(?3rotateAngleX)(?4rotateAngleY)(?5rotateAngleZ)

Models just using addBox: egrep -Lr "addShape3D|addTrapezoid|addFlexBox|addFlexTrapezoid|addShapeBox" .

Output format:

texture.jpg
0 QUAD tx0;ty0 tx1;ty1 tx2;ty2 tx3;ty3 x0;y0;z0 x1;y1;z1 x2;y2;z2 x3;y3;z4

QUAD stands for quadrilateral
First four couples are used as texture coordinates
Four last triples are used as shape coordinates

"""
