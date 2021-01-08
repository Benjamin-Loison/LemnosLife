#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "partitioning.h"
#include "../Render/Engine/vector3d.h"
#include "../../2D/vector2d.h"

#define TWOPI 6.283185307179586476925287
#define EPSILON 0.000000001
// which precision is really required ?

void initializeCollision();
bool lineQuadrilateralIntersect(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*),
     semiLineQuadrilateralIntersect(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*),
     segmentQuadrilateralIntersect(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*),
     rayPicking(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*),
     rayPickingFromFoot(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*, bool = false, Vector3D = Vector3D()),
     intersection(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, Vector3D*),
     pointIsInTriangle(Vector2D, Vector2D, Vector2D, Vector2D),
     pointIsInPolygon(point, std::vector<point>),
     pointIsInPolygon(Vector2D, std::vector<Vector2D>),
     pointIsIn2DPolygon(Vector3D, std::vector<Vector3D>),// isn't used
     pointIsIn2DPolygon(Vector3D, std::vector<Vector2D>),
     pointIsInTriangle3D(Vector3D, Vector3D, Vector3D, Vector3D);

double groundAltitude(Vector3D, Vector3D, Vector3D, Vector3D), groundAltitudePoints(Vector3D, Vector3D, Vector3D, Vector3D), groundAltitudePoints(Vector3D, Vector3D, Vector3D, Vector3D, Vector3D, bool = false);
Vector3D getBarycenter(std::vector<Vector3D> vecs), getBarycenter(std::vector<double>), getBarycenter(std::vector<std::string>);

#endif
