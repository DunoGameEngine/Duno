#include "PlainModel.h"

Duno::Graphics::RenderEngine::Types::PlainModel::PlainModel(int vaoID, int vertex, int vaoLength, bool index)
{
}

int Duno::Graphics::RenderEngine::Types::PlainModel::getVaoID()
{
	return vaoID;
}

int Duno::Graphics::RenderEngine::Types::PlainModel::getVaoLength()
{
	return vaoLength;
}

void Duno::Graphics::RenderEngine::Types::PlainModel::setVaoLength(int length)
{
	vaoLength = length;
}

int Duno::Graphics::RenderEngine::Types::PlainModel::getVertexNumber()
{
	return vertexNumber;
}

bool Duno::Graphics::RenderEngine::Types::PlainModel::getHasIndexBuffer()
{
	return hasIndexBuffer;
}
