#include <sstream>
#include "Polygon.h"

using namespace std;

Polygon::Polygon()
{
	fNumberOfVertices = 0;
}

size_t Polygon::getNumberOfVertices() const
{
	return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex(size_t aIndex) const
{
	return fVertices[aIndex];
}

void Polygon::readData(istream& aIStream)
{
	while (fNumberOfVertices < MAX_VERTICES && aIStream >> fVertices[fNumberOfVertices])
	{
		fNumberOfVertices++;
	}
}

float Polygon::getPerimeter() const
{
	float lPerimeter = 0.0f;

	for (size_t i = 0; i < fNumberOfVertices; i++)
	{
		lPerimeter += (fVertices[i] - fVertices[(i + 1) % fNumberOfVertices]).length();
	}

	return lPerimeter;
}

Polygon Polygon::scale(float aScalar) const
{
	Polygon lScaled = *this;

	lScaled.fNumberOfVertices = fNumberOfVertices;

	for (size_t i = 0; i < fNumberOfVertices; i++)
	{
		lScaled.fVertices[i] = fVertices[i] * aScalar;
	}

	return lScaled;
}