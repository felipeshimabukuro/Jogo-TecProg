#include "Proj_boss.h"
#include "Proj_top.h"
#include "Gerenciador_colisao.h"

using namespace Gerenciadores;
using namespace Entidades;

Proj_boss::Proj_boss(float vX, float vY, short int direcao):
	Projetil(ID::projBoss, vX, vY, direcao),
	fragmentos(3)
{
	velY = 0;
	srand(time(NULL));
	setFragmentos(rand() % 2 + 3);

	corpo.setSize(sf::Vector2f(28.0f, 28.0f));
	corpo.setPosition(x, y);
	setTextura("terra", getTam());
	sprite.setPosition(x, y);
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

void Proj_boss::salvarDataBuffer()
{
	Projetil::salvarDataBuffer();
	buffer << fragmentos;
}

void Proj_boss::salvar()
{
	buffer.str(""); // Limpa dados de saves anteriores no buffer
	buffer.clear();

	salvarDataBuffer();
}