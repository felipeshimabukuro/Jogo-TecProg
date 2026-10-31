#include "Proj_top.h"

using namespace Entidades;

Proj_top::Proj_top(int vX, int vY, short int direcao):
	Projetil(vX, vY, direcao),
	dano(10)
{
	srand(time(NULL));
	setDano(rand() % 10 + 10);
}

Proj_top::~Proj_top()
{
}

void Proj_top::setDano(int d)
{
	dano = d;
}

const int Proj_top::getDano() const
{
	return dano;
}