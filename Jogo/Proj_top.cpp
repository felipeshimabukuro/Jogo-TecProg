#include "Proj_top.h"
#include "Jogador.h"

using namespace Entidades;
using namespace Personagens;

Proj_top::Proj_top(short int direcao, float x, float y):
	Projetil(direcao, x, y),
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

void Proj_top::colisao(Entidade* ent, sf::Vector2f ds)
{
	if(ent)
	{
		Jogador* jogador = static_cast<Jogador*>(ent);
		if(jogador)
		{
			jogador->receberDano(getDano());
		}
	}
}
