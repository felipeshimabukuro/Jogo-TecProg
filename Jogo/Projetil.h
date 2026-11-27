#pragma once
#include "Bibliotecas.h"
#include "Entidade.h"

namespace Escavadores_intrepidos {
	namespace Entidades
	{
		class Projetil : public Entidade
		{
		protected:
			float velX;
			short int direcao;

		public:
			Projetil(short int dir, float ix, float iy);
			~Projetil();
			virtual void trajetoria();
			virtual void salvar() = 0;
			virtual void salvarDataBuffer();
			void executar();
			virtual void colisao(Entidade* ent, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) = 0;
			void setVelX(const float vx);
			void setVelY(const float vy);
		};
	}
}