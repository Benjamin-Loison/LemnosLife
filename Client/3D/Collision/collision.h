#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "partitioning.h"
#include "../Render/Engine/vector3d.h"
#include "../../2D/vector2d.h"

#define TWOPI 6.283185307179586476925287
#define EPSILON 0.000000000000000000000000000001

// 0.000000000000000001

void initializeCollision();
bool lineQuadrilateralIntersect(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*);
bool semiLineQuadrilateralIntersect(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*);
bool segmentQuadrilateralIntersect(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*);
bool rayPicking(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*);

double groundAltitude(Vector3D, Vector3D, Vector3D, Vector3D), groundAltitudePoints(Vector3D, Vector3D, Vector3D, Vector3D), groundAltitudePoints(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, bool = false);
bool pointIsInTriangle(Vector2D, Vector2D, Vector2D, Vector2D);



//Old deprecated functions
/*int F5CollisionDetection(Point3D, Point3D);
bool checkPlayerCollision();
std::pair<bool, Point> intersect(Segment, Segment);*/

#endif
