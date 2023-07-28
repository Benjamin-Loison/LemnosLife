def norm1(l):
    return abs(l[0]) + abs(l[1]) + abs(l[2])

def norm2(l):
    return (l[0] ** 2 + l[1] ** 2 + l[2] ** 2) ** 0.5

all = [
    [-79,453,-188],
    [-752,246,-114],
    [-61,-413,216],
    [47,297,426]
]

all = [
     [-1,18,509],
     []
]

for l in all:
    print(str(norm1(l)) + ' ' + str(norm2(l)))

##

import subprocess, os, time, math

path = 'C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\C and co\\C++\\Projects\\LemnosLife\\Client\\Mess\\'

cmd = 'C:\\Users\\Benjamin\\Desktop\\platform-tools_r29.0.6-windows\\platform-tools\\adb.exe pull /sys/class/sensors/accelerometer_sensor/raw_data'

os.chdir(path)


initialTime = time.time()

previousAccelerometer = [0] * 3
i = 0

# TODO: truncate (if up to 510 for example go back to 510)

MAX_ANGLE = 1.569

# theta real values: negatives 0 (bottom view), MAX_ANGLE (horizontal view), 0 (sky view) -> seems we can't know if looking at the bottom or sky for a given value (should "initialize")

# LL:
# theta: [-85; 70]

def computeAngles(xyz):
    phi = math.atan(xyz[1] / xyz[2])

    den = (xyz[1] ** 2 + xyz[2] ** 2) ** 0.5
    #if den == 0:
    #    theta =
    theta = math.atan(-xyz[0] / den)
    theta *= 90 / MAX_ANGLE

    return phi, theta

while True:
    subprocess.check_call(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.STDOUT)

    with open('raw_data') as f:
        data = f.readline()[:-1]

    currentTime = time.time()
    t = round(currentTime - initialTime, 2)

    accelerometer = [int(composant) for composant in data.split(',')]

    if accelerometer != previousAccelerometer:
        print(t, i, accelerometer)
        previousAccelerometer = accelerometer
        # TODO: give angles and refresh ingame
        #print(computeAngles(accelerometer))
        # TODO: is atan making me think that we can't get good angles ?

    i += 1

    #time.sleep(0.02)

# 70 ms new iteration in the while loop
# /!\ may be != period of sampling (of the accelerometer)

# with rotation mode activated
# when screen is off not refreshing (no need to unlock the phone)

# could do remotly (web server...) but pluged give a low-level access

# n'importe quoi:  # seems to be not in the order phi, theta but it is - sure ? nope (for computeAngles return)
