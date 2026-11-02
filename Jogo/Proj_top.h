#pragma once
#include "Bibliotecas.h"
#include "Projetil.h"

namespace Entidades
{
	class Proj_top : public Projetil
	{
	private:
		int dano;

	public:
		Proj_top(short int direcao, float x, float y);
		~Proj_top();
		void setDano(int d);
		const int getDano() const;
		void colisao(Entidade* ent, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
	};
}