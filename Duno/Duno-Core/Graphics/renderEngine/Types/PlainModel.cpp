#include "PlainModel.h"

Duno::Graphics::RenderEngine::PlainModel::PlainModel(int vaoID, int vertex, int vaoLength, bool index)
{
}

int Duno::Graphics::RenderEngine::PlainModel::getVaoID()
{
	return vaoID;
}

int Duno::Graphics::RenderEngine::PlainModel::getVaoLength()
{
	return vaoLength;
}

void Duno::Graphics::RenderEngine::PlainModel::setVaoLength(int length)
{
	vaoLength = length;
}

int Duno::Graphics::RenderEngine::PlainModel::getVertexNumber()
{
	return vertexNumber;
}

bool Duno::Graphics::RenderEngine::PlainModel::getHasIndexBuffer()
{
	return hasIndexBuffer;
}
