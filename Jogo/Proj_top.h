#pragma once
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
		Proj_top(int vX, int vY, short int direcao);
		~Proj_top();
		void setDano(int d);
		const int getDano() const;
	};
}