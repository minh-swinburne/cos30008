// COS30008, Problem Set 1/1, 2024

#include "Polygon.h"

float Polygon::getSignedArea() const
{
	float result = 0.0;

	if (fNumberOfVertices > 2) // a polygon with less than 3 vertices has no area
	{
		for (size_t i = 0; i < fNumberOfVertices; i++)
		{
			Vector2D lCurrent = fVertices[i];
			// if the current vertex is the last one, the next vertex will be the first vertice
			Vector2D lNext = fVertices[(i + 1) % fNumberOfVertices];

			// add determinant to the sum 
			// in 2D, this value is mathematically equal to the cross product of the two 2D vectors in terms of magnitude (= x1 * y2 - y1 * x2)
			result += lCurrent.cross(lNext);
			// of course, we can calculate it independently as follows
			//result += lCurrent.getX() * lNext.getY() - lCurrent.getY() * lNext.getX();
		}
	}

	return result / 2.0f;
}