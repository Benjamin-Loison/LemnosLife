import numpy as np
from math import cos, sin, radians

def rot(theta, phi, roll):

    A = np.zeros((3, 3))

    thetaRad, phiRad, rollRad = radians(theta), radians(phi), radians(roll)
    cosTheta, sinTheta = cos(thetaRad), sin(thetaRad)
    cosPhi, sinPhi = cos(phiRad), sin(phiRad)

    cosRoll, sinRoll = cos(rollRad), sin(rollRad)
    A[0][0] = cosRoll * cosPhi - sinRoll * cosTheta * sinPhi
    A[0][1] = -cosRoll * sinPhi - sinRoll * cosTheta * cosPhi
    A[0][2] = sinRoll * sinTheta

    A[1][0] = sinRoll * cosPhi + cosRoll * cosTheta * sinPhi
    A[1][1] = -sinRoll * sinPhi + cosRoll * cosTheta * cosPhi
    A[1][2] = -cosRoll * sinTheta

    A[2][0] = sinTheta * sinPhi
    A[2][1] = sinTheta * cosPhi
    A[2][2] = cosTheta

    return A

theta, phi, roll = 0, 39.2, 0
A = rot(theta, phi, roll)
print(A)

print()

AMT = np.array([0.09375, 0.5, 0.5])
res = AMT.dot(A)
print(res)