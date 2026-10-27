#include "Entidade.h"
#include "Bibliotecas.h"

using namespace Entidades;

Entidade::Entidade(int xx = 0, int yy = 0) : x(xx), y(yy), buffer(NULL)
{
}

Entidade::~Entidade()
{
}

void Entidade::salvarDataBuffer()
{
	
}

const int Entidade::getX() const {
	return x;
}

const int Entidade::getY() const {
	return y;
}