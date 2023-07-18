import os

# used to be named FlansModClassToJava but the name was incorrect

path = "C:\\Users\\Benjamin\\Desktop\\Flans\\com\\flansmod\\client\\model\\"
os.chdir(path)
cleanDir = "clean\\"

for r, d, files in os.walk(path):
    if "clean" in r:
        continue
    r += "\\"
    if r != path + "\\":
        if not os.path.isdir(r + cleanDir):
            os.mkdir(r + cleanDir)
    for file in files:
        if file[-5:] == ".java":
            print("Working on: " + r + file)

            f = open(r + file)
            lines = f.readlines()
            f.close()

            linesLen = len(lines)
            for linesIndex in range(linesLen):
                line = lines[linesIndex]
                lineParts = line.split("*/ ")
                if len(lineParts) >= 2:
                    line = lineParts[1]
                lines[linesIndex] = line.replace("func_78790_a", "addBox").replace("func_78793_a", "setRotationPoint").replace("field_78795_f", "rotateAngleX").replace("field_78796_g", "rotateAngleY").replace("field_78808_h", "rotateAngleZ")

            workingOnShape3D = False
            f = open(r + cleanDir + file, 'w')
            for linesIndex in range(linesLen):
                line = lines[linesIndex]
                if ".add" in line:
                    linePart = line.split(".add")[1]
                    workingOnShape3D = linePart[:7] == "Shape3D"
                    if workingOnShape3D:
                        pattern = "new Shape2D("
                        lineParts = line.split(pattern)
                        line = lineParts[0] + pattern + lineParts[1].replace(".0D", "").replace(".0F", "")
                else:
                    if ".rotateAngle" in line:
                        line = line.replace("(this.", "this.").replace("]).r", "].r")
                f.write(line)
            f.close()
