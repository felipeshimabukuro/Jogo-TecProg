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
	};
}