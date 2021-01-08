#ifndef AI_PLUS_H_INCLUDED
#define AI_PLUS_H_INCLUDED

#include <vector>
#include "../2D/vector2d.h"

void initializeDijkstra();
std::vector<Vector2D> /*nearestDijkstra(Vector2D sBeginning, Vector2D sEnd), */nearestDijkstra(double xEnd, double yEnd);

#endif
