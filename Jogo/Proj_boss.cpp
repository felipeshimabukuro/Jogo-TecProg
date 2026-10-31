#include "Proj_boss.h"

using namespace Entidades;

Proj_boss::Proj_boss(int vX, int vY, short int direcao):
	Projetil(vX, vY, direcao),
	fragmentos(3)
{
	srand(time(NULL));
	setFragmentos(rand() % 2 + 3);
}

Proj_boss::~Proj_boss()
{
	//criar n proj_top
}

void Proj_boss::setFragmentos(int frag)
{
	fragmentos = frag;
}

const int Proj_boss::getFragmentos() const
{
	return fragmentos;
}