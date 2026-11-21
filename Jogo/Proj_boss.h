#pragma once
#include "Bibliotecas.h"
#include "Projetil.h"

namespace Entidades
{
	class Proj_boss : public Projetil
	{
	private:
		int fragmentos;

	public:
		Proj_boss(int vX, int vY, short int direcao);
		~Proj_boss();
		void setFragmentos(int frag);
		const int getFragmentos() const;
		void colisao(Entidade* ent, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
		void salvarDataBuffer();
		void salvar();
	};
}