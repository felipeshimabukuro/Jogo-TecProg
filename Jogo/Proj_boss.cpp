#include "Proj_boss.h"
#include "Proj_top.h"
#include "Gerenciador_colisao.h"

using namespace Gerenciadores;
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
}

void Proj_boss::setFragmentos(int frag)
{
	fragmentos = frag;
}

const int Proj_boss::getFragmentos() const
{
	return fragmentos;
}

void Proj_boss::colisao(Entidade* ent, sf::Vector2f ds)
{
	if (ent)
	{
		Gerenciador_colisao* pGC = Gerenciador_colisao::getGerenciadorColisao();
		for (int i = 0; i < fragmentos; i++)
		{
			short int lado = rand() % 5 - 2;
			Projetil* proj = new Proj_top(lado, x + getTam().x / 2, y + getTam().y / 2);
			if (proj && pGC)
			{
				pGC->adicionarProjetil(proj);
			}
		}
	}
}