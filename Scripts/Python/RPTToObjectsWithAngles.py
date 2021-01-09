import numpy as np
from math import atan2, asin, pi

def abs(l): # assume 3 of length
    return (l[0] ** 2 + l[1] ** 2 + l[2] ** 2) ** 0.5

def getDegrees(radians):
    return radians * 180 / pi

# according to theory: https://stackoverflow.com/questions/21622956/how-to-convert-direction-vector-to-euler-angles
def getAngles(vectorUp, vectorDir):
    phi = atan2(vectorDir[1], vectorDir[0])
    theta = asin(vectorDir[2])

    W0 = (-vectorDir[1], vectorDir[0], 0)

    U0 = np.cross(W0, vectorDir)

    roll = atan2(np.dot(W0, vectorUp) / abs(W0), np.dot(U0, vectorUp) / abs(U0))

    return [getDegrees(x) for x in (phi, theta, roll)] # phi seems to be different from getDir if there is non null theta and roll components

vectorUpTest = np.array([-0.559193, 0.172367, 0.810921])
vectorDirTest = np.array([0.687303, 0.643359, 0.337199])

angles = getAngles(vectorUpTest, vectorDirTest)
print(angles)

