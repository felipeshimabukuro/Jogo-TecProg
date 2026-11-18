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

	corpo.setSize(sf::Vector2f(28.0f, 28.0f));
	corpo.setFillColor(sf::Color::Yellow); 
	corpo.setPosition(x, y);
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
		//mudar para o novo ///////////////////////////////////////////////////
		Gerenciador_colisao* pGC = Gerenciador_colisao::getGerenciadorColisao();
		if (!pGC)
			return;

		float spawnX = x + getTam().x / 2.0f;
		float spawnY = y - 15.0f;

		for (int i = 0; i < fragmentos; i++)
		{
			short int lado;
			if (i%2 == 0)
			{
				lado = -1;
			}
			else
			{
				lado = 1;
			}

			if (i >= 2)
			{
				lado *= i;
			}

			Projetil* proj = new Proj_top(lado, spawnX, spawnY);
			if (proj)
			{
				pGC->adicionarProjetil(proj);
			}
		}
	}
}
