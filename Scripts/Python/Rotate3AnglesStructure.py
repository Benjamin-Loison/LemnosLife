#import numpy as np
from scipy.spatial.transform import Rotation as R
# https://docs.scipy.org/doc/scipy/reference/generated/scipy.spatial.transform.Rotation.html
#from scipy.ndimage import map_coordinates
from math import radians

orient = [-90, 0, 0]
orient = [radians(w) for w in orient]

# 0 QUAD tX0;tY0 tX1;tY1 tX2;tY2 tX3;tY3 x0;y0;z0 x1;y1;z1 x2;y2;z2 x3;y3;z3

# https://stackoverflow.com/questions/59738230/apply-rotation-defined-by-euler-angles-to-3d-image-in-python
"""def rotateArray(array, orient):
    phi, psi, the = orient

    # create meshgrid
    dim = array.shape
    ax = np.arange(dim[0])
    ay = np.arange(dim[1])
    az = np.arange(dim[2])
    coords = np.meshgrid(ax, ay, az)

    # stack the meshgrid to position vectors, center them around 0 by substracting dim/2
    xyz = np.vstack([coords[0].reshape(-1) - float(dim[0]) / 2,  # x coordinate, centered
                     coords[1].reshape(-1) - float(dim[1]) / 2,  # y coordinate, centered
                     coords[2].reshape(-1) - float(dim[2]) / 2])  # z coordinate, centered

    # create transformation matrix
    r = R.from_euler('zxz', [phi, psi, the], degrees=True)
    mat = r.as_matrix()

    # apply transformation
    transformed_xyz = np.dot(mat, xyz)

    # extract coordinates
    x = transformed_xyz[0, :] + float(dim[0]) / 2
    y = transformed_xyz[1, :] + float(dim[1]) / 2
    z = transformed_xyz[2, :] + float(dim[2]) / 2

    x = x.reshape((dim[1],dim[0],dim[2]))
    y = y.reshape((dim[1],dim[0],dim[2]))
    z = z.reshape((dim[1],dim[0],dim[2])) # reason for strange ordering: see next line

    # the coordinate system seems to be strange, it has to be ordered like this
    new_xyz = [y, x, z]

    arrayR = map_coordinates(array, new_xyz, order=1)
    return arrayR"""

def rotateArray(array, orient):
    r = R.from_rotvec(orient) # convert degrees to rad - done in initialization of orient
    return r.apply(array)

lines = input().split('\n') # or do file input
print()
linesLen = len(lines)
for linesIndex in range(linesLen):
    line = lines[linesIndex]
    lineParts = line.split()
    linePartsLen = len(lineParts)
    if linePartsLen >= 10:
        coordinatesStr = lineParts[6:10] # upperBound in case linePartsLen strictly exceeds 10
        coordinates = [s.split(';') for s in coordinatesStr]
        coordinatesLen = len(coordinates)
        for coordinatesIndex in range(coordinatesLen):
            coordinate = coordinates[coordinatesIndex]
            newCoordinate = [float(w) for w in coordinate] # x;y;z
            #print(newCoordinate)
            #newCoordinate = np.array(newCoordinate)
            newCoordinate = rotateArray(newCoordinate, orient)
            res = []
            newCoordinateLen = len(newCoordinate)
            for newCoordinateIndex in range(newCoordinateLen):
                newCoordinatePart = newCoordinate[newCoordinateIndex]
                newCoordinatePart = str(round(newCoordinatePart, 3))
                if newCoordinatePart[-2:] == ".0":
                    newCoordinatePart = newCoordinatePart[:-2]
                res += [newCoordinatePart]
            coordinates[coordinatesIndex] = ';'.join(res)
        line = ' '.join(lineParts[:6]) + ' ' + ' '.join(coordinates)
    print(line)
